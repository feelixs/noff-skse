#!/usr/bin/env python3
"""
find_hooks.py — Locate NOFF write_call hook sites in any Skyrim SE/AE/VR binary.

For each of the 5 REL::Offset hooks in main.cpp, extracts a masked byte
signature from the AE 1.6.1170 reference binary, then scans a target binary
for the same pattern.  Relative operands (E8/E9/Jcc rel32 and RIP-relative
disp32) are wildcarded so the pattern works across versions even though
function addresses differ.

Requirements:
    pip install pefile capstone

Usage:
    python find_hooks.py <target.exe> --ref <ae_1170.exe>
    python find_hooks.py --list          # show built-in AE offsets only

Output:
    One REL::Offset(0xXXXXXXX) line per hook, ready to paste into main.cpp.
"""

import sys
import argparse
from pathlib import Path

try:
    import pefile
except ImportError:
    sys.exit("Missing dependency — run:  pip install pefile")

try:
    import capstone
    import capstone.x86
    _cs = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)
    _cs.detail = True
except ImportError:
    sys.exit("Missing dependency — run:  pip install capstone")


# ---------------------------------------------------------------------------
# Hook catalogue — REL::Offset values verified in AE 1.6.1170 (== PE RVA).
# ---------------------------------------------------------------------------
HOOKS = [
    {
        "name": "CombatUnk1",
        "rva":  0x6BC620,
        "desc": "Actor::Combat_unk1 — makes NPC enter combat state",
    },
    {
        "name": "HitEvent",
        "rva":  0x6C533B,
        "desc": "BSTEventSource<TESHitEvent>::SendEvent (Actor::AddTarget path)",
    },
    {
        "name": "HitTask",
        "rva":  0x6C5413,
        "desc": "Actor_QueueHitTask (Actor::AddTarget path)",
    },
    {
        "name": "ExplosionHitEvent",
        "rva":  0x7D15BD,
        "desc": "BSTEventSource<TESHitEvent>::SendEvent (Explosion_ApplyEffects path)",
    },
    {
        "name": "ExplosionActorHit",
        "rva":  0x7D16E2,
        "desc": "TESObjectREFR::sub (Explosion_ApplyEffects path)",
    },
]

# Bytes extracted before and after the E8 call instruction.
# Total window = BEFORE + 5 (E8 + rel32) + AFTER
CONTEXT_BEFORE = 32
CONTEXT_AFTER  = 20

WILDCARD = -1   # sentinel value in pattern lists


# ---------------------------------------------------------------------------
# PE helpers
# ---------------------------------------------------------------------------

def _load_pe(path: Path) -> pefile.PE:
    return pefile.PE(str(path), fast_load=False)


def _rva_to_file_offset(pe: pefile.PE, rva: int) -> int:
    for sec in pe.sections:
        if sec.VirtualAddress <= rva < sec.VirtualAddress + sec.Misc_VirtualSize:
            return sec.PointerToRawData + (rva - sec.VirtualAddress)
    raise ValueError(f"RVA 0x{rva:X} not found in any section")


def _read_rva(pe: pefile.PE, rva: int, size: int) -> bytes:
    off  = _rva_to_file_offset(pe, rva)
    data = pe.__data__[off: off + size]
    if len(data) < size:
        raise ValueError(f"Short read at RVA 0x{rva:X}: got {len(data)}/{size} bytes")
    return data


def _get_text_section(pe: pefile.PE) -> tuple[int, bytes]:
    """Return (section_rva, raw_bytes) for the .text section."""
    for sec in pe.sections:
        name = sec.Name.rstrip(b"\x00").decode("ascii", errors="replace")
        if name == ".text":
            off  = sec.PointerToRawData
            size = sec.SizeOfRawData
            return sec.VirtualAddress, pe.__data__[off: off + size]
    raise ValueError("No .text section found in binary")


def _detect_version(pe: pefile.PE) -> str:
    """Best-effort version string from PE version resources."""
    try:
        pe.parse_data_directories()
        # VS_FIXEDFILEINFO (always present, no string table needed)
        if hasattr(pe, "VS_FIXEDFILEINFO") and pe.VS_FIXEDFILEINFO:
            ffi = pe.VS_FIXEDFILEINFO[0]
            ms, ls = ffi.FileVersionMS, ffi.FileVersionLS
            return f"{ms>>16}.{ms&0xFFFF}.{ls>>16}.{ls&0xFFFF}"
    except Exception:
        pass
    return "(version unknown)"


def _check_64bit(pe: pefile.PE) -> bool:
    """Return True if the binary is x64 (PE32+)."""
    return pe.FILE_HEADER.Machine == 0x8664  # IMAGE_FILE_MACHINE_AMD64


