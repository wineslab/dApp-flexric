#!/bin/bash
#
# Build all per-SM unit tests under LeakSanitizer and run them.
#
# Fast path (~3 s after first build). No privileges required, no install,
# nothing touches /usr/local/. Skips the SCTP integration tests — for
# those, see run_integration_tests.sh.
#
# Usage:
#   test/run_unit_tests.sh           # incremental rebuild + run
#   test/run_unit_tests.sh --clean   # wipe build/ first

set -euo pipefail

CLEAN=0
for arg in "$@"; do
  case "$arg" in
    --clean) CLEAN=1 ;;
    -h|--help)
      sed -n '3,12p' "$0"
      exit 0
      ;;
    *)
      echo "Unknown argument: $arg" >&2
      exit 2
      ;;
  esac
done

# Resolve project root regardless of where the script is invoked from.
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PROJECT_ROOT="$(cd "${SCRIPT_DIR}/.." && pwd)"
BUILD_DIR="${PROJECT_ROOT}/build"

cd "${PROJECT_ROOT}"

if [[ "${CLEAN}" -eq 1 ]]; then
  echo "[unit] removing ${BUILD_DIR}"
  rm -rf "${BUILD_DIR}"
fi

echo "[unit] configuring (E3_AGENT=ON, -fsanitize=leak)"
cmake -DE3_AGENT=ON \
      -DCMAKE_C_FLAGS="-fsanitize=leak -g" \
      -DCMAKE_EXE_LINKER_FLAGS="-fsanitize=leak" \
      -B "${BUILD_DIR}" \
      -S "${PROJECT_ROOT}" \
      >/dev/null

echo "[unit] building"
cmake --build "${BUILD_DIR}" -j

# Filter out the SCTP integration tests — they need installed .so files
# under /usr/local/lib/flexric/, which run_integration_tests.sh handles.
echo "[unit] running ctest (excluding integration tests)"
ctest --test-dir "${BUILD_DIR}" \
      -E "nearRT_RIC|Agent_RIC_xApp" \
      --output-on-failure
