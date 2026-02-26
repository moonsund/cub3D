#!/usr/bin/env python3
import os
import shlex
import subprocess
import sys
from pathlib import Path

PROJECT_ROOT = Path(__file__).resolve().parent.parent
MAPS_DIR = PROJECT_ROOT / "tests" /  "maps"
EXPECTED_DIR = MAPS_DIR / "expected"

RUN_PREFIX = shlex.split(os.getenv("RUN_PREFIX", ""))

BINARY_DEFAULT = PROJECT_ROOT / "cub3d_debug"

ERROR_MARKER_DEFAULT = "Error"

def read_text(path: Path) -> str:
    return path.read_text(encoding="utf-8", errors="replace")

def run_cmd(
        binary: str,
        map_file: str,
        prefix=None,
    ) -> tuple[int, str, str]:

    cmd = []
    if isinstance(prefix, str):
        cmd.extend(shlex.split(prefix))
    elif prefix:
        cmd.extend(prefix)
    cmd.extend([binary, map_file])
    
    proc = subprocess.run(
        cmd,
        cwd=str(PROJECT_ROOT),
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE,
        text=True,
        encoding="utf-8",
        errors="replace",
    )
    return proc.returncode, proc.stdout, proc.stderr

def normalize_newlines(s: str) -> str:
    return s.replace("\r\n", "\n").replace("\r", "\n")

def fail(msg: str) -> None:
    print(msg, file=sys.stderr)
    sys.exit(1)

def list_maps(prefix: str) -> list[Path]:
    return sorted(MAPS_DIR.glob(f"{prefix}_*.cub"))

def main() -> None:
    binary = Path(os.environ.get("CUB3D_BIN", str(BINARY_DEFAULT)))
    error_marker = os.environ.get("CUB3D_ERROR_MARKER", ERROR_MARKER_DEFAULT)

    if not binary.exists():
        fail(f"[FAIL] Binary not found: {binary}\n"
             f"Build it first (e.g. `make debug`) or set CUB3D_BIN.")

    ok_maps = list_maps("ok")
    err_maps = list_maps("err")

    if not ok_maps and not err_maps:
        fail(f"[FAIL] No maps found in {MAPS_DIR}")

    total = 0
    passed = 0

    # OK cases
    for ok_map in ok_maps:
        total += 1
        expected = EXPECTED_DIR / f"{ok_map.stem}.out"
        if not expected.exists():
            fail(f"[FAIL] Expected file missing: {expected}")

        return_code, out, err = run_cmd(str(binary), str(ok_map))
        out = normalize_newlines(out)
        err = normalize_newlines(err)
        exp = normalize_newlines(read_text(expected))

        if return_code != 0:
            print(f"[FAIL] {ok_map.name}: expected exit 0, got {return_code}", file=sys.stderr)
            print("---- stderr ----", file=sys.stderr)
            print(err, file=sys.stderr)
            continue

        if out != exp:
            print(f"[FAIL] {ok_map.name}: stdout mismatch", file=sys.stderr)
            print("---- expected ----", file=sys.stderr)
            print(exp, file=sys.stderr)
            print("---- got ----", file=sys.stderr)
            print(out, file=sys.stderr)
            continue

        passed += 1
        print(f"[OK]   {ok_map.name}")

    # ERR cases
    for err_map in err_maps:
        total += 1
        rc, out, err = run_cmd(str(binary), str(err_map))
        out = normalize_newlines(out)
        err = normalize_newlines(err)

        if rc == 0:
            print(f"[FAIL] {err_map.name}: expected non-zero exit, got 0", file=sys.stderr)
            print("---- stdout ----", file=sys.stderr)
            print(out, file=sys.stderr)
            continue

        if error_marker and error_marker not in err:
            print(f"[FAIL] {err_map.name}: stderr does not contain marker '{error_marker}'", file=sys.stderr)
            print("---- stderr ----", file=sys.stderr)
            print(err, file=sys.stderr)
            continue

        passed += 1
        print(f"[OK]   {err_map.name} (failed as expected)")

    if passed != total:
        fail(f"[SUMMARY] {passed}/{total} passed")
    print(f"[SUMMARY] {passed}/{total} passed")

if __name__ == "__main__":
    main()