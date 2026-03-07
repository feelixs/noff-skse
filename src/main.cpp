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
// We hook MagicTarget::AddTarget and return false to drop the hit cleanly.
// ---------------------------------------------------------------------------

namespace {

    // ------------------------------------------------------------------
    // Faction ally check
    //
    // Iterates the target NPC's faction memberships and checks whether
    // any of those factions has a GROUP_COMBAT_REACTION == 2 (Ally)
    // reaction toward any faction the player belongs to.
    //
    // Field names (factions, reactions) are from CommonLibSSE-NG
    // RE/FormComponents/TESActorBase.h and RE/GameObjects/TESFaction.h.
    // If compilation fails here, inspect those headers and adjust.
    // ------------------------------------------------------------------
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

            // TESFaction::reactions — verify field name in RE/GameObjects/TESFaction.h
            // reaction.reaction: GROUP_COMBAT_REACTION  0=Neutral 1=Enemy 2=Ally 3=Friend
            for (auto& reaction : tFaction->reactions) {
                if (reaction.reaction != 2) {
                    continue;
                }
                auto* reactionTarget = reaction.faction;
                if (!reactionTarget) {
                    continue;
                }
                for (auto& playerFR : playerBase->factions) {
                    if (playerFR.faction == reactionTarget) {
                        return true;
                    }
                }
            }
        }
        return false;
    }

    // ------------------------------------------------------------------
    // Hook: MagicTarget::AddTarget
    //
    // Installed as a vtable write on Actor's MagicTarget sub-vtable.
    //
    // *** VERIFY THESE TWO CONSTANTS BEFORE BUILDING ***
    //
    //   kMagicTargetIdx    — index into VTABLE_Actor[] that holds the
    //                        MagicTarget sub-vtable pointer
    //   kAddTargetVfuncIdx — slot within that sub-vtable for AddTarget
    //
    // How to verify with IDA (address library applied):
    //   1. Find the Actor class vtable list.
    //   2. Locate the sub-vtable labelled Actor::MagicTarget (or search
    //      for the string "MagicTarget" in xrefs).
    //   3. Count its 0-based position in RE::VTABLE_Actor[].
    //   4. Within that sub-vtable, AddTarget is the slot that fans out
    //      into ActiveEffect::Start — typically slot 9.
    // ------------------------------------------------------------------
    constexpr std::size_t kMagicTargetIdx    = 6;  // TODO verify
    constexpr std::size_t kAddTargetVfuncIdx = 9;  // TODO verify

    struct AddTargetHook {
        static bool thunk(RE::MagicTarget* a_this, RE::MagicTarget::AddTargetData& a_data)
        {
            auto* targetActor = skyrim_cast<RE::Actor*>(a_this);
            if (!targetActor) {
                return func(a_this, a_data);
            }

            auto* caster = a_data.caster;
            if (!caster) {
                return func(a_this, a_data);
            }

            auto* casterActor = caster->GetCasterActor();
            if (!casterActor) {
                return func(a_this, a_data);
            }

            auto* player = RE::PlayerCharacter::GetSingleton();
            if (!player) {
                return func(a_this, a_data);
            }

            // P: cast by player — only proceed for player spells
            if (casterActor != static_cast<RE::Actor*>(player)) {
                return func(a_this, a_data);
            }

            // H: target is currently hostile toward the player
            const bool H = targetActor->IsHostileToActor(player);

            // S: target is a commanded actor (summon / raise / dominate)
            const bool S = targetActor->IsCommandedActor();

            // A: target has Ally faction relation to player
            const bool A = IsAllyToPlayer(targetActor, player);

            // Allow when: (H || !S) && (H || !A)  [simplified with P=true]
            //   = H || (!S && !A)
            // Block when: !H && (S || A)
            if (!H && (S || A)) {
                logger::trace("NOFF: blocked player spell on {} (S={} A={})",
                    targetActor->GetName(), S, A);
                return false;  // drop the hit — effect never applied
            }

            return func(a_this, a_data);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            REL::Relocation<std::uintptr_t> vtbl{ RE::VTABLE_Actor[kMagicTargetIdx] };
            func = vtbl.write_vfunc(kAddTargetVfuncIdx, thunk);
            logger::info("NOFF: MagicTarget::AddTarget hooked (VTABLE_Actor[{}] vfunc {})",
                kMagicTargetIdx, kAddTargetVfuncIdx);
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

#ifndef NDEBUG
    log->set_level(spdlog::level::trace);
    log->flush_on(spdlog::level::trace);
#else
    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::info);
#endif

    spdlog::set_default_logger(std::move(log));
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    InitLogger();

    auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    logger::info("NOFF v{} loading", plugin->GetVersion());

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
            AddTargetHook::Install();
        }
    });

    return true;
}
