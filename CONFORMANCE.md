# arcal-cert Conformance Matrix

This matrix tracks the portable conformance coverage in `arcal-cert`. It is
intentionally implementation-neutral: parent projects provide the CAL target and
transport environment, while tests exercise only the public CAL API.

Status values:

- `covered` — directly exercised by an automated test in this repository.
- `partial` — exercised indirectly or incompletely; notes describe the gap.
- `planned` — useful coverage not yet implemented.
- `blocked` — cannot be covered portably with the current public API.
- `not applicable` — requirement does not apply to the C++ CAL conformance
  surface tested here.

## CERT Requirements

| Requirement | Area | Test type | Test file | Status | Notes |
|---|---|---|---|---|---|
| CERT-CAL-005201 | ASB lifecycle | Runtime | [cert/CAL-005201.cpp](cert/CAL-005201.cpp) | covered | Verifies initialized ASB creation, `NORMAL` status, and valid service UUID. |
| CERT-CAL-005202 | ASB identity | Runtime | [cert/CAL-005202.cpp](cert/CAL-005202.cpp) | covered | Verifies same service/ASB identifiers produce stable service UUIDs and distinct service labels produce distinct UUIDs. |
| CERT-CAL-005203 | UUID accessors | Runtime | [cert/CAL-005203.cpp](cert/CAL-005203.cpp) | partial | Verifies non-nil system/service/subsystem/component/capability UUIDs and distinct names. Repeated lookup stability remains planned. |
| CERT-CAL-005204 | Error reporting | Runtime | [cert/CAL-005204.cpp](cert/CAL-005204.cpp) | partial | Verifies status/listener error-state reporting through shutdown. A portable forced initialization-failure scenario remains planned or parent-specific. |
| CERT-CAL-005208 | Topic/type association | Runtime | [cert/CAL-005208.cpp](cert/CAL-005208.cpp) | partial | Verifies typed reader/writer creation on a topic. Negative mismatched-type behavior remains planned if expressible through public APIs. |
| CERT-CAL-005209 | Client topic mapping | Runtime | [cert/CAL-005209.cpp](cert/CAL-005209.cpp) | covered | Verifies client-facing topic names can be used to create matching typed readers and writers. |
| CERT-CAL-005210 | Per-topic QoS | Runtime | [cert/CAL-005210.cpp](cert/CAL-005210.cpp) | partial | Verifies independent client topics can coexist. Direct QoS policy assertion depends on public API coverage and remains planned. |
| CERT-CAL-016015 | Multiple clients | Runtime | [cert/CAL-016015.cpp](cert/CAL-016015.cpp) | partial | Verifies distinct service UUIDs for multiple CAL clients in one process. Full same-as-separate-process pub/sub behavior is supported by E2E tests. |
| CERT-CAL-016366 | Status listener | Runtime | [cert/CAL-016366.cpp](cert/CAL-016366.cpp) | covered | Verifies listener registration immediately reports current ASB status. |

## Supplemental E2E Coverage

These tests are not one-to-one CERT rows, but they support conformance claims by
exercising portable public-API behavior against the parent implementation.

| Behavior | Area | Test type | Test file | Status | Notes |
|---|---|---|---|---|---|
| ActionCommand publish/subscribe | Pub/sub | E2E runtime | [e2e/pub_action_command.cpp](e2e/pub_action_command.cpp), [e2e/sub_action_command.cpp](e2e/sub_action_command.cpp), [e2e/run_e2e_action_command.sh.in](e2e/run_e2e_action_command.sh.in) | covered | Two-process publish/subscribe smoke test. |
| Topic isolation | Pub/sub | E2E runtime | [e2e/topic_isolation.cpp](e2e/topic_isolation.cpp), [e2e/run_e2e_topic_isolation.sh.in](e2e/run_e2e_topic_isolation.sh.in) | covered | Verifies messages on one topic are not delivered through another topic. |
| Content fidelity | Accessor round trip | E2E runtime | [e2e/content_fidelity.cpp](e2e/content_fidelity.cpp) | covered | Verifies selected public accessor values survive CAL delivery. |
| Multiple messages | Reader/writer behavior | E2E runtime | [e2e/multi_message.cpp](e2e/multi_message.cpp) | covered | Verifies multiple sequential messages are delivered. |
| Listener lifecycle | Listener behavior | E2E runtime | [e2e/listener_lifecycle.cpp](e2e/listener_lifecycle.cpp) | covered | Verifies data listener delivery and removal behavior. |
| Two writers, one reader | Pub/sub fan-in | E2E runtime | [e2e/two_writers_one_reader.cpp](e2e/two_writers_one_reader.cpp) | covered | Verifies one reader can receive from two writers. |
| Two readers, one writer | Pub/sub fan-out | E2E runtime | [e2e/two_readers_one_writer.cpp](e2e/two_readers_one_writer.cpp) | covered | Verifies two readers can independently receive from one writer. |
| Empty readNoWait | Reader behavior | E2E runtime | [e2e/readnowait_empty.cpp](e2e/readnowait_empty.cpp) | covered | Verifies non-blocking empty read semantics. |
| Read timeout | Reader behavior | E2E runtime | [e2e/read_timeout.cpp](e2e/read_timeout.cpp) | covered | Verifies blocking read timeout semantics. |

## Planned Portable Coverage

| Requirement | Area | Test type | Test file | Status | Notes |
|---|---|---|---|---|---|
| CERT-CAL-005203 | UUID accessors | Runtime | planned | planned | Repeated component/capability lookup stability for identical names. |
| CERT-CAL-005204 | Error reporting | Runtime | planned | planned | Parent-injected initialization failure, if a transport-neutral trigger can be defined. |
| CERT-CAL-005208 | Topic/type association | Runtime | planned | planned | Negative test for one topic associated with multiple message types, if public API behavior is specified. |
| CERT-CAL-005210 | Per-topic QoS | Runtime | planned | planned | Direct QoS configuration/assertion through public CAL API, if exposed by the binding. |
| CERT-CAL-016015 | Multiple clients | Runtime | planned | planned | Stronger same-address-space pub/sub comparison for multiple service clients. |
| planned | ASB lifecycle | Runtime | planned | planned | Shutdown idempotence and documented post-shutdown behavior. |
| planned | Status listener | Runtime | planned | planned | No callback after removal and multiple listeners receiving state changes. |
| planned | Reader/writer lifecycle | Runtime | planned | planned | `close()` and destroy semantics after resource teardown. |
| planned | Generated message shapes | E2E runtime | planned | planned | Representative choice, bounded list, inherited/base-field, and nested complex-field message round trips. |
