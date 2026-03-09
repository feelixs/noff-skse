# NOFF — No Offensive Friendly Fire

NOFF is an SKSE plugin for Skyrim AE 1.6.1170 that prevents player-cast spells and enchantments from damaging allied/summoned actors or triggering NPC hostility from accidental hits.

---

## Decision Logic

```
P = spell cast by the player
H = target is currently hostile to the player
S = target is a commanded actor (summon / raise dead / dominate)
A = target has Ally faction reaction toward the player
```

| Condition | Result |
|---|---|
| `!P` | Pass through — not a player spell |
| `P && H` | Pass through — target is already hostile |
| `P && !H && (S \|\| A) && hostile spell` | **Block** — effect never applies |
| `P && !H && !(S \|\| A) && hostile spell` | Allow effect, **suppress combat trigger** |
| `P && !H && non-hostile spell` | Pass through — no combat trigger anyway |

"Hostile spell" means any spell/enchantment where at least one magic effect has the `IsHostile` flag set (`IsParentSpellHostile`). Results are cached per `FormID`.

**Block** shows a HUD notification: `"[Actor] resisted [Spell]."` Duplicate notifications are coalesced.

**Ally** (`A`) is determined by walking the target's faction list and checking for a `kAlly` group combat reaction toward any faction the player belongs to — equivalent to the original Papyrus mod's `GetFactionRelation(PlayerRef) == 2`.

**Commanded** (`S`) uses `Actor::IsCommandedActor()`.

---

## Scope

- Suppresses aggression **on hit only** — kills can still generate witness reactions and murder bounty normally.
- Covers spells, shouts, enchanted weapons, and staves.
- Does not affect NPC-cast spells.

---

## Hook Inventory

All offsets are for AE 1.6.1170 (`SkyrimSE.exe`).

### 1 — `MagicTarget::AddTarget` (vtable hook, slot 1)

Patched on `Actor`, `Character`, and `PlayerCharacter` vtables.

The engine calls this to apply any magic effect to a target. This is the primary decision point:

- Returns `false` to drop the effect entirely for blocked targets (allies/summons).
- Sets `g_suppressNextHitEvent`, calls through, then clears the flag for neutral NPC hits.

Covers: direct-hit projectile spells, concentration beams, touch spells, staves, weapon enchantments.

### 2 — `ValueModifierEffect::Update` (vtable hook, slot 4)

Patched on `VTABLE_ValueModifierEffect[0]`.

Concentration spells (Flames, Lightning Storm) re-apply their value modifier every frame (~60/s). `AddTarget` only fires on the first tick, so this hook enforces the block/suppress logic on every subsequent tick.

### 3a — `Actor` vtable slot 260 — `HealthDamageNotify` (vtable hook)

Patched on `Actor`, `Character`, and `PlayerCharacter` vtables.

Called when an actor takes health damage from any source. For player→non-hostile hits, sets `g_suppressNextHitEvent` around the call so that `CombatUnk1Hook` (below) can suppress the combat state change.

### 3b — `Actor::Combat_unk1` call site (offset `0x6BC620`)

`write_call<5>` hook inside `func_0x0001406bc4a0`.

`Actor::Combat_unk1(actor, 8)` is the call that sets the NPC's combat state and makes `IsHostileToActor` return true. It lives on the "actor survived" branch of the damage handler. The kill branch (`Kill_impl2`) is a separate path and is not affected.

When `g_suppressNextHitEvent` is set by `HealthDamageNotifyHook`, this call is skipped — the NPC takes damage but never enters combat.

### 4 — `BSTEventSource<TESHitEvent>::SendEvent` call site in `AddTarget` (offset `0x6C533B`)

`write_call<5>` hook.

Fires inside `Actor::AddTarget` after the effect is applied. Checks `g_suppressNextHitEvent` and skips the call if set. This prevents the hit event broadcast for the `AddTarget` code path.

> **Note:** Investigation confirmed that the two registered `TESHitEvent` sinks at runtime are the engine's Papyrus `OnHit` relay and an SKSE plugin (`inertia`). Neither is a direct hostility trigger. The actual hostility suppression comes from hooks 3a/3b above. Hook 4 suppresses the `TESHitEvent` broadcast purely to avoid Papyrus `OnHit` firing on suppressed hits.

### 5a — `TESObjectREFR::sub` call site in `Explosion_ApplyEffects` (offset `0x7D16E2`)

`write_call<5>` hook.

Called inside `Explosion_ApplyEffects` for character targets after the hit event. This is what triggers `Actor::StartCombat` for explosion-type spells (Fireball, etc.), making `IsHostileToActor` return true despite other hooks. Suppressed when `g_suppressNextHitEvent` is set by hook 5b.

### 5b — `BSTEventSource<TESHitEvent>::SendEvent` call site in `Explosion_ApplyEffects` (offset `0x7D15BD`)

`write_call<5>` hook.

Explosion spells bypass `AddTarget` and go directly through `Explosion_ApplyEffects`. This hook detects player→non-hostile hits, sets `g_suppressNextHitEvent` (for hook 5a), and calls through so Papyrus `OnHit` still fires.

### 6 — `Actor_QueueHitTask` call site in `AddTarget` (offset `0x6C5413`)

`write_call<5>` hook.

Queues the combat AI task that causes an NPC to personally turn hostile. Suppressed either via the `g_suppressNextHitEvent` flag or via a direct player→non-hostile check as a fallback.

---

## Flag Coordination

`g_suppressNextHitEvent` is a plain `static bool`. It is set and cleared within a single call frame. Game magic processing is single-threaded, so no synchronisation is needed.

---

## AE Only

Hooks 3b, 4, 5a, 5b, and 6 use hardcoded AE 1.6.1170 offsets and are skipped with a log warning on SE. Hooks 1, 2, and 3a use CommonLibSSE vtable IDs and work on all versions.


---

Created by feelixs (@hesmick on nexusmods) and Claude Code
