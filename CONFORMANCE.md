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
| CERT-CAL-005201 | ASB lifecycle | Runtime | [cert/CAL-005201.cpp](cert/CAL-005201.cpp) | covered | Verifies initialized ASB creation, `NORMAL` status, valid service UUID, and idempotent shutdown behavior. |
| CERT-CAL-005202 | ASB identity | Runtime | [cert/CAL-005202.cpp](cert/CAL-005202.cpp) | covered | Verifies same service/ASB identifiers produce stable service UUIDs and distinct service labels produce distinct UUIDs. |
| CERT-CAL-005203 | UUID accessors | Runtime | [cert/CAL-005203.cpp](cert/CAL-005203.cpp) | covered | Verifies non-nil system/service/subsystem/component/capability UUIDs, distinct names, and repeated lookup stability. |
| CERT-CAL-005204 | Error reporting | Runtime | [cert/CAL-005204.cpp](cert/CAL-005204.cpp) | partial | Verifies status/listener error-state reporting through shutdown. A portable forced initialization-failure scenario remains planned or parent-specific. |
| CERT-CAL-005208 | Topic/type association | Runtime | [cert/CAL-005208.cpp](cert/CAL-005208.cpp) | partial | Verifies typed reader/writer creation on a topic. Negative mismatched-type behavior remains planned if expressible through public APIs. |
| CERT-CAL-005209 | Client topic mapping | Runtime | [cert/CAL-005209.cpp](cert/CAL-005209.cpp) | covered | Verifies client-facing topic names can be used to create matching typed readers and writers. |
| CERT-CAL-005210 | Per-topic QoS | Runtime | [cert/CAL-005210.cpp](cert/CAL-005210.cpp) | partial | Verifies independent client topics can coexist. Direct QoS policy assertion depends on public API coverage and remains planned. |
| CERT-CAL-016015 | Multiple clients | Runtime | [cert/CAL-016015.cpp](cert/CAL-016015.cpp) | covered | Verifies distinct service UUIDs and same-process pub/sub between two CAL clients. |
| CERT-CAL-016366 | Status listener | Runtime | [cert/CAL-016366.cpp](cert/CAL-016366.cpp) | covered | Verifies listener registration immediately reports current ASB status, removed listeners stop receiving updates, and multiple listeners receive state changes. |

## Supplemental E2E Coverage

These tests are not one-to-one CERT rows, but they support conformance claims by
exercising portable public-API behavior against the parent implementation.

| Behavior | Area | Test type | Test file | Status | Notes |
|---|---|---|---|---|---|
| ServiceStatus publish/subscribe | Pub/sub | E2E runtime | [e2e/pub_action_command.cpp](e2e/pub_action_command.cpp), [e2e/sub_action_command.cpp](e2e/sub_action_command.cpp), [e2e/run_e2e_action_command.sh.in](e2e/run_e2e_action_command.sh.in) | covered | Two-process publish/subscribe smoke test. |
| Topic isolation | Pub/sub | E2E runtime | [e2e/topic_isolation.cpp](e2e/topic_isolation.cpp), [e2e/run_e2e_topic_isolation.sh.in](e2e/run_e2e_topic_isolation.sh.in) | covered | Verifies messages on one topic are not delivered through another topic. |
| Content fidelity | Accessor round trip | E2E runtime | [e2e/content_fidelity.cpp](e2e/content_fidelity.cpp) | covered | Verifies selected public accessor values survive CAL delivery. |
| Multiple messages | Reader/writer behavior | E2E runtime | [e2e/multi_message.cpp](e2e/multi_message.cpp) | covered | Verifies multiple sequential messages are delivered. |
| Listener lifecycle | Listener behavior | E2E runtime | [e2e/listener_lifecycle.cpp](e2e/listener_lifecycle.cpp) | covered | Verifies data listener delivery and removal behavior. |
| Two writers, one reader | Pub/sub fan-in | E2E runtime | [e2e/two_writers_one_reader.cpp](e2e/two_writers_one_reader.cpp) | covered | Verifies one reader can receive from two writers. |
| Two readers, one writer | Pub/sub fan-out | E2E runtime | [e2e/two_readers_one_writer.cpp](e2e/two_readers_one_writer.cpp) | covered | Verifies two readers can independently receive from one writer. |
| Empty readNoWait | Reader behavior | E2E runtime | [e2e/readnowait_empty.cpp](e2e/readnowait_empty.cpp) | covered | Verifies non-blocking empty read semantics. |
| Read timeout | Reader behavior | E2E runtime | [e2e/read_timeout.cpp](e2e/read_timeout.cpp) | covered | Verifies blocking read timeout semantics. |
| Reader/writer close | Reader/writer lifecycle | E2E runtime | [e2e/reader_writer_close.cpp](e2e/reader_writer_close.cpp) | covered | Verifies read, readNoWait, and write operations throw after close. |

