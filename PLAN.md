# Package CERT and E2E tests as `arcal-cert`

## Context

The CERT and E2E tests in `arcal/test/cert/` and `arcal/test/e2e/` test conformance to
OMSC-SPC-008 using only the public `uci::base::*` / `uci::type::*` CAL API. They could
run against any compliant CAL, but are currently embedded inside the arcal build and
hard-code arcal target names and CycloneDDS transport configuration. The goal is to move
them into a standalone git repository (`arcal-cert`) that any CAL project can consume as a
git submodule, with CMake variables for the CAL library target and test environment.

Transport configuration (e.g. `CYCLONEDDS_URI`, `cyclonedds_localhost.xml`) is
deliberately left in the parent project (arcal) — arcal-cert knows nothing about DDS.

While we're here, `pub_rich.cpp` and `pub_continuous.cpp` are bus-monitor utilities that
live in `test/e2e/` but belong in `arcal-busmon/`. That move is included.

---

## New repository: `/home/brent/repos/modular-af/arcal-cert/`

### Directory layout

```
arcal-cert/
├── CMakeLists.txt
├── README.md
├── cert/
│   ├── CMakeLists.txt
│   ├── CAL-005201.cpp      ← copied from arcal/test/cert/
│   ├── CAL-005202.cpp
│   ├── CAL-005203.cpp
│   ├── CAL-005204.cpp
│   ├── CAL-005208.cpp
│   ├── CAL-005209.cpp
│   ├── CAL-005210.cpp
│   ├── CAL-016015.cpp
│   └── CAL-016366.cpp
└── e2e/
    ├── CMakeLists.txt
    ├── run_e2e_action_command.sh.in   ← stripped of transport exports
    ├── run_e2e_topic_isolation.sh.in  ← stripped of transport exports
    ├── pub_action_command.cpp         ← copied (needed by shell test)
    ├── sub_action_command.cpp         ← copied (needed by shell test)
    ├── topic_isolation.cpp
    ├── content_fidelity.cpp
    ├── multi_message.cpp
    ├── listener_lifecycle.cpp
    ├── two_writers_one_reader.cpp
    ├── two_readers_one_writer.cpp
    ├── readnowait_empty.cpp
    └── read_timeout.cpp
```

