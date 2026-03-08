# Game Logic Trace — Spell Hit Hostility Paths

This document traces the call order for each spell type as observed via Ghidra
decompilation, log analysis, and hook testing. Indentation = call depth.
Hook points are marked with [HOOK]. Addresses are AE 1.6.1170 image-relative offsets.

---

## Mod scope

NOFF suppresses aggression **on hit** only. If the player actually kills a non-hostile
NPC, the vanilla murder crime system (bounty, guard hostility) is intentionally left
intact. Only the "you hit me, now I attack you" reaction is suppressed.

---

## Shared downstream paths

These functions appear across multiple spell types and are referenced below.

```
Character::sub (AE 38468, offset 0x6B27A0)
│   Applies health AV damage to the target.
│   Then calls vtable[0]+0x820 on the target actor.
│
└── Actor vtable[0] slot 260 (0x820/8) (AE 38606, offset 0x6B9950)  [HOOK: HealthDamageNotifyHook]
    │   Receives (target, caster, damage).
    │   Sets g_suppressNextHitEvent=true when player→non-hostile, calls through, then clears flag.
    │   Critically: does NOT skip the call — lets Kill_impl2 proceed normally.
    │
    └── func_0x0001406bc4a0 (AE 38631)
        ├── Actor::Combat_unk1(actor, 8) @ 0x6BC620  [HOOK: CombatUnk1Hook]
        │       Starts combat / marks aggressor. Suppressed via g_suppressNextHitEvent flag.
        │       NOTE: this hook only fires when func_0x0001406bc4a0's outer condition passes,
        │       which is blocked for AI actors (Lami etc) — so this hook rarely fires in practice.
        │       Combat_unk1 for dying AI actors comes from character_sub2 @ 0x667C50 instead.
        │
        └── Actor::Kill_impl2              — kills actor if health <= 0. NOT suppressed.
            └── FUN_140655640 (async death task, via gBSTaskPool)
                └── Character::sub(actor, 1) @ 0x65571A
                        Murder crime / witness notification. NOT hooked —
                        kills intentionally generate bounty/guard reaction.

MagicTarget::Func1 (called from inside MagicTarget::AddTarget)
│   Applies a magic effect to an actor and signals combat systems.
│
├── BSTEventSource<TESHitEvent>::SendEvent (call site offset 0x6C533B)  [HOOK: HitEventHook]
│       Notifies crime witnesses (guards, NPCs) that the target was hit.
│
└── Actor_QueueHitTask (call site offset 0x6C5413)  [HOOK: HitTaskHook]
        Queues task 0x62 (fUnk_Attacked) on the target NPC.
        This task tells the NPC itself "you were attacked, react/turn hostile."
```

---

## Spell type traces

### Flames (concentration beam, no explosion)

Every ~16ms per active target:

```
ValueModifierEffect::Update (VTABLE_ValueModifierEffect[0] slot 4)  [HOOK: ValueModifierUpdateHook]
│   Per-tick damage for beam/concentration spells. Sets g_suppressNextHitEvent
│   before calling func so downstream HitEventHook and HitTaskHook suppress.
│
└── Character::sub
    └── vtable slot 260  [HOOK: HealthDamageNotifyHook]

MagicTarget::AddTarget (VTABLE_Actor[4] slot 1)  [HOOK: AddTargetHook]
│   Also fires each tick. Sets g_suppressNextHitEvent before calling func.
│
└── MagicTarget::Func1
    ├── BSTEventSource::SendEvent @ 0x6C533B  [HOOK: HitEventHook — suppressed via flag]
    └── Actor_QueueHitTask @ 0x6C5413         [HOOK: HitTaskHook  — suppressed via flag]
```

Fire Storm (AoE) also follows this path and was confirmed NOT to trigger guard
reaction, consistent with these hooks being sufficient for non-explosion spells.

---

### Ice Spike / Firebolt (single projectile, no explosion)

