#include "pch.h"

namespace logger = SKSE::log;

// ---------------------------------------------------------------------------
// Friendly-fire resist logic
//
//   P = spell cast by player
//   H = target is hostile to player
//   S = target is a commanded actor (summon / raise / dominate)
//   A = target has Ally faction relation to player (GROUP_COMBAT_REACTION == 2)
//
//   ALLOW hit when: (!P || H || !S) && (!P || H || !A)
//   BLOCK hit when: P && !H && (S || A)
//
// Hook: MagicTarget::AddTarget — returns false to drop hits on friendlies.
// ---------------------------------------------------------------------------

namespace {

    static inline bool g_suppressNextHitEvent = false;

    // Returns true if any effect on the magic item has the Hostile flag.
    bool HasHostileEffect(RE::MagicItem* a_item)
    {
        if (!a_item) {
            return false;
        }
        for (auto* eff : a_item->effects) {
            if (eff && eff->baseEffect && eff->baseEffect->IsHostile()) {
                return true;
            }
        }
        return false;
    }

    // Checks if any of the target's factions have an Ally reaction
    // toward any faction the player belongs to.
    bool IsAllyToPlayer(RE::Actor* a_target, RE::PlayerCharacter* a_player)
    {
        auto* targetBase = a_target->GetActorBase();
        auto* playerBase = a_player->GetActorBase();
        if (!targetBase || !playerBase) {
            return false;
        }

        for (auto& targetFR : targetBase->factions) {
            auto* tFaction = targetFR.faction;
            if (!tFaction) {
                continue;
            }

            for (auto* reaction : tFaction->reactions) {
                if (!reaction || reaction->fightReaction != RE::FIGHT_REACTION::kAlly) {
                    continue;
                }
                for (auto& playerFR : playerBase->factions) {
                    if (playerFR.faction == reaction->form) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // ── Hook: MagicTarget::AddTarget ────────────────────────────────────────

    // Actor inherits: TESObjectREFR(4 vtables), MagicTarget, ActorValueOwner,
    // ActorState, 2x BSTEventSink, IPostAnimationChannelUpdateFunctor = 10 total.
    // MagicTarget is the 5th vtable segment (index 4).
    // AddTarget is slot 1 in MagicTarget's vtable (confirmed via Ghidra).
    constexpr std::size_t kMagicTargetIdx    = 4;
    constexpr std::size_t kAddTargetVfuncIdx = 1;

    struct AddTargetHook {
        static bool thunk(RE::MagicTarget* a_this, RE::MagicTarget::AddTargetData& a_data)
        {
            auto* targetActor = skyrim_cast<RE::Actor*>(a_this);
            if (!targetActor) {
                return func(a_this, a_data);
            }

            auto* player = RE::PlayerCharacter::GetSingleton();
            if (!player) {
                return func(a_this, a_data);
            }

            // Always allow spells on self
            if (targetActor == static_cast<RE::Actor*>(player)) {
                return func(a_this, a_data);
            }

            // P: cast by player — caster is a TESObjectREFR*
            if (a_data.caster != static_cast<RE::TESObjectREFR*>(player)) {
                logger::trace("NOFF: non-player caster on '{}' casterType={} spell={}",
                    targetActor->GetName(),
                    a_data.caster ? a_data.caster->GetFormType() : RE::FormType::None,
                    a_data.magicItem ? a_data.magicItem->GetName() : "?");
                return func(a_this, a_data);
            }
            logger::trace("NOFF: player caster on '{}' spell={}",
                targetActor->GetName(),
                a_data.magicItem ? a_data.magicItem->GetName() : "?");

            // Weapon enchantments go through here too — skip them
            if (skyrim_cast<RE::EnchantmentItem*>(a_data.magicItem)) {
                return func(a_this, a_data);
            }

            // H: target is currently hostile toward the player
            const bool H = targetActor->IsHostileToActor(player);

            // S: target is a commanded actor (summon / raise / dominate)
            const bool S = targetActor->IsCommandedActor();

            // A: target has Ally faction relation to player
            const bool A = IsAllyToPlayer(targetActor, player);

            logger::trace("NOFF: player spell on '{}' H={} S={} A={} spell={}",
                targetActor->GetName(), H, S, A,
                a_data.magicItem ? a_data.magicItem->GetName() : "?");

            // Block when: !H && (S || A)
            if (!H && (S || A)) {
                logger::trace("NOFF: blocked on ally/summon");
                return false;  // drop the hit — effect never applied
            }

            // Neutral NPC hit by hostile spell: let effect apply but suppress
            // the hit-task that would make the NPC turn hostile.
            if (!H && HasHostileEffect(a_data.magicItem)) {
                logger::trace("NOFF: suppressing hit-task for '{}'", targetActor->GetName());
                g_suppressNextHitEvent = true;
                bool result = func(a_this, a_data);
                g_suppressNextHitEvent = false;
                return result;
            }

            return func(a_this, a_data);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // Hook all three classes that have their own MagicTarget vtable.
            // Character and PlayerCharacter don't inherit Actor's MagicTarget
            // vtable — each gets its own, all at the same index and slot.
            REL::Relocation<std::uintptr_t> vtblActor{ RE::VTABLE_Actor[kMagicTargetIdx] };
            func = vtblActor.write_vfunc(kAddTargetVfuncIdx, thunk);

            REL::Relocation<std::uintptr_t> vtblCharacter{ RE::VTABLE_Character[kMagicTargetIdx] };
            vtblCharacter.write_vfunc(kAddTargetVfuncIdx, thunk);

            REL::Relocation<std::uintptr_t> vtblPlayerCharacter{ RE::VTABLE_PlayerCharacter[kMagicTargetIdx] };
            vtblPlayerCharacter.write_vfunc(kAddTargetVfuncIdx, thunk);

            auto base = REL::Module::get().base();
            logger::debug("NOFF: image base            = {:016X}", base);
            logger::debug("NOFF: Actor::AddTarget      = {:016X} (offset {:08X})",
                func.address(), func.address() - base);

            logger::info("NOFF: MagicTarget::AddTarget hooked on Actor, Character, PlayerCharacter (idx {} vfunc {})",
                kMagicTargetIdx, kAddTargetVfuncIdx);
        }
    };

    // ── Hook 2: Hit-event broadcast ──────────────────────────────────────────
    //
    // BSTEventSource<TESHitEvent>::SendEvent call site inside Actor::AddTarget
    // (offset 0x6C533B, AE 1.6.1170). Broadcasts to all registered hit-event
    // listeners including the crime/witness system. Suppressing this prevents
    // guards from being alerted by AOE spells (Fire Storm, Lightning Storm).
    // Skipped when g_suppressNextHitEvent is set by AddTargetHook.

    struct HitEventHook {
        static void thunk(void* a_eventSource, void* a_event)
        {
            if (g_suppressNextHitEvent) {
                logger::trace("NOFF: hit-event suppressed");
                return;
            }
            return func(a_eventSource, a_event);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: HitEventHook requires AE — skipped");
                return;
            }

            // Call site verified in Ghidra for AE 1.6.1170 at 0x1406C533B.
            REL::Relocation<std::uintptr_t> target{ REL::Offset(0x6C533B) };
            func = SKSE::GetTrampoline().write_call<5>(target.address(),
                reinterpret_cast<std::uintptr_t>(thunk));

            logger::info("NOFF: hit-event hook installed at offset {:08X}", 0x6C533Bu);
        }
    };

    // ── Hook 3: Hit-task dispatch ────────────────────────────────────────────
    //
    // Actor_QueueHitTask call site inside Actor::AddTarget (offset 0x6C5413,
    // AE 1.6.1170). Queues the fUnk_Attacked task (0x62) that notifies
    // combat AI and causes the NPC to personally turn hostile.
    // Skipped when g_suppressNextHitEvent is set by AddTargetHook.

    struct HitTaskHook {
        static void thunk(void* a_taskPool, RE::Actor* a_target, RE::TESObjectREFR* a_caster,
                          void* a_spell, std::uint32_t a_param5)
        {
            logger::trace("NOFF: hit-task enter target='{}' suppress={}",
                a_target ? a_target->GetName() : "?", g_suppressNextHitEvent);
            if (g_suppressNextHitEvent) {
                logger::trace("NOFF: hit-task suppressed");
                return;
            }
            logger::trace("NOFF: hit-task calling func");
            func(a_taskPool, a_target, a_caster, a_spell, a_param5);
            logger::trace("NOFF: hit-task func returned");
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: HitTaskHook requires AE — skipped");
                return;
            }

            // Call site of Actor_QueueHitTask inside Actor::AddTarget,
            // verified in Ghidra for AE 1.6.1170 (E8 68 19 F9 FF at 0x1406C5413).
            // Must use write_call (E8) not write_branch (E9) — original is a CALL,
            // and JMP would misalign the stack by 8, crashing on movaps in the thunk.
            REL::Relocation<std::uintptr_t> target{ REL::Offset(0x6C5413) };
            func = SKSE::GetTrampoline().write_call<5>(target.address(),
                reinterpret_cast<std::uintptr_t>(thunk));

            auto base = REL::Module::get().base();
            logger::info("NOFF: hit-task hook installed at {:016X} (offset {:08X})",
                target.address(), target.address() - base);
        }
    };

}  // namespace

// ---------------------------------------------------------------------------
// SKSE plugin boilerplate
// ---------------------------------------------------------------------------

void InitLogger()
{
    auto path = SKSE::log::log_directory();
    if (!path) {
        SKSE::stl::report_and_fail("Unable to locate SKSE log directory.");
    }
    *path /= SKSE::PluginDeclaration::GetSingleton()->GetName();
    *path += L".log";

    auto sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(path->string(), true);
    auto log  = std::make_shared<spdlog::logger>("global", std::move(sink));

    log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::info);

    spdlog::set_default_logger(std::move(log));
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    InitLogger();

    auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    logger::info("NOFF v{} loading", plugin->GetVersion());

    SKSE::AllocTrampoline(28);

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
            AddTargetHook::Install();
            HitEventHook::Install();
            HitTaskHook::Install();
        }
    });

    return true;
}