**Not included**: `cyclonedds_localhost.xml` (stays in arcal — it's DDS-specific),
`pub_rich.cpp`, `pub_continuous.cpp` (moved to arcal-busmon).

---

### CMake variables (transport-agnostic)

| Variable | Required | Description |
|---|---|---|
| `ARCAL_CERT_CAL_LIB` | Yes | CMake target for the CAL implementation. Must expose `uci/base/*` and `uci/type/*` in its interface include dirs and provide `uci_getAbstractServiceBusConnection`. |
| `ARCAL_CERT_EXTERNALIZER_LIB` | No | CMake target for the CDR message externalizer. Required for E2E tests and CERT CAL-005208/209/210. If unset, those tests are skipped with `message(STATUS ...)`. |
| `ARCAL_CERT_TEST_ENV` | No | Semicolon-separated list of `VAR=VALUE` strings forwarded verbatim to every test's `ENVIRONMENT` property. The parent project injects transport-specific vars here (e.g. `CYCLONEDDS_URI=...`, `LD_LIBRARY_PATH=...`). |
| `ARCAL_CERT_BUILD_CERT` | No | Build CERT tests (default `ON`) |
| `ARCAL_CERT_BUILD_E2E` | No | Build E2E tests (default `ON`) |

### `arcal-cert/CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.21)
project(arcal-cert LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(ARCAL_CERT_CAL_LIB          ""  CACHE STRING "CMake target for the CAL library (required)")
set(ARCAL_CERT_EXTERNALIZER_LIB ""  CACHE STRING "CMake target for CDR externalizer (optional)")
set(ARCAL_CERT_TEST_ENV         ""  CACHE STRING "Extra env vars for tests, e.g. 'TRANSPORT_URI=...'")
option(ARCAL_CERT_BUILD_CERT "Build CERT tests" ON)
option(ARCAL_CERT_BUILD_E2E  "Build E2E tests"  ON)

if(NOT ARCAL_CERT_CAL_LIB)
    message(FATAL_ERROR "ARCAL_CERT_CAL_LIB must name the CMake target for your CAL implementation.")
endif()
if(NOT TARGET ${ARCAL_CERT_CAL_LIB})
    message(FATAL_ERROR "'${ARCAL_CERT_CAL_LIB}' is not a defined CMake target.")
endif()
if(ARCAL_CERT_EXTERNALIZER_LIB AND NOT TARGET ${ARCAL_CERT_EXTERNALIZER_LIB})
    message(FATAL_ERROR "'${ARCAL_CERT_EXTERNALIZER_LIB}' is not a defined CMake target.")
endif()

enable_testing()
if(ARCAL_CERT_BUILD_CERT) add_subdirectory(cert) endif()
if(ARCAL_CERT_BUILD_E2E)  add_subdirectory(e2e)  endif()
```

### `arcal-cert/cert/CMakeLists.txt`

Two internal helpers `_arcal_cert_test(id)` and `_arcal_cert_test_ext(id)` each call
`set_tests_properties(... ENVIRONMENT "${ARCAL_CERT_TEST_ENV}")`. The `_ext` variant
skips gracefully if `ARCAL_CERT_EXTERNALIZER_LIB` is unset.

### `arcal-cert/e2e/CMakeLists.txt`

Guards at top: `return()` with status message if `ARCAL_CERT_EXTERNALIZER_LIB` is unset.
Otherwise mirrors the existing `test/e2e/CMakeLists.txt` using the variable targets
and `ARCAL_CERT_TEST_ENV`. Drops the `PRIVATE ${CMAKE_SOURCE_DIR}/src` include path
(no test file actually uses it).

### Shell scripts — transport-neutral

`run_e2e_action_command.sh.in` and `run_e2e_topic_isolation.sh.in` currently export
`CYCLONEDDS_URI` and `LD_LIBRARY_PATH` inline. Both lines are removed. CTest injects
those values via `ENVIRONMENT` (set from `ARCAL_CERT_TEST_ENV`), which is inherited by
shell script child processes. The scripts become pure orchestration logic with only
`@CMAKE_CURRENT_BINARY_DIR@` substituted.

---

## Changes to `arcal/`

### 1. Add arcal-cert as a git submodule

```bash
git -C /home/brent/repos/modular-af/arcal \
    submodule add ../arcal-cert test/arcal-cert
```

### 2. Update `arcal/CMakeLists.txt`

Replace:
```cmake
if(ARCAL_BUILD_TESTS)
    add_subdirectory(test/cert)
    ...
endif()
if(ARCAL_BUILD_E2E_TESTS)
    add_subdirectory(test/e2e)
endif()
```
With:
```cmake
if(ARCAL_BUILD_TESTS OR ARCAL_BUILD_E2E_TESTS)
    set(ARCAL_CERT_CAL_LIB          "arcal"                  CACHE STRING "" FORCE)
    set(ARCAL_CERT_EXTERNALIZER_LIB "arcal_externalizer_cdr" CACHE STRING "" FORCE)
    set(ARCAL_CERT_BUILD_CERT       ${ARCAL_BUILD_TESTS}     CACHE BOOL   "" FORCE)
    set(ARCAL_CERT_BUILD_E2E        ${ARCAL_BUILD_E2E_TESTS} CACHE BOOL   "" FORCE)
    set(ARCAL_CERT_TEST_ENV
        "CYCLONEDDS_URI=file://${CMAKE_SOURCE_DIR}/test/e2e/cyclonedds_localhost.xml"
        CACHE STRING "" FORCE)
    add_subdirectory(test/arcal-cert)
endif()
```

`cyclonedds_localhost.xml` stays in `arcal/test/e2e/` (or moves to `arcal/test/` — either
works since the path is constructed by arcal's CMakeLists, not by arcal-cert).

### 3. Delete migrated files from arcal

- `arcal/test/cert/` — entire directory (9 .cpp + CMakeLists.txt)
- `arcal/test/e2e/` — all CTest-registered test files + shell scripts (see list above)
- Keep: `arcal/test/e2e/pub_rich.cpp`, `pub_continuous.cpp`, `cyclonedds_localhost.xml`

After deletion `arcal/test/e2e/CMakeLists.txt` is removed entirely (it only built tests and
the two demo programs, which are moving to arcal-busmon).

---

## Changes to `arcal-busmon/`

Move `arcal/test/e2e/pub_rich.cpp` and `arcal/test/e2e/pub_continuous.cpp` to
`arcal-busmon/`. Update `arcal-busmon/CMakeLists.txt` to build them, linking against
`arcal` and `arcal_externalizer_cdr`.

---

## `arcal-cert/README.md` — key sections

1. **What it is**: transport-agnostic OMSC-SPC-008 RevK conformance test suite. 9 CERT tests + 9 E2E pub/sub scenarios. No DDS-specific code.
2. **Requirements**: C++17, CMake ≥ 3.21, a conforming CAL library + optional CDR externalizer.
3. **Integration as a git submodule**:
   ```bash
   git submodule add https://github.com/modular-af/arcal-cert <path>
   ```
   Then in your `CMakeLists.txt`:
   ```cmake
   set(ARCAL_CERT_CAL_LIB          "your_cal_target")
   set(ARCAL_CERT_EXTERNALIZER_LIB "your_cdr_target")  # omit to skip E2E + 3 CERT tests
   set(ARCAL_CERT_TEST_ENV         "YOUR_TRANSPORT_URI=..." "LD_LIBRARY_PATH=...")
   add_subdirectory(<path>)
   ```
4. **Environment variables**: injected by the parent via `ARCAL_CERT_TEST_ENV`; arcal-cert itself sets none.
5. **Running**:
   ```bash
   cmake --build build
   ctest --test-dir build -R "^(CERT|E2E)-" --output-on-failure
   ```
6. **Test inventory table**: one row per test with CERT ID, description, and whether externalizer is required.

---

## Verification

```bash
# Full arcal build (now uses arcal-cert submodule)
cmake --build /home/brent/repos/modular-af/arcal/build

# All 22 tests must still pass
ctest --test-dir /home/brent/repos/modular-af/arcal/build --output-on-failure
```

---

## Files summary

| Action | Path |
|---|---|
| **git init** new repo | `/home/brent/repos/modular-af/arcal-cert/` |
| **Create** | `arcal-cert/CMakeLists.txt` |
| **Create** | `arcal-cert/README.md` |
| **Create** | `arcal-cert/cert/CMakeLists.txt` |
| **Copy** 9 files | `arcal/test/cert/*.cpp` → `arcal-cert/cert/` |
| **Create** | `arcal-cert/e2e/CMakeLists.txt` |
| **Copy** 12 files | E2E `.cpp` + simplified `.sh.in` → `arcal-cert/e2e/` |
| **Modify** | `arcal/CMakeLists.txt` |
| **Delete** | `arcal/test/cert/` (all) |
| **Delete** | `arcal/test/e2e/` test files + CMakeLists |
| **git submodule add** | `arcal-cert` → `arcal/test/arcal-cert/` |
| **Move** | `pub_rich.cpp`, `pub_continuous.cpp` → `arcal-busmon/` |
| **Modify** | `arcal-busmon/CMakeLists.txt` |
