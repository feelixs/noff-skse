# NOFF - Trace MagicTarget::AddTarget internals
#
# We found the vtable addresses for Actor and Character's MagicTarget segment.
# AddTarget is slot 1 (offset +8) in the MagicTarget vtable.
# This script reads the actual AddTarget function pointer from the vtable,
# then dumps all calls it makes to find the combat initiation path.

import time

t0 = time.time()
def ts():
    return "[{:.1f}s]".format(time.time() - t0)

addr_factory = currentProgram.getAddressFactory()
sym_table    = currentProgram.getSymbolTable()
ref_manager  = currentProgram.getReferenceManager()
func_manager = currentProgram.getFunctionManager()
listing      = currentProgram.getListing()
memory       = currentProgram.getMemory()

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

def read_pointer(va):
    """Read an 8-byte pointer from the given VA."""
    addr = to_addr(va)
    if not addr:
        return None
    try:
        jb = getBytes(addr, 8)
        val = 0
        for i in range(8):
            val |= (jb[i] & 0xFF) << (i * 8)
        return val
    except Exception:
        return None

def get_calls_in_function(func):
    calls = []
    addr_set = func.getBody()
    insn_iter = listing.getInstructions(addr_set, True)
    while insn_iter.hasNext():
        insn = insn_iter.next()
        if not insn.getFlowType().isCall():
            continue
        call_va = int(str(insn.getAddress()), 16)
        # Direct calls
        for ref in ref_manager.getReferencesFrom(insn.getAddress()):
            if ref.getReferenceType().isCall():
                target_va = int(str(ref.getToAddress()), 16)
                calls.append((call_va, target_va, label_at(target_va)))
        # Virtual/indirect calls (CALL qword ptr [RAX+xx])
        mnemonic = str(insn)
        if "CALL qword ptr" in mnemonic and len(calls) > 0 and calls[-1][0] != call_va:
            # No direct ref found — it's an indirect call
            calls.append((call_va, 0, "(indirect) " + mnemonic.split("CALL ")[1] if "CALL " in mnemonic else "(indirect)"))
        elif len(calls) == 0 or calls[-1][0] != call_va:
            if insn.getFlowType().isCall():
                # Check for indirect
                op_str = str(insn)
                if "qword ptr" in op_str or "RAX" in op_str:
                    calls.append((call_va, 0, "(indirect) " + op_str.replace("CALL ", "")))
    return calls

def dump_function_calls(func_va, label):
    """Dump all calls in a function at func_va."""
    func = func_manager.getFunctionAt(to_addr(func_va))
    if not func:
        func = func_manager.getFunctionContaining(to_addr(func_va))
    if not func:
        # Try to create function
        try:
            from ghidra.app.cmd.function import CreateFunctionCmd
            cmd = CreateFunctionCmd(to_addr(func_va))
            cmd.applyTo(currentProgram)
            func = func_manager.getFunctionAt(to_addr(func_va))
        except Exception:
            pass
    if not func:
        print("  Could not resolve function at 0x{:X}".format(func_va))
        return []

    entry = int(str(func.getEntryPoint()), 16)
    body = func.getBody()
    size = 0
    for r in body:
        size += r.getLength()
    print("  {} at 0x{:X}  ({} bytes)  {}".format(label, entry, size, func.getName(True)))

    calls = get_calls_in_function(func)
    print("  All calls ({} total):".format(len(calls)))
    for (cva, tva, lbl) in calls:
        print("    0x{:X} -> {}".format(cva, lbl or "0x{:X}".format(tva)))
    return calls

# ── Step 1: Read AddTarget from vtables ──────────────────────────────────────
print("=" * 70)
print("{} Step 1: Read MagicTarget::AddTarget from vtables".format(ts()))

vtables = [
    ("VTABLE_Actor[4]",           0x14189E288),
    ("VTABLE_Character[4]",       0x1418A5F80),
]

add_target_addrs = set()
for name, vtable_va in vtables:
    slot1_va = read_pointer(vtable_va + 8)  # slot 1 = AddTarget
    if slot1_va:
        print("  {} @ 0x{:X} -> slot 1 (AddTarget) = 0x{:X}  {}".format(
            name, vtable_va, slot1_va, label_at(slot1_va) or "(unlabeled)"))
        add_target_addrs.add(slot1_va)
    else:
        print("  {} @ 0x{:X} -> FAILED to read".format(name, vtable_va))

# ── Step 2: Dump AddTarget raw instructions and fix analysis ─────────────────
print("\n" + "=" * 70)
print("{} Step 2: AddTarget raw disassembly and call analysis".format(ts()))