def _check_drm(pe: pefile.PE) -> bool:
    """Return True if the binary shows signs of SteamStub section encryption."""
    # SteamStub adds a .bind section and/or marks .text as not-readable in raw data.
    # A quick heuristic: if the first 8 bytes of .text are all the same non-zero byte,
    # or entropy is very low/high, it's likely encrypted.
    # Simpler: check for the SteamStub stub section name.
    section_names = [s.Name.rstrip(b"\x00") for s in pe.sections]
    if b".bind" in section_names or b"steamclient" in section_names:
        return True
    # Also check: if .text characteristic doesn't include MEM_EXECUTE it may be packed
    for sec in pe.sections:
        if sec.Name.rstrip(b"\x00") == b".text":
            # SteamStub 3.1 zeroes PointerToRawData or sets SizeOfRawData to 0
            if sec.SizeOfRawData == 0 or sec.PointerToRawData == 0:
                return True
    return False


# ---------------------------------------------------------------------------
# Signature extraction using Capstone
# ---------------------------------------------------------------------------

def _build_masked_pattern(code: bytes, window_va: int) -> list[int]:
    """
    Disassemble `code` (notionally at `window_va`) with Capstone.
    Return a list[int] where relative-operand bytes are replaced with WILDCARD:
      - E8 / E9 rel32    (CALL / JMP near)
      - 0F 8x rel32      (Jcc long)
      - EB rel8          (JMP short)
      - RIP-relative disp32  (LEA/MOV/CMP etc. with base == RIP)
    All other bytes are kept as literals.
    """
    pattern = list(code)

    for insn in _cs.disasm(code, window_va):
        rel = insn.address - window_va      # position within chunk
        b0  = code[rel]

        # ── Relative branch operands ────────────────────────────────────────
        if b0 in (0xE8, 0xE9):             # CALL/JMP rel32
            for k in range(rel + 1, rel + 5):
                if k < len(pattern):
                    pattern[k] = WILDCARD

        elif b0 == 0xEB:                   # JMP rel8
            if rel + 1 < len(pattern):
                pattern[rel + 1] = WILDCARD

        elif b0 == 0x0F and rel + 1 < len(code) and (code[rel + 1] & 0xF0) == 0x80:
            for k in range(rel + 2, rel + 6):   # Jcc rel32
                if k < len(pattern):
                    pattern[k] = WILDCARD

        # ── RIP-relative memory operands ────────────────────────────────────
        for op in insn.operands:
            if (op.type == capstone.x86.X86_OP_MEM and
                    op.mem.base == capstone.x86.X86_REG_RIP):
                # disp32 sits in the last 4 bytes of the instruction
                disp_start = rel + insn.size - 4
                for k in range(disp_start, disp_start + 4):
                    if 0 <= k < len(pattern):
                        pattern[k] = WILDCARD

    return pattern


def extract_signature(pe: pefile.PE, hook: dict) -> dict:
    """Extract a masked signature for `hook` from `pe`."""
    rva   = hook["rva"]
    start = rva - CONTEXT_BEFORE
    total = CONTEXT_BEFORE + 5 + CONTEXT_AFTER

    code    = _read_rva(pe, start, total)
    win_va  = pe.OPTIONAL_HEADER.ImageBase + start
    pattern = _build_masked_pattern(code, win_va)

    # Sanity check: the target byte must be E8 (CALL rel32)
    if code[CONTEXT_BEFORE] != 0xE8:
        print(f"  WARNING [{hook['name']}]: byte at RVA 0x{rva:X} is "
              f"0x{code[CONTEXT_BEFORE]:02X}, expected 0xE8.")
        print(f"           If ALL hooks warn like this, the binary is likely Steam DRM encrypted.")
        print(f"           Strip it with Steamless first: https://github.com/atom0s/Steamless/releases")

    return {
        "name":     hook["name"],
        "rva":      rva,
        "pattern":  pattern,
        "call_idx": CONTEXT_BEFORE,   # E8 position within pattern
    }


# ---------------------------------------------------------------------------
# Pattern scanner
# ---------------------------------------------------------------------------