On projectile impact:

```
Projectile_OnActorHit (offset 0x7EC640)
│   Handles actor-hit logic for direct projectiles.
│   Has built-in guard: func_0x000140400780(target, projectile).
│   Despite earlier assumption, this guard PASSES for player-cast bolts on
│   neutral NPCs — confirmed by logs showing ProjectileOnActorHitEventHook firing.
│
├── BSTEventSource::SendEvent @ 0x7EC772  [HOOK: ProjectileOnActorHitEventHook]
│       Notifies witnesses.
│
└── (leads into MagicTarget::Func1 path)
    ├── BSTEventSource::SendEvent @ 0x6C533B  [HOOK: HitEventHook]
    └── Actor_QueueHitTask @ 0x6C5413         [HOOK: HitTaskHook]

Projectile_HandleImpact (offset 0x7ECD80)
│   Handles visual/audio impact AND sends a separate TESHitEvent.
│
└── BSTEventSource::SendEvent @ 0x7ED0D7  [HOOK: ProjectileHitEventHook]
```

---

### Lightning Storm bolt / Fireball (projectile + explosion)

These spells create a projectile that hits an actor directly, then detonates
and processes all actors in blast radius through Explosion_ApplyEffects.

#### Phase 1 — Direct projectile hit (actor the bolt/ball impacts first)

```
Projectile_OnActorHit (offset 0x7EC640)
├── BSTEventSource::SendEvent @ 0x7EC772  [HOOK: ProjectileOnActorHitEventHook]
└── → MagicTarget::Func1
    ├── BSTEventSource::SendEvent @ 0x6C533B  [HOOK: HitEventHook]
    └── Actor_QueueHitTask @ 0x6C5413         [HOOK: HitTaskHook]

Projectile_HandleImpact (offset 0x7ECD80)
└── BSTEventSource::SendEvent @ 0x7ED0D7  [HOOK: ProjectileHitEventHook]
```

#### Phase 2 — Explosion radius (all actors in blast, including first-hit actor again)

```
Explosion_ApplyEffects (offset 0x7D12D0)
│   Iterates over all actors in the blast radius in a do-while loop.
│   For each actor (skips dead/disabled via flag checks at +0x144):
│
├── [if damage > 0]
│   │
│   ├── [if target is a Character ('>' type at +0x1A offset)]
│   │   └── Character::sub(target)                    ← line 105, fires BEFORE SendEvent
│   │       └── vtable slot 260  [HOOK: HealthDamageNotifyHook]
│   │           Suppressed here when H=false. This is the damage application.
│   │
│   ├── [setup TESHitEvent struct on stack]
│   │   Layout: [target NiPtr @ +0x00][cause NiPtr @ +0x08]
│   │           [sourceFormID @ +0x10][projectileFormID @ +0x14][HitFlags @ +0x18]
│   │
│   ├── BSTEventSource::SendEvent(0x1420f7c68, &event) @ 0x7D15BD  [HOOK: ExplosionHitEventHook]
│   │       Notifies witnesses. When suppressed (player→non-hostile):
│   │       sets g_suppressNextHitEvent=true so the actor-hit hook below also fires.
│   │
│   └── [else branch — for Character targets only, i.e. any NPC like Teeba-Ei]
│       │   This entire block runs AFTER the SendEvent above.
│       │
│       ├── func_0x0001407d2fb0(explosion, &posData)
│       │       Unknown purpose. When it returns non-zero the rest of this block runs.
│       │       Observed to return non-zero for Lightning Storm bolt explosions.
│       │
│       ├── func_0x0001407db590(hitData, caster, target, explosion, damage)
│       │       Builds a hit-data struct (position, damage, impact type, etc.)
│       │
│       ├── TESObjectREFR::sub(target, hitData) @ 0x7D16E2  [HOOK: ExplosionActorHitHook]
│       │       Applies the explosion impact to the actor. Internally calls
│       │       Actor::StartCombat or equivalent — this was confirmed as the
│       │       mechanism that makes IsHostileToActor return true ~13ms after
│       │       the SendEvent fires, even when SendEvent is suppressed.
│       │       Reads g_suppressNextHitEvent; if set, skips call and clears flag.
│       │
│       ├── [MagicCaster spell application, line 213-216]
│       │   Calls vtable[0x2e0/8](caster, 3) → get MagicCaster for slot 3.
│       │   Then calls vtable[0x8/8](magicCaster, spellData, 0, target, power, ...).
│       │   Likely applies the explosion's secondary magic effect to the target.
│       │   → probably routes through MagicTarget::AddTarget  [HOOK: AddTargetHook]
│       │
│       └── vtable[0x4C8/8](target, 1)  — unknown; some bool query on the target actor.
│           Return value determines animation/visual branch (stagger vs. visual update).
```

