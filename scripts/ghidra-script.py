# NOFF - Analyze Actor::SendAssaultAlarm for hooking
#
# We already know:
#   - Actor::SendAssaultAlarm @ 0x1406703B0 (AE 1.6.1170)
#   - Signature: void(Actor* this, Actor* attacker, bool flag)
#   - Two callers: FUN_1406df3a0, FUN_1406df420
#
# This script gathers:
#   1. All functions near SendAssaultAlarm to find the AE address-library ID
#   2. Tail-call target (0x140670410) disassembly
#   3. Full disassembly of both caller functions

import time

t0 = time.time()
def ts():
    return "[{:.1f}s]".format(time.time() - t0)

BASE = 0x140000000

addr_factory = currentProgram.getAddressFactory()
func_manager = currentProgram.getFunctionManager()
listing      = currentProgram.getListing()
sym_table    = currentProgram.getSymbolTable()
ref_manager  = currentProgram.getReferenceManager()

def to_addr(va):
    try:
        return addr_factory.getAddress("0x{:x}".format(va))
    except Exception:
        return None

def label_at(va):
    a = to_addr(va)
    if not a:
        return None
    sym = sym_table.getPrimarySymbol(a)
    return sym.getName(True) if sym else None

def dump_disasm(va, max_insn=60):
    func = func_manager.getFunctionAt(to_addr(va))
    if not func:
        func = func_manager.getFunctionContaining(to_addr(va))
    if not func:
        print("    (could not resolve function)")
        return
    print("    Name: {}".format(func.getName(True)))
    body = func.getBody()
    it = listing.getInstructions(to_addr(va), True)
    n = 0
    while it.hasNext() and n < max_insn:
        insn = it.next()
        if not body.contains(insn.getAddress()):
            break
        a = int(str(insn.getAddress()), 16)
        lbl = label_at(a)
        prefix = "    "
        # Mark call targets
        if insn.getFlowType().isCall():
            for ref in ref_manager.getReferencesFrom(insn.getAddress()):
                if ref.getReferenceType().isCall():
                    tgt = int(str(ref.getToAddress()), 16)
                    tgt_lbl = label_at(tgt)
                    if tgt_lbl:
                        prefix = "    ; -> {}  \n    ".format(tgt_lbl)
        print("{}0x{:X}  {}".format(prefix, a, insn))
        n += 1

SEND_ASSAULT_VA = 0x1406703B0

# ── 1. Functions near SendAssaultAlarm for AE ID cross-reference ─────────────
print("=" * 70)
print("{} Step 1: Functions near SendAssaultAlarm".format(ts()))
print("  (StealAlarm AE ID=37422 @ 0x14066F320 for reference)")
print("  SendAssaultAlarm offset from base: 0x{:X}".format(SEND_ASSAULT_VA - BASE))

SCAN_START = 0x14066F000
SCAN_END   = 0x140672000

func_iter = func_manager.getFunctions(to_addr(SCAN_START), True)
while func_iter.hasNext():
    f = func_iter.next()
    entry = int(str(f.getEntryPoint()), 16)
    if entry >= SCAN_END:
        break
    name = f.getName(True)
    marker = " <<< SendAssaultAlarm" if entry == SEND_ASSAULT_VA else ""
    print("    0x{:X}  offset=0x{:X}  {}{}".format(entry, entry - BASE, name, marker))

# ── 2. Tail-call target disassembly ──────────────────────────────────────────
print("\n" + "=" * 70)
TAIL_VA = 0x140670410
print("{} Step 2: Tail-call target @ 0x{:X}".format(ts(), TAIL_VA))
dump_disasm(TAIL_VA, 40)

# ── 3. Caller disassembly ────────────────────────────────────────────────────
print("\n" + "=" * 70)
print("{} Step 3: Disassembly of SendAssaultAlarm callers".format(ts()))

for caller_va, caller_name in [(0x1406DF3A0, "FUN_1406df3a0"), (0x1406DF420, "FUN_1406df420")]:
    print("\n  --- {} @ 0x{:X} ---".format(caller_name, caller_va))
    dump_disasm(caller_va, 80)

print("\n{} Done.".format(ts()))
