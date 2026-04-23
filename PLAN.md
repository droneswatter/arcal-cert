# arcal-cert Plan

`arcal-cert` is the portable conformance suite for C++ CAL implementations. It
should stay transport-agnostic: the parent project supplies the CAL target and
any transport environment variables.

## Current Contract

Keep the repository easy for any CAL implementation to consume as a CMake
subdirectory.

- `ARCAL_CERT_CAL_LIB` is the only required integration variable.
- `ARCAL_CERT_TEST_ENV` is the transport environment injection mechanism.
- Tests link only to `ARCAL_CERT_CAL_LIB`.
- Tests use public CAL headers and APIs only.
- Transport setup, private implementation checks, and generated build paths
  belong to the parent implementation project.

## P0: Requirements Traceability

Add a requirements matrix so coverage is explicit and reviewable.

- Add `CONFORMANCE.md`.
- Include every existing `CERT-CAL-*` test.
- Mark uncovered requirements as `planned`, not implied.
- Use stable statuses: `covered`, `partial`, `planned`, `blocked`,
  `not applicable`.
- Link each covered row to the test file.
- Note when a requirement is better covered by implementation-specific tests
  outside `arcal-cert`.

Verification:

```bash
rg -n "CERT-CAL-|planned|partial|blocked" CONFORMANCE.md
```

## P0: Test Metadata

Make the existing suite easier to filter and audit.

- Add CTest labels:
  - `cert`
  - `e2e`
  - `runtime`
- Ensure each CERT source file starts with a short requirement comment.
- Keep CERT filenames aligned with the requirement ID.
- Keep README, PLAN, and CMake variable names aligned.

Verification:

```bash
ctest --test-dir build -N
ctest --test-dir build -R "^CERT-" --output-on-failure
```

## P1: Remaining Coverage Gaps

The suite already covers the current CERT IDs listed in `README.md`, plus
representative E2E behavior: content fidelity, listener lifecycle, topic
isolation, two-reader/two-writer delivery, read timeout, and read-no-wait.

Useful remaining additions:

- ASB lifecycle behavior:
  - shutdown idempotence or documented post-shutdown behavior
  - status before and after shutdown
- Status listener behavior:
  - no callback after removal
  - multiple listeners receive state changes
- UUID behavior:
  - repeated lookup stability for same component/capability names
  - unique service UUIDs for distinct service identifiers
- Reader/writer lifecycle:
  - `close()` prevents further use as required or documented
  - destroy functions close resources cleanly
- Representative generated-message round trips:
  - choice
  - bounded list
  - inherited/base fields
  - nested complex field

Message-content tests should stay format-agnostic: publish via CAL writer,
receive via CAL reader, and compare public accessor values. They should not
inspect wire bytes or serialization whitespace.

## P2: Developer Workflow

- Add a short maintainer checklist for new CERT tests:
  - requirement ID
  - public API only
  - transport-neutral
  - CMake helper choice
  - matrix row
- Document common CTest label filters once labels exist.
- Consider small CI snippets for parent projects.

Common commands:

```bash
cmake --build build
ctest --test-dir build -R "^CERT-" --output-on-failure
ctest --test-dir build -R "^E2E-" --output-on-failure
ctest --test-dir build -R "^(CERT|E2E)-" --output-on-failure
```

## Boundaries

- `arcal-cert` owns portable CERT and E2E conformance tests.
- Parent projects own transport configuration and implementation-specific setup.
- CAL implementations may add private implementation checks outside
  `arcal-cert`.
- Tests should prefer public CAL APIs even when implementation-specific
  shortcuts would be easier.
