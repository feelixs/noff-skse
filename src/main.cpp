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
//   ALLOW hit when: (!P || H || !S) && (!P || H || !A) || !hostile
//   BLOCK hit when: P && !H && (S || A) && hostile
//
// Hook: MagicTarget::AddTarget — returns false to drop hits on friendlies.
// ---------------------------------------------------------------------------

namespace {

    static inline bool g_suppressNextHitEvent = false;

    // Resolves the display name for any TESForm that may be a spell, shout
    // word-combo spell, or magic effect — returning the highest-level name:
    //   MGEF      → parent SpellItem  → parent TESShout (if voice-power)
    //   SpellItem (kVoicePower) → parent TESShout
    //   Any other MagicItem    → item's own name
    // Returns "" when the form is null or has no resolvable magic name.
    const char* GetSpellDisplayName(RE::TESForm* a_form)
    {
        if (!a_form) {
            return "";
        }

        // EffectSetting (MGEF) — find a parent SpellItem that contains it.
        if (auto* mgef = skyrim_cast<RE::EffectSetting*>(a_form)) {
            auto* dh = RE::TESDataHandler::GetSingleton();
            if (dh) {
                for (auto* spell : dh->GetFormArray<RE::SpellItem>()) {
                    if (!spell) continue;
                    for (auto* eff : spell->effects) {
                        if (eff && eff->baseEffect == mgef) {
                            return GetSpellDisplayName(spell);  // recurse → may hit voice-power branch
                        }
                    }
                }
            }
            return "";
        }

        // Voice-power SpellItem (shout word-combo) — return parent TESShout name.
        if (auto* spell = skyrim_cast<RE::SpellItem*>(a_form)) {
            if (spell->data.spellType == RE::MagicSystem::SpellType::kVoicePower) {
                auto* dh = RE::TESDataHandler::GetSingleton();
                if (dh) {
                    for (auto* shout : dh->GetFormArray<RE::TESShout>()) {
                        if (!shout) continue;
                        for (auto& variation : shout->variations) {
                            if (variation.spell == spell) {
                                return shout->GetName();
                            }
                        }
                    }
                }
                return spell->GetName();  // fallback if shout table lookup fails
            }
        }

        // Any other MagicItem (regular spell, direct TESShout lookup, etc.)
        if (auto* item = skyrim_cast<RE::MagicItem*>(a_form)) {
            return item->GetName();
        }

        return "";
    }

