# arcal-cert

A transport-agnostic OMSC-SPC-008 RevK conformance and end-to-end test suite for
C++ CAL implementations. It checks public API compile/link compatibility and
runtime behavior without DDS- or transport-specific code; the parent project
supplies the CAL library target and injects transport environment variables.

## What it tests

**CERT** — compile-and-run checks against OMSC-SPC-008 RevK requirement IDs:

| Test ID | Description |
|---|---|
| CERT-CAL-016015 | Distinct UUIDs for multiple CAL clients in one address space |
| CERT-CAL-016366 | Status listener called immediately on registration with current state |
| CERT-CAL-005201 | Mechanism to obtain an initialized CAL instance |
| CERT-CAL-005202 | Single CAL instance per unique Service + ASB Identifier |
| CERT-CAL-005203 | Retrieve System/Service/Subsystem/Component/Capability UUIDs |
| CERT-CAL-005204 | Error reported when initialization fails |
| CERT-CAL-005208 | Topic associated with one and only one CAL message type |
| CERT-CAL-005209 | Client topics mapped to applicable CAL topics |
| CERT-CAL-005210 | Independent QoS settings per client topic |

**E2E** — single- and multi-process pub/sub scenarios:

| Test ID | Description |
|---|---|
| E2E-ActionCommand-PubSub | Publish + subscribe one ActionCommand message end-to-end |
| E2E-TopicIsolation | Messages on one topic are not delivered on another |
| E2E-content-fidelity | Message content survives CAL publish/subscribe delivery |
| E2E-multi-message | Multiple sequential messages are all delivered |
| E2E-listener-lifecycle | DataAvailableListener fires and can be removed cleanly |
| E2E-two-writers-one-reader | Two writers, one reader; all messages received |
| E2E-two-readers-one-writer | Two readers, one writer; both readers receive |
| E2E-readnowait-empty | readNoWait on empty topic returns immediately with no data |
| E2E-read-timeout | Blocking read times out when no data arrives within the deadline |

## Requirements

- C++17
- CMake ≥ 3.21
- A conforming CAL library exposing `uci/base/*` and `uci/type/*` headers and
  providing `uci_getAbstractServiceBusConnection`

## Integration as a git submodule

```bash
git submodule add https://github.com/droneswatter/arcal-cert <path/to/arcal-cert>
```

Then in your `CMakeLists.txt`, **before** `add_subdirectory`:

```cmake
# Required: your CAL implementation target.
set(ARCAL_CERT_CAL_LIB "my_cal_target")

# Optional: transport environment variables forwarded to every test.
# List entries are VAR=VALUE strings; they are passed verbatim to CTest's
# ENVIRONMENT property and inherited by child processes (e.g. shell scripts).
set(ARCAL_CERT_TEST_ENV
    "MY_TRANSPORT_URI=..."
    "LD_LIBRARY_PATH=/path/to/transport/libs")

add_subdirectory(<path/to/arcal-cert>)
```

`ARCAL_CERT_CAL_LIB` must be a defined CMake target at the time `add_subdirectory`
is called. The target must export `uci/base/` and `uci/type/` headers via its
`INTERFACE_INCLUDE_DIRECTORIES`.

## Running the tests

```bash
cmake --build build
ctest --test-dir build -R "^(CERT|E2E)-" --output-on-failure
```

To run only CERT or only E2E:

```bash
ctest --test-dir build -R "^CERT-" --output-on-failure
ctest --test-dir build -R "^E2E-"  --output-on-failure
```

## CMake variables reference

| Variable | Required | Description |
|---|---|---|
| `ARCAL_CERT_CAL_LIB` | **Yes** | CMake target for the CAL implementation |
| `ARCAL_CERT_TEST_ENV` | No | Semicolon-separated `VAR=VALUE` list forwarded to test `ENVIRONMENT` |
| `ARCAL_CERT_BUILD_CERT` | No | Build CERT tests (default `ON`) |
| `ARCAL_CERT_BUILD_E2E` | No | Build E2E tests (default `ON`) |
