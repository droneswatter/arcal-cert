# arcal-cert Plan

`arcal-cert` is a conformance suite for C++ CAL implementations. It verifies public API compile/link compatibility, CERT requirements, and end-to-end runtime behavior through the public CAL API. It should remain transport-agnostic: the parent project supplies the CAL target and any transport environment variables.

Some compile/link API-shape checks can live in `arcal-cert` when they exercise the public C++CAL headers and link target directly. Implementation-specific build checks still belong in the CAL implementation's own build.

## P0: Submodule Contract

Keep this repository easy for any CAL project to consume as a CMake subdirectory.

Tasks:

- [ ] Keep `ARCAL_CERT_CAL_LIB` as the only required integration variable.
- [ ] Keep `ARCAL_CERT_TEST_ENV` as the only transport environment injection mechanism.
- [ ] Avoid private implementation headers, generated build paths, DDS types, or ARCAL-specific helpers in tests.
- [ ] Ensure every executable links only to `ARCAL_CERT_CAL_LIB`.
- [ ] Keep CMake failures clear when required targets are missing.
- [ ] Add CTest labels for filtering:
  - `cert`
  - `e2e`
  - `runtime`

Verification:

```bash
cmake --build build
ctest --test-dir build -N
```

## P0: Requirements Traceability

Create a matrix that makes coverage honest and reviewable.

Tasks:

- [ ] Add `CONFORMANCE.md` with a requirements matrix.
- [ ] Start with every existing `CERT-CAL-*` test in `cert/`.
- [ ] Record uncovered CERT requirements as `planned`, not implied.
- [ ] Use these columns:
  - Requirement
  - Area
  - Test type
  - Test file
  - Status
  - Notes
- [ ] Keep statuses small and consistent:
  - `covered`
  - `partial`
  - `planned`
  - `blocked`
  - `not applicable`
- [ ] Link each requirement row to the test file that covers it.
- [ ] Add a short note when a requirement is covered by compile/link checks outside `arcal-cert`.

Verification:

```bash
rg -n "CERT-CAL-|planned|partial|blocked" CONFORMANCE.md
```

## P0: CERT Test Quality

Keep CERT tests focused, traceable, and transport-neutral.

Tasks:

- [ ] Ensure every CERT test has the requirement ID in the filename.
- [ ] Ensure every CERT test starts with a short comment naming the requirement being exercised.
- [ ] Keep each CERT test focused on one primary behavior.
- [ ] Avoid sleeps unless the behavior is inherently asynchronous.
- [ ] Replace broad `assert(...)` messages with specific failure messages where useful.
- [ ] Confirm all tests link only to `ARCAL_CERT_CAL_LIB`.
- [ ] Do not call `Externalizer` APIs from conformance tests unless a future requirement explicitly targets that API.

Verification:

```bash
ctest --test-dir build -R "^CERT-" --output-on-failure
```

## P1: Broaden CERT Behavior Coverage

Add more requirement-level runtime tests where the behavior is observable through the public CAL API.

Tasks:

- [ ] Add tests for ASB lifecycle behavior:
  - initialization success
  - shutdown idempotence or documented post-shutdown behavior
  - status before and after shutdown
- [ ] Add tests for status listener behavior:
  - immediate callback on registration
  - no callback after removal
  - multiple listeners receive state changes
- [ ] Add tests for UUID behavior:
  - system/service/subsystem/component/capability UUID stability
  - unique service UUIDs for distinct service identifiers
  - repeated lookup stability for same component/capability names
- [ ] Add tests for topic behavior:
  - one topic associated with one message type
  - independent topics do not cross-deliver
  - multiple readers and writers on the same topic behave consistently
- [ ] Add tests for reader/writer lifecycle:
  - `close()` prevents further use as required or documented
  - destroy functions close resources cleanly
  - read timeout semantics
  - read-no-wait semantics
- [ ] Keep message-content tests format-agnostic:
  - publish via CAL writer
  - receive via CAL reader
  - compare public accessor values
  - never inspect wire bytes or serialization whitespace

Verification:

```bash
ctest --test-dir build -R "^(CERT|E2E)-" --output-on-failure
```

## P1: Generated Message Runtime Coverage

Exercise representative generated message shapes without turning this repository into a schema compiler test suite.

Tasks:

- [ ] Pick a small set of representative generated message types:
  - scalar field
  - enum field
  - choice field
  - unbounded list field
  - bounded list field
  - inherited/base fields
  - nested complex field
- [ ] Add runtime round-trip checks through CAL writer/reader APIs.
- [ ] Add E2E publish/subscribe checks only where transport behavior matters.
- [ ] Keep compile-only API-shape checks out of this repo unless they are necessary to build a runtime test.

Verification:

```bash
ctest --test-dir build -R "content|round|E2E-" --output-on-failure
```

## P1: Runtime Portability

Make failures easy to attribute to a CAL implementation or environment.

Tasks:

- [ ] Document that transport configuration belongs in the parent project.
- [ ] Keep examples for `ARCAL_CERT_TEST_ENV` generic.
- [ ] Avoid hard-coded paths in scripts and tests.
- [ ] Ensure shell scripts inherit CTest environment variables rather than setting transport variables themselves.
- [ ] Consider a minimal "environment sanity" test label for parent projects that want to diagnose transport setup separately.

Verification:

```bash
ctest --test-dir build -R "^E2E-" --output-on-failure
```

## P2: Developer Workflow

Make daily use boring and predictable.

Tasks:

- [ ] Keep `README.md` and `PLAN.md` aligned on CMake variable names.
- [ ] Add a short "Common commands" section to `README.md`.
- [ ] Add CTest labels and document common filters.
- [ ] Add a maintainer checklist for new CERT tests:
  - requirement ID
  - public API only
  - transport-neutral
  - CMake helper choice
  - matrix row
- [ ] Consider adding CI examples for parent projects.

Common commands:

```bash
cmake --build build
ctest --test-dir build -R "^CERT-" --output-on-failure
ctest --test-dir build -R "^E2E-" --output-on-failure
ctest --test-dir build -R "^(CERT|E2E)-" --output-on-failure
```

## Boundaries

- `arcal-cert` owns portable CERT and E2E conformance tests, including public API compile/link checks where practical.
- Parent projects own transport configuration and implementation-specific setup.
- CAL implementations may add their own implementation-specific compile/link checks outside `arcal-cert`.
- Tests should prefer public CAL APIs over implementation knowledge, even when implementation-specific shortcuts would be easier.