    // Displays "ActorName resisted SpellName." in the top-left HUD.
    // Uses a session-scoped set to coalesce duplicate notifications from
    // multiple hooks firing for the same hit into a single print.
    // cancelIfAlreadyQueued=true prevents re-showing while the message is visible.
    void NotifyResisted(const char* a_actorName, RE::TESForm* a_sourceForm)
    {
        const char* spellName = GetSpellDisplayName(a_sourceForm);
        if (!a_actorName || !a_actorName[0] || !spellName || !spellName[0]) {
            return;
        }
        static std::unordered_set<std::string> s_shown;
        std::string key = std::string(a_actorName) + "|" + spellName;
        if (!s_shown.insert(key).second) {
            return;  // already notified this session for this actor+spell pair
        }
        auto msg = std::string(a_actorName) + " resisted " + spellName + ".";
        RE::DebugNotification(msg.c_str(), nullptr, true);
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

    // Cached version of HasHostileEffect. Spell/shout hostility flags are
    // static at runtime, so the result is safe to cache for the session.
    // Called on every VME::Update tick (~60/s per active effect), so the
    // cache avoids repeated effect-list walks on the same spell form.
    bool IsParentSpellHostile(RE::MagicItem* a_item)
    {
        if (!a_item) {
            return false;
        }
        static std::unordered_map<RE::FormID, bool> s_cache;
        auto formID = a_item->GetFormID();
        auto [it, inserted] = s_cache.emplace(formID, false);
        if (inserted) {
            it->second = HasHostileEffect(a_item);
        }
        return it->second;
    }

    // Equivalent to the original mod's condition:
    //   GetFactionRelation(PlayerRef) == 2 (Ally), run on subject.
    // Walks the target's faction list and checks each faction's GROUP_REACTION
    // list for an kAlly reaction toward any faction the player belongs to.
    bool IsAllyToPlayer(RE::Actor* a_target, RE::PlayerCharacter* a_player)
    {
        auto* targetBase = a_target->GetActorBase();
        auto* playerBase = a_player->GetActorBase();
        if (!targetBase || !playerBase) {
            return false;
        }
        for (auto& targetFR : targetBase->factions) {
            auto* tFaction = targetFR.faction;
            if (!tFaction) continue;
            for (auto* reaction : tFaction->reactions) {
                if (!reaction || reaction->fightReaction != RE::FIGHT_REACTION::kAlly) continue;
                for (auto& playerFR : playerBase->factions) {
                    if (reaction->form == playerFR.faction) return true;
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

            // H: target is currently hostile toward the player
            const bool H = targetActor->IsHostileToActor(player);

            // S: target is a commanded actor (summon / raise / dominate)
            const bool S = targetActor->IsCommandedActor();

            // A: target has Ally faction relation to player
            const bool A = IsAllyToPlayer(targetActor, player);

            logger::trace("NOFF: player spell on '{}' H={} S={} A={} spell={}",
                targetActor->GetName(), H, S, A,
                a_data.magicItem ? a_data.magicItem->GetName() : "?");

            // Block when: !H && (S || A) && hostile spell
            if (!H && (S || A) && IsParentSpellHostile(a_data.magicItem)) {
                logger::trace("NOFF: blocked on ally/summon");
                NotifyResisted(targetActor->GetName(), a_data.magicItem);
                return false;  // drop the hit — effect never applied
            }

            // Neutral NPC hit by hostile spell: formula passes — let effect apply,
            // suppress hostility silently (no "resisted" notification).
            if (!H && IsParentSpellHostile(a_data.magicItem)) {
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
            auto base = REL::Module::get().base();
            REL::Relocation<std::uintptr_t> vtblActorPrimary{ RE::VTABLE_Actor[0] };
            auto slot260 = *reinterpret_cast<std::uintptr_t*>(vtblActorPrimary.address() + 260 * sizeof(void*));
            logger::info("NOFF: Actor vtable slot 260 = {:016X} (offset {:08X})", slot260, slot260 - base);

            // Hook all three classes that have their own MagicTarget vtable.
            // Character and PlayerCharacter don't inherit Actor's MagicTarget
            // vtable — each gets its own, all at the same index and slot.
            REL::Relocation<std::uintptr_t> vtblActor{ RE::VTABLE_Actor[kMagicTargetIdx] };
            func = vtblActor.write_vfunc(kAddTargetVfuncIdx, thunk);

            REL::Relocation<std::uintptr_t> vtblCharacter{ RE::VTABLE_Character[kMagicTargetIdx] };
            vtblCharacter.write_vfunc(kAddTargetVfuncIdx, thunk);

            REL::Relocation<std::uintptr_t> vtblPlayerCharacter{ RE::VTABLE_PlayerCharacter[kMagicTargetIdx] };
            vtblPlayerCharacter.write_vfunc(kAddTargetVfuncIdx, thunk);

            logger::debug("NOFF: image base            = {:016X}", base);
            logger::debug("NOFF: Actor::AddTarget      = {:016X} (offset {:08X})",
                func.address(), func.address() - base);

            logger::info("NOFF: MagicTarget::AddTarget hooked on Actor, Character, PlayerCharacter (idx {} vfunc {})",
                kMagicTargetIdx, kAddTargetVfuncIdx);

        }
    };

    // ── Hook 2: ValueModifierEffect::Update ──────────────────────────────────
    //
    // Catches concentration/beam spells (Lightning Storm, Flames, etc.) that
    // apply damage directly via ActiveEffect::Update, bypassing AddTarget.
    // Hooked via write_vfunc on VTABLE_ValueModifierEffect at slot 4.
    //
    // For allies/summons:  return without calling func (block damage entirely).
    // For neutral NPCs:    set g_suppressNextHitEvent, call func, reset flag —
    //                      relies on the downstream Character::sub chain
    //                      eventually calling our hooked BSTEventSource::SendEvent
    //                      and Actor_QueueHitTask.

    struct ValueModifierUpdateHook {
        static void thunk(RE::ActiveEffect* a_this, float a_delta)
        {
            auto* player = RE::PlayerCharacter::GetSingleton();
            if (!player) {
                return func(a_this, a_delta);
            }

            auto* caster = a_this->caster.get().get();
            if (caster != static_cast<RE::Actor*>(player)) {
                return func(a_this, a_delta);
            }

            auto* targetMT = a_this->target;
            auto* targetActor = targetMT ? skyrim_cast<RE::Actor*>(targetMT->GetTargetStatsObject()) : nullptr;
            if (!targetActor || targetActor == static_cast<RE::Actor*>(player)) {
                return func(a_this, a_delta);
            }

            // Skip enchantments
            if (a_this->spell && skyrim_cast<RE::EnchantmentItem*>(a_this->spell)) {
                return func(a_this, a_delta);
            }

            const bool H = targetActor->IsHostileToActor(player);
            const bool S = targetActor->IsCommandedActor();
            const bool A = IsAllyToPlayer(targetActor, player);

            logger::trace("NOFF: VME::Update on '{}' H={} S={} A={} spell={}",
                targetActor->GetName(), H, S, A,
                a_this->spell ? a_this->spell->GetName() : "?");

            if (!H && (S || A) && IsParentSpellHostile(a_this->spell)) {
                logger::trace("NOFF: VME::Update blocked on ally/summon");
                NotifyResisted(targetActor->GetName(), a_this->spell);
                return;
            }

            if (!H && IsParentSpellHostile(a_this->spell)) {
                logger::trace("NOFF: VME::Update suppressing for '{}'", targetActor->GetName());
                g_suppressNextHitEvent = true;
                func(a_this, a_delta);
                g_suppressNextHitEvent = false;
                return;
            }

            return func(a_this, a_delta);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            REL::Relocation<std::uintptr_t> vtbl{ RE::VTABLE_ValueModifierEffect[0] };
            func = vtbl.write_vfunc(4, thunk);
            logger::info("NOFF: ValueModifierEffect::Update hooked (slot 4)");
        }
    };

    // ── Hook 3: Actor vtable[0x820/8] — post-health-damage hostility notify ──
    //
    // Character::sub (AE 38468, 0x6B27A0) applies health damage then calls
    // vtable[0]+0x820 (AE 38606, slot 260) with the caster. That function
    // (func_0x0001406bc4a0, AE 38631) contains two separate branches:
    //   line 56: Actor::Combat_unk1(actor, 8)  — hostility trigger (param_3 > 0)
    //   line 96: Actor::Kill_impl2(...)         — kill (param_3 <= 0)
    //
    // We hook slot 260 as a flag-setter: when player→non-hostile, set
    // g_suppressNextHitEvent, call through, then clear the flag.
    // CombatUnk1Hook (below) reads the flag at line 56 and skips that call,
    // leaving Kill_impl2 at line 96 completely unaffected.

    struct HealthDamageNotifyHook {
        static void thunk(RE::Actor* a_target, RE::TESObjectREFR* a_caster, float a_damage)
        {
            auto* player = RE::PlayerCharacter::GetSingleton();
            if (player && a_caster == static_cast<RE::TESObjectREFR*>(player) &&
                !a_target->IsHostileToActor(player)) {
                logger::trace("NOFF: health-damage notify: setting flag for '{}'", a_target->GetName());
                g_suppressNextHitEvent = true;
                func(a_target, a_caster, a_damage);
                g_suppressNextHitEvent = false;
                return;
            }
            return func(a_target, a_caster, a_damage);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            constexpr std::size_t kSlot = 0x820 / sizeof(void*);  // 260

            REL::Relocation<std::uintptr_t> vtblActor{ RE::VTABLE_Actor[0] };
            func = vtblActor.write_vfunc(kSlot, thunk);

            REL::Relocation<std::uintptr_t> vtblCharacter{ RE::VTABLE_Character[0] };
            vtblCharacter.write_vfunc(kSlot, thunk);

            REL::Relocation<std::uintptr_t> vtblPlayerCharacter{ RE::VTABLE_PlayerCharacter[0] };
            vtblPlayerCharacter.write_vfunc(kSlot, thunk);

            logger::info("NOFF: health-damage notify hook installed (vtable[0] slot {})", kSlot);
        }
    };

    // ── Hook 3b: Actor::Combat_unk1 call site (func_0x0001406bc4a0, line 56) ──
    //
    // Actor::Combat_unk1(actor, 8) at offset 0x6BC620 is the call that sets the
    // NPC's combat state and makes IsHostileToActor return true. It lives on the
    // param_3 > 0 branch of func_0x0001406bc4a0 (i.e. only when the actor is still
    // alive after taking damage). Kill_impl2 is on the param_3 <= 0 branch at
    // line 96 — a completely separate path not touched by this hook.
    //
    // When HealthDamageNotifyHook sets g_suppressNextHitEvent, we skip this call,
    // leaving the kill path intact.

    struct CombatUnk1Hook {
        static void thunk(RE::Actor* a_actor, std::uint32_t a_param2)
        {
            if (g_suppressNextHitEvent) {
                logger::trace("NOFF: Combat_unk1 suppressed for '{}'", a_actor ? a_actor->GetName() : "?");
                return;
            }
            logger::trace("NOFF: Combat_unk1 passthrough for '{}' param2={}", a_actor ? a_actor->GetName() : "?", a_param2);
            return func(a_actor, a_param2);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // CALL to Actor::Combat_unk1 inside the health-damage notify function.
            // AE: ID 38631 (RVA 0x6BC4A0), call site +0x180.
            // SE 1.5.97: Character::sub (RVA 0x62A530), call site +0x16D = RVA 0x62A69D.
            //   Note: SE Combat_unk1 takes 4 params; suppress path is unaffected,
            //   passthrough relies on R8/R9 being preserved (valid if no trace logging).
            std::uintptr_t addr;
            if (REL::Module::IsAE()) {
                addr = REL::Relocation<std::uintptr_t>{ REL::ID(38631), 0x180 }.address();
            } else {
                addr = REL::Module::get().base() + 0x62A69D;
            }
            func = SKSE::GetTrampoline().write_call<5>(addr, reinterpret_cast<std::uintptr_t>(thunk));
            logger::info("NOFF: Combat_unk1 hook installed at {:016X}", addr);
        }
    };

    // ── Hook 5: Hit-event broadcast (AddTarget path) ─────────────────────────
    //
    // BSTEventSource<TESHitEvent>::SendEvent call site inside Actor::AddTarget
    // (offset 0x6C533B, AE 1.6.1170). Covers direct-hit projectile spells
    // (Ice Spike, Firebolt) and concentration beams (Flames, Lightning Storm
    // initial tick). Skipped when g_suppressNextHitEvent is set by AddTargetHook.

    struct HitEventHook {
        static void thunk(void* a_eventSource, void* a_event)
        {
            if (g_suppressNextHitEvent) {
                logger::trace("NOFF: hit-event suppressed");
                return;
            }
            logger::trace("NOFF: hit-event passthrough");
            return func(a_eventSource, a_event);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // BSTEventSource<TESHitEvent>::SendEvent inside Actor::AddTarget (ID 38786).
            // AE: ID 38786 (RVA 0x6C50A0), call site +0x29B.
            // SE 1.5.97: pending Ghidra offset mapping — skipped for now.
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: HitEventHook skipped on SE (SE offset pending)");
                return;
            }
            REL::Relocation<std::uintptr_t> target{ REL::ID(38786), 0x29B };
            func = SKSE::GetTrampoline().write_call<5>(target.address(), reinterpret_cast<std::uintptr_t>(thunk));
            logger::info("NOFF: hit-event hook installed at {:016X}", target.address());
        }
    };

    // ── Hook 5b: TESObjectREFR::sub (Explosion_ApplyEffects, post-SendEvent) ──
    //
    // Called at offset 0x7D16E2 inside Explosion_ApplyEffects for CHARACTER targets
    // (non-player), AFTER the TESHitEvent SendEvent. It applies the explosion impact
    // to the actor (hit reaction, combat start, etc.). For player→non-hostile targets
    // this is what internally triggers Actor::StartCombat, making IsHostileToActor
    // return true ~13ms later despite all TESHitEvent hooks firing correctly.

    struct ExplosionActorHitHook {
        static void thunk(RE::Actor* a_target, void* a_hitData)
        {
            // g_suppressNextHitEvent is set by ExplosionHitEventHook when the
            // cause is the player and target is non-hostile — both hooks fire
            // within the same Explosion_ApplyEffects loop iteration.
            if (g_suppressNextHitEvent) {
                g_suppressNextHitEvent = false;
                logger::trace("NOFF: explosion actor-hit suppressed for '{}'", a_target ? a_target->GetName() : "?");
                return;
            }
            logger::trace("NOFF: explosion actor-hit passthrough for '{}'", a_target ? a_target->GetName() : "?");
            return func(a_target, a_hitData);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // TESObjectREFR::sub inside Explosion_ApplyEffects (ID 43849).
            // AE: ID 43849 (RVA 0x7D12D0), call site +0x412.
            // SE 1.5.97: pending Ghidra offset mapping — skipped for now.
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: ExplosionActorHitHook skipped on SE (SE offset pending)");
                return;
            }
            REL::Relocation<std::uintptr_t> target{ REL::ID(43849), 0x412 };
            func = SKSE::GetTrampoline().write_call<5>(target.address(), reinterpret_cast<std::uintptr_t>(thunk));
            logger::info("NOFF: explosion actor-hit hook installed at {:016X}", target.address());
        }
    };

    // ── Hook 6: Hit-event broadcast (Explosion_ApplyEffects path) ────────────
    //
    // BSTEventSource<TESHitEvent>::SendEvent call site inside Explosion_ApplyEffects
    // (offset 0x7D15BD, AE 1.6.1170). This is the path taken by Fireball's explosion
    // and Lightning Storm's bolt-node — both bypass AddTarget entirely.
    // Unlike the AddTarget path, this function has no hostility check before
    // dispatching the event, so guards are notified unconditionally.
    //
    // The TESHitEvent stack struct at a_event: [target NiPointer][cause NiPointer][...]
    // We read cause and target directly and suppress if player→non-hostile.

    struct ExplosionHitEventHook {
        static void thunk(void* a_eventSource, RE::TESHitEvent* a_event)
        {
            if (a_event) {
                auto* player = RE::PlayerCharacter::GetSingleton();
                if (player) {
                    auto* cause  = a_event->cause.get();
                    auto* target = a_event->target.get();
                    auto* causeActor  = cause  ? skyrim_cast<RE::Actor*>(cause)  : nullptr;
                    auto* targetActor = target ? skyrim_cast<RE::Actor*>(target) : nullptr;
                    if (causeActor == static_cast<RE::Actor*>(player) &&
                        targetActor && !targetActor->IsHostileToActor(player)) {
                        // Set flag so ExplosionActorHitHook (fired later in
                        // the same loop iteration) also suppresses.
                        g_suppressNextHitEvent = true;
                        return func(a_eventSource, a_event);
                    }
                    logger::trace("NOFF: explosion hit-event passthrough for '{}'", targetActor ? targetActor->GetName() : "?");
                }
            }
            return func(a_eventSource, a_event);
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // BSTEventSource<TESHitEvent>::SendEvent inside Explosion_ApplyEffects (ID 43849).
            // AE: ID 43849 (RVA 0x7D12D0), call site +0x2ED.
            // SE 1.5.97: pending Ghidra offset mapping — skipped for now.
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: ExplosionHitEventHook skipped on SE (SE offset pending)");
                return;
            }
            REL::Relocation<std::uintptr_t> target{ REL::ID(43849), 0x2ED };
            func = SKSE::GetTrampoline().write_call<5>(target.address(), reinterpret_cast<std::uintptr_t>(thunk));
            logger::info("NOFF: explosion hit-event hook installed at {:016X}", target.address());
        }
    };

    // ── Hook 7: Hit-task dispatch ────────────────────────────────────────────
    //
    // Actor_QueueHitTask call site inside Actor::AddTarget (offset 0x6C5413,
    // AE 1.6.1170). Queues the fUnk_Attacked task (0x62) that notifies
    // combat AI and causes the NPC to personally turn hostile.
    // Skipped when g_suppressNextHitEvent is set by AddTargetHook.

    struct HitTaskHook {
        static void thunk(void* a_taskPool, RE::Actor* a_target, RE::TESObjectREFR* a_caster, void* a_spell, std::uint32_t a_param5)
        {
            logger::trace("NOFF: hit-task enter target='{}' suppress={}", a_target ? a_target->GetName() : "?", g_suppressNextHitEvent);
            if (g_suppressNextHitEvent) {
                logger::trace("NOFF: hit-task suppressed (flag)");
                return;
            }
            // Also suppress when player casts on a non-hostile target — covers
            // paths that bypass AddTarget (e.g. Projectile_OnActorHit → MagicTarget::Func1).
            auto* player = RE::PlayerCharacter::GetSingleton();
            const bool casterIsPlayer = player && a_caster == static_cast<RE::TESObjectREFR*>(player);
            const bool targetHostile   = a_target && player && a_target->IsHostileToActor(player);
            logger::trace("NOFF: hit-task direct-check: casterIsPlayer={} targetHostile={} caster={}",
                casterIsPlayer, targetHostile,
                a_caster ? a_caster->GetFormType() : RE::FormType::None);
            if (casterIsPlayer && a_target && !targetHostile) {
                logger::trace("NOFF: hit-task suppressed (direct) for '{}'", a_target->GetName());
                return;
            }
            logger::trace("NOFF: hit-task calling func");
            func(a_taskPool, a_target, a_caster, a_spell, a_param5);
            logger::trace("NOFF: hit-task func returned");
        }

        static inline REL::Relocation<decltype(thunk)> func;

        static void Install()
        {
            // Actor_QueueHitTask call site inside Actor::AddTarget (ID 38786).
            // AE: ID 38786 (RVA 0x6C50A0), call site +0x373.
            // SE 1.5.97: pending Ghidra offset mapping — skipped for now.
            // Must use write_call (E8) not write_branch (E9) — original is a CALL,
            // and JMP would misalign the stack by 8, crashing on movaps in the thunk.
            if (!REL::Module::IsAE()) {
                logger::warn("NOFF: HitTaskHook skipped on SE (SE offset pending)");
                return;
            }
            REL::Relocation<std::uintptr_t> target{ REL::ID(38786), 0x373 };
            func = SKSE::GetTrampoline().write_call<5>(target.address(), reinterpret_cast<std::uintptr_t>(thunk));

            auto base = REL::Module::get().base();
            logger::info("NOFF: hit-task hook installed at {:016X} (offset {:08X})", target.address(), target.address() - base);
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

    log->set_level(spdlog::level::info);
    log->flush_on(spdlog::level::info);

    spdlog::set_default_logger(std::move(log));
}

SKSEPluginLoad(const SKSE::LoadInterface* a_skse)
{
    SKSE::Init(a_skse);
    InitLogger();

    auto* plugin = SKSE::PluginDeclaration::GetSingleton();
    logger::info("NOFF v{} loading", plugin->GetVersion());

    SKSE::AllocTrampoline(70);  // 14 per write_call<5> × 5 hooks

    SKSE::GetMessagingInterface()->RegisterListener([](SKSE::MessagingInterface::Message* msg) {
        if (msg->type == SKSE::MessagingInterface::kDataLoaded) {
            AddTargetHook::Install();
            ValueModifierUpdateHook::Install();
            HealthDamageNotifyHook::Install();
            CombatUnk1Hook::Install();
            HitEventHook::Install();
            ExplosionActorHitHook::Install();
            ExplosionHitEventHook::Install();
            HitTaskHook::Install();
        }
    });

    return true;
}
