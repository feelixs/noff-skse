#include "pch.h"

#include <unordered_set>

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
// Hook 1: MagicTarget::AddTarget — returns false to drop hits on friendlies.
// Hook 2: Actor::SendAssaultAlarm — suppresses NPC hostility reaction when
//         a player spell hits a neutral (non-hostile) NPC.  Melee and
//         NPC-cast spells are unaffected.
// ---------------------------------------------------------------------------

namespace {

    // Actors recently hit by a player spell that has the Hostile flag.
    // Populated in AddTargetHook, consumed in SendAssaultAlarmHook.
    // Safe without synchronisation — game logic is single-threaded.
    static inline std::unordered_set<RE::FormID> g_playerSpellTargets;

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

    // ── Hook 1: MagicTarget::AddTarget ──────────────────────────────────────

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
                return func(a_this, a_data);
            }

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
                logger::trace("NOFF: blocked");
                return false;  // drop the hit — effect never applied
            }

            // Hit is allowed.  If non-hostile and spell has Hostile effects,
            // mark the target so SendAssaultAlarm can suppress the reaction.
            if (!H && HasHostileEffect(a_data.magicItem)) {
                g_playerSpellTargets.insert(targetActor->GetFormID());
                logger::trace("NOFF: marked '{}' for assault-alarm suppression",
                    targetActor->GetName());
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

            logger::info("NOFF: MagicTarget::AddTarget hooked on Actor, Character, PlayerCharacter (idx {} vfunc {})",
                kMagicTargetIdx, kAddTargetVfuncIdx);
        }
    };

    // ── Hook 2: Actor::SendAssaultAlarm ─────────────────────────────────────
    //
    // Non-virtual function.  Ghidra signature (AE 1.6.1170):
    //   void Actor::SendAssaultAlarm(TESObjectREFR* a_param, bool a_flag)
    //   RCX = this (victim), RDX = a_param, R8B = a_flag
    //
    // Hooked via 5-byte branch trampoline.
    // SE ID 36429  /  AE ID 37424

    struct SendAssaultAlarmHook {
        static void thunk(RE::Actor* a_this, RE::TESObjectREFR* a_param, bool a_flag)
        {
            auto it = g_playerSpellTargets.find(a_this->GetFormID());
            if (it != g_playerSpellTargets.end()) {
                g_playerSpellTargets.erase(it);
                logger::trace("NOFF: suppressed assault alarm on '{}'",
                    a_this->GetName());
                return;
            }

            return func(a_this, a_param, a_flag);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            REL::Relocation<std::uintptr_t> target{ RELOCATION_ID(36429, 37424) };
            func = target.write_branch<5>(thunk);

            logger::info("NOFF: Actor::SendAssaultAlarm hooked (RELOCATION_ID 36429/37424)");
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
    log->flush_on(spdlog::level::trace);

    spdlog::set_default_logger(std::move(log));
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    InitLogger();

    auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    logger::info("NOFF v{} loading", plugin->GetVersion());

    SKSE::AllocTrampoline(14);

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
            AddTargetHook::Install();
            SendAssaultAlarmHook::Install();
        }
    });

    return true;
}