#### g_suppressNextHitEvent flag lifecycle for the explosion path

```
ExplosionHitEventHook fires:
    cause == player, target not hostile
    → g_suppressNextHitEvent = true
    → return (SendEvent suppressed, witnesses never notified)

[Explosion_ApplyEffects continues executing for this actor]

ExplosionActorHitHook fires (same loop iteration, ~0–5ms later):
    g_suppressNextHitEvent == true
    → g_suppressNextHitEvent = false   (cleared here)
    → return (TESObjectREFR::sub suppressed, combat start blocked)

[Loop advances to next actor; flag is clear]
```

---

## Hook inventory (as of current build)

| Hook | Address | Purpose | Needed? |
|------|---------|---------|---------|
| AddTargetHook | vtable Actor/Char/PC [4] slot 1 | Sets flag for player→non-hostile spell hits via AddTarget path | YES |
| ValueModifierUpdateHook | VTABLE_ValueModifierEffect[0] slot 4 | Sets flag for concentration/beam per-tick damage (Flames etc) | YES |
| HealthDamageNotifyHook | vtable[0] slot 260 (0x6B9950) | Sets flag, calls through (lets Kill_impl2 run) | YES |
| CombatUnk1Hook | call site 0x6BC620 | Suppresses combat-state-change from damage notify. Rarely fires for AI actors. | MAYBE — log shows it fires for Lami once she's near death |
| HitEventHook | call site 0x6C533B | Suppresses TESHitEvent witness notification (AddTarget path) | YES |
| HitTaskHook | call site 0x6C5413 | Suppresses fUnk_Attacked task that makes NPC personally hostile | YES |
| ExplosionHitEventHook | call site 0x7D15BD | Suppresses explosion TESHitEvent, sets flag for ExplosionActorHitHook | YES (explosion path) |
| ExplosionActorHitHook | call site 0x7D16E2 | Suppresses actor-hit function that starts combat inside explosion loop | YES (explosion path) |
| ProjectileOnActorHitEventHook | call site 0x7EC772 | Suppresses TESHitEvent from Projectile_OnActorHit | YES (projectile path) |
| ProjectileHitEventHook | call site 0x7ED0D7 | Suppresses TESHitEvent from Projectile_HandleImpact | YES (projectile path) |
| ~~KillWitnessNotifyHook~~ | ~~call site 0x65571A~~ | ~~Suppresses murder crime / kill witness notify~~ | REMOVED — out of scope; kills generate bounty normally |

## Known issues / open questions

- **g_suppressNextHitEvent race condition**: Plain `bool`, no atomics, no
  critical section. Concurrent Lightning Storm ticks on different threads could
  produce flag-state races. Not yet confirmed as causing observable failures.

- **TESObjectREFR::sub suppression may also suppress stagger/animation**:
  The call at 0x7D16E2 handles more than just combat start. Suppressing it for
  player→non-hostile may prevent hit-reaction animations on affected NPCs.
  Needs verification.
