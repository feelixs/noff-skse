# NOFF — How It Works

NOFF (No Offensive Friendly Fire) is an SKSE plugin that prevents player-cast spells from triggering NPC hostility or damaging allied/summoned actors.

## Decision Logic

```
P = spell cast by the player
H = target is currently hostile to the player
S = target is a commanded actor (summon / raise dead / dominate)
A = target has an Ally faction reaction toward the player
```

| Condition       | Result                                    |
|-----------------|-------------------------------------------|
| !P              | Pass through — not a player spell         |
| P && H          | Pass through — target is already hostile  |
| P && !H && S    | **Block** — don't hit your summons        |
| P && !H && A    | **Block** — don't hit your allies         |
| P && !H && !S && !A, hostile spell | Apply effect, **suppress combat trigger** |
| P && !H && !S && !A, non-hostile spell | Pass through — no combat trigger anyway |

## The Two Hooks

### Hook 1 — `MagicTarget::AddTarget` (vtable hook)

This is the function the engine calls to apply a magic effect to a target. It is virtual and overridden by `Actor`, `Character`, and `PlayerCharacter`, so we patch all three vtable entries.

**What it does:**
- Identifies the target as an Actor and checks whether the caster is the player.
- For player spells on allied/commanded targets: returns `false` to drop the effect entirely — it never applies.
- For player spells on non-hostile targets with hostile effects: sets a thread-local flag (`g_suppressNextHitEvent`), calls the original `AddTarget` so the effect applies normally, then clears the flag.

### Hook 2 — Hit-event dispatch (`FUN_1406be880`, AE ID 38668)

This function is called from inside `AddTarget` after the effect is applied. It dispatches a "hit event" to the game's combat AI, which is what causes an NPC to turn hostile toward the caster.

The function is guarded inside `AddTarget` by a `kNoHitEvent` flag check on the `EffectSetting` — hostile spells generally do NOT have that flag, so they reach this call.

**What it does:**
- Checks `g_suppressNextHitEvent`. If set, skips the original call entirely — the AI is never notified of the hit.
- Otherwise, calls the original function normally.

Because game logic is single-threaded, it is safe to use a plain `bool` flag that is set and cleared within a single call frame.

## What Is and Isn't Affected

| Scenario | Result |
|---|---|
| Player casts fire spell at neutral NPC | Damage applies, NPC stays neutral |
| Player casts healing spell at any NPC | Unchanged (non-hostile effect, no combat trigger anyway) |
| Player casts fire spell at hostile enemy | Unchanged (hook passes through when `H = true`) |
| Player's summon / zombie takes a player spell | Effect is **blocked entirely** |
| Player's follower (Ally faction) takes a player spell | Effect is **blocked entirely** |
| NPC casts a spell at the player | Unchanged (hook only fires for player casters) |
| Player hits with a melee weapon | Unchanged (not magic, AddTarget not involved) |
| Player fires a weapon enchantment | Unchanged (enchantments are explicitly skipped) |

## Discovering the Hook Point

Finding `FUN_1406be880` required several rounds of Ghidra analysis:

1. Searched for all uses of the `kHostile` flag (`TEST byte [reg+0x68], 0x01`) — found only in unrelated 3D/physics code.
2. Found that `MagicTarget::AddTarget` (vtable slot 1) was stored as data in Ghidra, not analyzed as code. After forcing disassembly we recovered the full 977-byte function.
3. Traced the function flow and found the hit-event dispatch call at offset `+0x29B`, gated by a `kNoHitEvent` check.
4. Confirmed `FUN_1406be880` (AE ID 38668) is the function that notifies the combat AI.

## AE vs SE

Hook 1 uses CommonLibSSE vtable IDs and works on all versions.

Hook 2 currently only installs on AE (ID 38668). The SE equivalent ID is not yet known. On SE the hook is skipped with a log warning.