## Compile-Only API Shape Coverage (OMSC-SPC-008 RevK)

These tests verify the public C++ header API shapes mandated by the C++ CAL Spec.
Successful compilation is the test — no DDS or runtime required.
Successful compilation is the test; conformance gaps should be represented by
active failing checks, not hidden behind preprocessor guards.

| Rule family | CERTs covered | Test file | Status | Notes |
|---|---|---|---|---|
| Accessor base structure (inheritance, protected lifecycle) | CXX-005456, CXX-011135, CXX-012705, CXX-005464, CXX-005465, CXX-011064 | [compile/conf_base_structure.cpp](compile/conf_base_structure.cpp) | covered | PASS. Covered accessor classes inherit the required base types and expose protected lifecycle. |
| Factory methods: create/destroy/copy/getUCITypeVersion | CXX-011063, CXX-011066, CXX-011067, CXX-011068, CXX-011410 | [compile/conf_factory_methods.cpp](compile/conf_factory_methods.cpp) | covered | PASS. `copy`, `create`, copy-create, `destroy`, and `getUCITypeVersion()` all match the expected generated shape, including default `= nullptr` support. |
| Required sequence element get/set pairs | CXX-011213–011220, CXX-011223, CXX-012706–012708 | [compile/conf_required_elements.cpp](compile/conf_required_elements.cpp) | covered | PASS. Required complex, primitive, string-family, and enum fields expose the expected getter/setter signatures in current generated headers. |
| Optional element has/enable/clear | CXX-011229, CXX-011230, CXX-011231, CXX-012709 | [compile/conf_optional_elements.cpp](compile/conf_optional_elements.cpp) | covered | PASS. Optional complex and primitive-style fields expose the expected `has`, `enable`, `clear`, and `set` signatures covered by the compile checks. |
| BoundedList inner typedef and accessors | CXX-007053, CXX-012712, CXX-012713, CXX-011226–011228 | [compile/conf_bounded_list_elements.cpp](compile/conf_bounded_list_elements.cpp) | covered | PASS. Inner typedef, correct accessorType constant, and setter generated for all BoundedList fields (TASK-005). |
| UUID element accessors | CXX-006154, CXX-011054 | [compile/conf_uuid_elements.cpp](compile/conf_uuid_elements.cpp) | covered | PASS. Returns by value, parent-ref setter, no spurious has/enable/clear. Spec example has erroneous void return; generated code correctly follows normative CERT text. |
| SimpleRestriction typedef pattern | CXX-006143, CXX-006144, CXX-006553 | [compile/conf_simple_restriction.cpp](compile/conf_simple_restriction.cpp) | covered | PASS. Non-enum `xs:restriction` types now generate typedef aliases, with companion `*Value` aliases for scalar restrictions. |
| Enumeration accessor shape | CXX-006211, CXX-006240, CXX-006323/340/357/374/391/408, CXX-006417, CXX-006424, CXX-006457, CXX-011062, CXX-011149 | [compile/conf_enum_extended.cpp](compile/conf_enum_extended.cpp) | covered | PASS. Extended enum API shape matches the RevK requirements covered by this compile test. |
| Choice accessor enum naming and methods | CXX-007137, CXX-007138, CXX-011109, CXX-011110, CXX-012695, CXX-012696 | [compile/conf_choice_accessor.cpp](compile/conf_choice_accessor.cpp) | covered | PASS. Enum renamed to `<T>Choice`; values use `<TYPENAME>_CHOICE_` prefix; `CHOICE_NONE = 0` first; `setChoiceOrdinal()` added; `choose()` accepts `AccessorType = null` for complex elements, while simple-restriction choice branches remain zero-argument (TASK-009). |
| MT nested Listener/Reader/Writer shape | CXX-005494/495/499/506, CXX-005546/564/567/608/615/624/653/660, CXX-011072–011080, CXX-012710/711 | [compile/conf_mt_shape.cpp](compile/conf_mt_shape.cpp) | covered | PASS. Nested Listener/Reader/Writer lifecycle and factory-access shape are covered. |

## Planned Portable Coverage

| Requirement | Area | Test type | Test file | Status | Notes |
|---|---|---|---|---|---|
| CERT-CAL-005204 | Error reporting | Runtime | planned | planned | Parent-injected initialization failure, if a transport-neutral trigger can be defined. |
| CERT-CAL-005208 | Topic/type association | Runtime | planned | planned | Negative test for one topic associated with multiple message types, if public API behavior is specified. |
| CERT-CAL-005210 | Per-topic QoS | Runtime | planned | planned | Direct QoS configuration/assertion through public CAL API, if exposed by the binding. |
| planned | Reader/writer lifecycle | Runtime | planned | planned | Destroy semantics after resource teardown. |
| planned | Generated message shapes | E2E runtime | planned | planned | Representative choice, bounded list, inherited/base-field, and nested complex-field message round trips. |