def scan_text(text_bytes: bytes, text_rva: int, pattern: list[int]) -> list[int]:
    """
    Scan text_bytes for occurrences of `pattern`.
    Returns list of window-start RVAs (relative to image base).
    WILDCARD entries match any byte.
    """
    plen    = len(pattern)
    results = []
    for i in range(len(text_bytes) - plen + 1):
        for j, p in enumerate(pattern):
            if p != WILDCARD and text_bytes[i + j] != p:
                break
        else:
            results.append(text_rva + i)
    return results


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> None:
    ap = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    ap.add_argument("target", nargs="?", help="Target Skyrim .exe to scan")
    ap.add_argument(
        "--ref",
        metavar="AE_1170_EXE",
        help="Reference AE 1.6.1170 SkyrimSE.exe (required for scanning)",
    )
    ap.add_argument(
        "--list", action="store_true",
        help="Print the known AE 1.6.1170 offsets and exit",
    )
    ap.add_argument(
        "--show-patterns", action="store_true",
        help="Print extracted hex patterns (useful for debugging false positives)",
    )
    args = ap.parse_args()

    if args.list:
        print("Known hook offsets in AE 1.6.1170 (REL::Offset values):\n")
        for h in HOOKS:
            print(f"  0x{h['rva']:07X}  {h['name']}")
            print(f"             {h['desc']}")
        return

    if not args.target and not args.ref:
        ap.print_help()
        sys.exit(0)
    if not args.target:
        ap.error("target executable is required")
    if not args.ref:
        ap.error("--ref <ae_1170.exe> is required")

    ref_path    = Path(args.ref)
    target_path = Path(args.target)

    # ── Extract signatures from reference binary ────────────────────────────
    print(f"Reference : {ref_path}")
    print("Extracting signatures from AE 1.6.1170…\n")

    ref_pe = _load_pe(ref_path)
    if not _check_64bit(ref_pe):
        print("ERROR: Reference binary is 32-bit (Skyrim LE / TESV.exe).")
        print("       NOFF uses CommonLibSSE which only supports 64-bit SE/AE/VR.")
        sys.exit(1)
    if _check_drm(ref_pe):
        print("ERROR: Reference binary appears to be Steam DRM protected (code section encrypted).")
        print("       Run Steamless on it first: https://github.com/atom0s/Steamless/releases")
        print("       Then point --ref at the output .unpacked.exe file.")
        sys.exit(1)

    signatures = []

    for hook in HOOKS:
        try:
            sig = extract_signature(ref_pe, hook)
            signatures.append(sig)
            if args.show_patterns:
                pat = " ".join("??" if b == WILDCARD else f"{b:02X}"
                               for b in sig["pattern"])
                print(f"  [{hook['name']}]\n    {pat}\n")
        except Exception as exc:
            print(f"  [{hook['name']}]  ERROR extracting signature: {exc}")

    # ── Scan target binary ──────────────────────────────────────────────────
    print(f"Target    : {target_path}")
    target_pe = _load_pe(target_path)
    if not _check_64bit(target_pe):
        print("ERROR: Target binary is 32-bit (Skyrim LE / TESV.exe).")
        print("       NOFF uses CommonLibSSE which only supports 64-bit SE/AE/VR.")
        sys.exit(1)
    if _check_drm(target_pe):
        print("ERROR: Target binary appears to be Steam DRM protected (code section encrypted).")
        print("       Run Steamless on it first: https://github.com/atom0s/Steamless/releases")
        print("       Then point the target at the output .unpacked.exe file.")
        sys.exit(1)
    target_version = _detect_version(target_pe)
    target_base    = target_pe.OPTIONAL_HEADER.ImageBase

    print(f"Version   : {target_version}")
    print(f"ImageBase : 0x{target_base:X}\n")

    text_rva, text_bytes = _get_text_section(target_pe)
    print("Scanning .text section…\n")

    all_found = True
    results   = []

    for sig in signatures:
        hook_name = sig["name"]
        hook_desc = next(h["desc"] for h in HOOKS if h["name"] == hook_name)
        windows   = scan_text(text_bytes, text_rva, sig["pattern"])
        # Adjust from window-start RVA to call-instruction RVA
        call_rvas = [w + sig["call_idx"] for w in windows]
        # Filter: the byte at the match must actually be E8
        call_rvas = [r for r in call_rvas
                     if text_bytes[r - text_rva] == 0xE8]

        print(f"[{hook_name}]  {hook_desc}")

        if not call_rvas:
            print(f"  NOT FOUND — no match in .text")
            print(f"  Try widening CONTEXT_BEFORE/AFTER or verify in Ghidra\n")
            all_found = False
        elif len(call_rvas) == 1:
            rva = call_rvas[0]
            print(f"  REL::Offset(0x{rva:07X})")
            print(f"  VA 0x{target_base + rva:X}\n")
            results.append((hook_name, rva))
        else:
            print(f"  AMBIGUOUS — {len(call_rvas)} matches (widen context to disambiguate):")
            for rva in call_rvas:
                print(f"    REL::Offset(0x{rva:07X})   // VA 0x{target_base + rva:X}")
            print()
            all_found = False

    # ── Summary ────────────────────────────────────────────────────────────
    if results:
        print("-" * 60)
        print("Paste into main.cpp Install() guards:\n")
        for name, rva in results:
            print(f'    // {name}')
            print(f'    REL::Relocation<std::uintptr_t> target{{ REL::Offset(0x{rva:07X}) }};')
        print()

    if all_found:
        print("All hooks located successfully.")
    else:
        print("Some hooks were not found or ambiguous — manual Ghidra verification needed.")


if __name__ == "__main__":
    main()
