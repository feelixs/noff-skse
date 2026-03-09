#!/usr/bin/env python3
# Scan AE 1.6.1170 — edit the path below, then run.

EXE = r""  # AE 1.6.1170

# ─────────────────────────────────────────────────────────────────────────────
import subprocess, sys
from pathlib import Path

ref    = Path(__file__).parent / "find_hooks.py"
result = subprocess.run(
    [sys.executable, str(ref), EXE, "--ref", EXE],
    cwd=Path(__file__).parent,
    capture_output=True, text=True,
)
print(result.stdout)
if result.stderr:
    print(result.stderr)