all_subcalls = {}  # target_va -> label
for addr in sorted(add_target_addrs):
    func = func_manager.getFunctionAt(to_addr(addr))
    if func:
        body = func.getBody()
        size = 0
        for r in body:
            size += r.getLength()
        print("  Existing function at 0x{:X}: {} ({} bytes)".format(addr, func.getName(True), size))

        # If function is tiny, it's probably mis-analyzed.
        if size < 16:
            print("  Function too small — dumping raw bytes and trying to disassemble:")

            # Read raw bytes
            try:
                jb = getBytes(to_addr(addr), 64)
                hex_bytes = " ".join(["{:02X}".format(b & 0xFF) for b in jb])
                print("  Raw bytes at 0x{:X}: {}".format(addr, hex_bytes))
            except Exception as e:
                print("  Failed to read bytes: {}".format(e))

            # Check what Ghidra has at this address (data? undefined?)
            data_at = listing.getDataAt(to_addr(addr))
            if data_at:
                print("  Ghidra data at 0x{:X}: {} ({})".format(addr, data_at, data_at.getDataType()))
            codeunit = listing.getCodeUnitAt(to_addr(addr))
            if codeunit:
                print("  Code unit at 0x{:X}: {} (type: {})".format(addr, codeunit, type(codeunit).__name__))

            # Try to clear and disassemble
            print("\n  Clearing and disassembling from 0x{:X}...".format(addr))
            try:
                from ghidra.app.cmd.disassemble import DisassembleCommand
                from ghidra.program.model.address import AddressSet

                # Clear existing code units first
                listing.clearCodeUnits(to_addr(addr), to_addr(addr + 0x1000), False)

                # Now disassemble
                disCmd = DisassembleCommand(to_addr(addr), AddressSet(to_addr(addr), to_addr(addr + 0x1000)), True)
                disCmd.applyTo(currentProgram)
                print("  Disassembly applied.")
            except Exception as e:
                print("  Disassembly error: {}".format(e))

            # Now try to read instructions
            insn = listing.getInstructionAt(to_addr(addr))
            if not insn:
                print("  Still no instruction at 0x{:X}!".format(addr))
                # Try next address
                for offset in range(1, 16):
                    insn = listing.getInstructionAt(to_addr(addr + offset))
                    if insn:
                        print("  Found instruction at 0x{:X}: {}".format(addr + offset, insn))
                        break

            if insn:
                print("\n  Instructions from 0x{:X}:".format(int(str(insn.getAddress()), 16)))
                count = 0
                cur = insn
                while cur and count < 200:
                    iva = int(str(cur.getAddress()), 16)
                    marker = ""
                    if cur.getFlowType().isCall():
                        for ref in ref_manager.getReferencesFrom(cur.getAddress()):
                            if ref.getReferenceType().isCall():
                                tva = int(str(ref.getToAddress()), 16)
                                marker = "  -> {}".format(label_at(tva) or "0x{:X}".format(tva))
                                all_subcalls[tva] = label_at(tva)
                        if not marker and "CALL" in str(cur):
                            marker = "  (indirect)"
                    print("    0x{:X}  {}{}".format(iva, cur, marker))
                    mnem = cur.getMnemonicString()
                    if mnem == "RET" and count > 10:
                        break
                    cur = cur.getNext()
                    count += 1

            # Try to recreate function
            print("\n  Recreating function at 0x{:X}...".format(addr))
            try:
                existing = func_manager.getFunctionAt(to_addr(addr))
                if existing:
                    func_manager.removeFunction(to_addr(addr))
                from ghidra.app.cmd.function import CreateFunctionCmd
                cmd = CreateFunctionCmd(to_addr(addr))
                cmd.applyTo(currentProgram)
                func = func_manager.getFunctionAt(to_addr(addr))
                if func:
                    body = func.getBody()
                    newsize = 0
                    for r in body:
                        newsize += r.getLength()
                    print("  Recreated: {} ({} bytes)".format(func.getName(True), newsize))
                    if newsize > 16:
                        calls = get_calls_in_function(func)
                        print("  All calls ({} total):".format(len(calls)))
                        for (cva, tva, lbl) in calls:
                            print("    0x{:X} -> {}".format(cva, lbl or "0x{:X}".format(tva)))
                            if tva != 0:
                                all_subcalls[tva] = lbl
            except Exception as e:
                print("  Recreate failed: {}".format(e))
    else:
        print("  No function at 0x{:X}, creating one...".format(addr))
        calls = dump_function_calls(addr, "AddTarget")
        for (cva, tva, lbl) in calls:
            if tva != 0:
                all_subcalls[tva] = lbl
    print()

# ── Step 3: One level deeper — dump calls inside each sub-function ───────────
print("=" * 70)
print("{} Step 3: Calls inside AddTarget's sub-functions (one level deep)".format(ts()))

for tva in sorted(all_subcalls.keys()):
    lbl = all_subcalls[tva]
    if not lbl or "(indirect)" in (lbl or ""):
        continue
    # Skip very common/uninteresting functions
    skip_keywords = ["operator", "memset", "memcpy", "strlen", "mutex",
                     "lock", "unlock", "atomic", "NiSmartPointer"]
    if any(kw.lower() in (lbl or "").lower() for kw in skip_keywords):
        continue
    print()
    func = func_manager.getFunctionAt(to_addr(tva))
    if not func:
        func = func_manager.getFunctionContaining(to_addr(tva))
    if not func:
        print("  0x{:X}  {} — could not resolve".format(tva, lbl))
        continue
    body = func.getBody()
    size = 0
    for r in body:
        size += r.getLength()
    # Only dump functions that are non-trivial (>32 bytes)
    if size < 32:
        print("  0x{:X}  {} — {} bytes (small, skipped)".format(tva, lbl, size))
        continue
    sub_calls = dump_function_calls(tva, lbl)

# ── Step 4: Search for combat/aggression symbols ─────────────────────────────
print("\n" + "=" * 70)
print("{} Step 4: Combat/aggression/hit symbols".format(ts()))

keywords = ["HitData", "ActorCause", "SetActorCause", "Aggression",
            "CombatAlarm", "ProcessHit", "NotifyHit", "RegisterHit",
            "TriggerHostility", "HandleHostile", "ProcessMagicHit",
            "MagicHit", "SpellHit", "HitMe", "ReportCrime"]

found = {}
for sym in sym_table.getAllSymbols(True):
    name = sym.getName(True)
    for kw in keywords:
        if kw.lower() in name.lower():
            va = int(str(sym.getAddress()), 16)
            found[name] = va
            break

for name, va in sorted(found.items()):
    print("  0x{:X}  {}".format(va, name))

print("\n{} Done.".format(ts()))
