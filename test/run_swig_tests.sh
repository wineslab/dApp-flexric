#!/bin/bash
#
# Build all unit tests + the SWIG/Python smoke test (no sanitizer) and run them.
#
# Companion to run_unit_tests.sh: that script is the leak-sanitizer fast path
# without SWIG; this one is the regular build path and additionally exercises
# the Python xApp SDK bindings via test/swig/smoke_test.py.
#
# Requires SWIG >= 4.1 and python3.x-dev (same deps as build_flexric.sh).
# Skips the SCTP integration tests (nearRT_RIC, Agent_RIC_xApp) — those need
# flexric installed under /usr/local/lib/flexric/.
#
# Usage:
#   test/run_swig_tests.sh           # incremental rebuild + run
#   test/run_swig_tests.sh --clean   # wipe build/ first

set -euo pipefail

CLEAN=0
for arg in "$@"; do
  case "$arg" in
    --clean) CLEAN=1 ;;
    -h|--help)
      sed -n '3,15p' "$0"
      exit 0
      ;;
    *)
      echo "Unknown argument: $arg" >&2
      exit 2
      ;;
  esac
done

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

cd "${PROJECT_ROOT}"

if [[ "${CLEAN}" -eq 1 ]]; then
  echo "[swig] removing ${BUILD_DIR}"
  rm -rf "${BUILD_DIR}"
fi

echo "[swig] configuring (E3_AGENT=ON, XAPP_MULTILANGUAGE=ON, no sanitizer)"


cmake -DKPM_VERSION=KPM_V3_00 \
      -DE3_AGENT=ON \
      -DXAPP_MULTILANGUAGE=ON \
      -DCMAKE_C_FLAGS="" \
      -DCMAKE_CXX_FLAGS="" \
      -DCMAKE_EXE_LINKER_FLAGS="" \
      -B "${BUILD_DIR}" \
      -S "${PROJECT_ROOT}" \
      >/dev/null

echo "[swig] building"
cmake --build "${BUILD_DIR}" -j

echo "[swig] running ctest (excluding integration tests)"
ctest --test-dir "${BUILD_DIR}" \
      -E "nearRT_RIC|Agent_RIC_xApp" \
      --output-on-failure
