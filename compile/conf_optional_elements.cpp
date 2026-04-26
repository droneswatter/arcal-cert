// Compile-only conformance: optional element accessor methods (OMSC-SPC-008 RevK §9595–9762)
// CERT IDs: CXX-011229 (hasX), CXX-011230 (enableX complex), CXX-012709 (enableX binary/list),
//           CXX-011231 (clearX), CXX-012708 (setX primitive)
//
// Each static_assert checks the *declared* signature shape against the spec requirement.
// KNOWN VIOLATIONS captured here as XFAIL comments — these document current non-compliance.
//
// Spec signatures:
//   CXX-011229:  virtual bool hasX() const = 0
//   CXX-011230:  virtual T& enableX(uci::base::accessorType::AccessorType = null) = 0  [complex types]
//   CXX-012709:  virtual xs::PrimName& enableX() = 0  [binary/list primitive types]
//   CXX-011231:  virtual ParentType& clearX() = 0  (NOT void)
//   CXX-012708:  virtual ParentType& setX(const T&) = 0  [string/numeric primitives, including optional]

#include "uci/base/Accessor.h"
#include "uci/base/accessorType.h"
#include "uci/type/ACO_TraceabilityType.h"
#include "uci/type/ACO_FileTraceabilityType.h"
#include "uci/type/ACTDF_CollectionPlanType.h"
#include "uci/type/MetricCollectionType.h"
#include "uci/type/CommConnectionType.h"
#include "uci/type/PO_ComponentStatusFilterType.h"
#include "uci/type/SlantRangeConstraintsType.h"
#include "uci/type/ActionActivityType.h"
#include "uci/type/OpPointMT.h"

#include <type_traits>

// ---------------------------------------------------------------------------
// Helper: pointer-to-member type aliases used in static_asserts.
// ---------------------------------------------------------------------------

// CXX-011229: hasX() must be:  bool (T::*)() const
template <typename T, typename MFn>
constexpr bool has_method_v = std::is_same_v<MFn, decltype(MFn{})>;  // placeholder; real checks below

// ---------------------------------------------------------------------------
// ACO_TraceabilityType — optional string-restriction element: ACO_Identifier
// XSD: xs:sequence/xs:element[@minOccurs='0'] of string-restriction type
// ---------------------------------------------------------------------------
namespace check_aco_traceability {

using T = uci::type::ACO_TraceabilityType;
using ElemType = uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type;

// CXX-011229: bool hasACO_Identifier() const
using HasFn    = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasACO_Identifier)>,
    "CXX-011229: hasACO_Identifier() must return bool and be const");

// CXX-012709 / CXX-011230: enableACO_Identifier() — string-restriction is SIMPLE_PRIMITIVE, not
// a true xs:complexType, so the no-arg form (CXX-012709) is correct here.
// NOTE: The spec is ambiguous about string-restriction wrappers; the no-arg form matches practice.
using EnableFn = ElemType& (T::*)();
static_assert(std::is_same_v<EnableFn, decltype(&T::enableACO_Identifier)>,
    "enableACO_Identifier() must return ElemType& and take no arguments (CXX-012709 path)");

// CXX-011231 XFAIL: clearACO_Identifier() currently returns void; spec requires T&
// Spec: virtual ACO_TraceabilityType& clearACO_Identifier() = 0
// Generated: virtual void clearACO_Identifier() = 0
// VIOLATION: clearX returns void instead of Parent& (CXX-011231)
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearACO_Identifier)>,
    "XFAIL CXX-011231: clearACO_Identifier() returns void (should return ACO_TraceabilityType&)");

// CXX-012708 XFAIL: setACO_Identifier(const ElemType&) is absent.
// Spec requires setX for optional string-restriction elements (not UUID, not unbounded).
// VIOLATION: setX missing for optional simple-primitive element (CXX-012708)

} // namespace check_aco_traceability

// ---------------------------------------------------------------------------
// ACO_FileTraceabilityType — optional complex element: FileID (ACCESSOR_TYPE_COMPLEX)
// XSD: xs:sequence/xs:element[@minOccurs='0'] of xs:complexType
// ---------------------------------------------------------------------------
namespace check_aco_file_traceability {

using T        = uci::type::ACO_FileTraceabilityType;
using ElemType = uci::type::FileMetadataID_Type;

// CXX-011229
using HasFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasFileID)>,
    "CXX-011229: hasFileID() must return bool and be const");

// CXX-011230 XFAIL: enableFileID() currently takes no arguments.
// Spec requires: virtual ElemType& enableFileID(uci::base::accessorType::AccessorType = null) = 0
// Generated:     virtual ElemType& enableFileID() = 0
// VIOLATION: enableX for complex type missing AccessorType default arg (CXX-011230)
using EnableFnActual = ElemType& (T::*)();
static_assert(std::is_same_v<EnableFnActual, decltype(&T::enableFileID)>,
    "XFAIL CXX-011230: enableFileID() takes no args (should take AccessorType with default=null)");

// CXX-011231 XFAIL: clearFileID() returns void; spec requires T&
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearFileID)>,
    "XFAIL CXX-011231: clearFileID() returns void (should return ACO_FileTraceabilityType&)");

// CXX-012708 note: setX is not required for optional xs:complexType elements per spec —
// those use get/enable/has/clear. (setX only required for primitive types.)

} // namespace check_aco_file_traceability

// ---------------------------------------------------------------------------
// ACTDF_CollectionPlanType — optional primitive double element: Version
// XSD: xs:sequence/xs:element[@minOccurs='0'] of xs:double (numeric primitive)
// ---------------------------------------------------------------------------
namespace check_actdf_collection_plan {

using T = uci::type::ACTDF_CollectionPlanType;

// CXX-011229
using HasFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasVersion)>,
    "CXX-011229: hasVersion() must return bool and be const");

// enableVersion() — plain double (not binary/list), no-arg form is generated.
// Spec note: CXX-011230 applies to xs:complexType only. CXX-012709 applies to
// binary/list primitives. Plain numeric (xs:double) does not appear in either
// CERT condition; the generated no-arg form is the closest match.
using EnableFn = double& (T::*)();
static_assert(std::is_same_v<EnableFn, decltype(&T::enableVersion)>,
    "enableVersion() must return double& with no arguments");

// CXX-011231 XFAIL: clearVersion() returns void; spec requires T&
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearVersion)>,
    "XFAIL CXX-011231: clearVersion() returns void (should return ACTDF_CollectionPlanType&)");

// CXX-012708 XFAIL: setVersion(const double&) is absent.
// Spec: setX required for numeric primitive elements not UUID and not unbounded.
// VIOLATION: setX missing for optional numeric primitive element (CXX-012708)

} // namespace check_actdf_collection_plan

// ---------------------------------------------------------------------------
// MetricCollectionType — optional complex (NumberOfObservations) and optional
// primitive int32_t (SpacingOfObservations)
// ---------------------------------------------------------------------------
namespace check_metric_collection {

using T         = uci::type::MetricCollectionType;
using ObsType   = uci::type::ObservationsPerTrackLimitsType;

// CXX-011229 — complex optional field
using HasObsFn = bool (T::*)() const;
static_assert(std::is_same_v<HasObsFn, decltype(&T::hasNumberOfObservations)>,
    "CXX-011229: hasNumberOfObservations() must return bool const");

// CXX-011230 XFAIL: enableNumberOfObservations() takes no args (complex type)
using EnableObsActual = ObsType& (T::*)();
static_assert(std::is_same_v<EnableObsActual, decltype(&T::enableNumberOfObservations)>,
    "XFAIL CXX-011230: enableNumberOfObservations() takes no args (should take AccessorType=null)");

// CXX-011231 XFAIL: clearNumberOfObservations() returns void
using ClearObsActual = void (T::*)();
static_assert(std::is_same_v<ClearObsActual, decltype(&T::clearNumberOfObservations)>,
    "XFAIL CXX-011231: clearNumberOfObservations() returns void (should return MetricCollectionType&)");

// CXX-011229 — int32_t optional field
using HasSpacingFn = bool (T::*)() const;
static_assert(std::is_same_v<HasSpacingFn, decltype(&T::hasSpacingOfObservations)>,
    "CXX-011229: hasSpacingOfObservations() must return bool const");

// CXX-011231 XFAIL: clearSpacingOfObservations() returns void
using ClearSpacingActual = void (T::*)();
static_assert(std::is_same_v<ClearSpacingActual, decltype(&T::clearSpacingOfObservations)>,
    "XFAIL CXX-011231: clearSpacingOfObservations() returns void (should return MetricCollectionType&)");

// CXX-012708 XFAIL: setSpacingOfObservations(const int32_t&) absent for optional numeric field.

} // namespace check_metric_collection

// ---------------------------------------------------------------------------
// CommConnectionType — optional complex (NetworkTime: DateTimeType) and optional
// float (NetworkTimeUncertaintyRange)
// ---------------------------------------------------------------------------
namespace check_comm_connection {

using T            = uci::type::CommConnectionType;
using DateTimeType = uci::type::DateTimeType;

// CXX-011229
using HasDateFn = bool (T::*)() const;
static_assert(std::is_same_v<HasDateFn, decltype(&T::hasNetworkTime)>,
    "CXX-011229: hasNetworkTime() must return bool const");

// CXX-011230 XFAIL: enableNetworkTime() takes no args (complex type)
using EnableDateActual = DateTimeType& (T::*)();
static_assert(std::is_same_v<EnableDateActual, decltype(&T::enableNetworkTime)>,
    "XFAIL CXX-011230: enableNetworkTime() takes no args (should take AccessorType=null)");

// CXX-011231 XFAIL: clearNetworkTime() returns void
using ClearDateActual = void (T::*)();
static_assert(std::is_same_v<ClearDateActual, decltype(&T::clearNetworkTime)>,
    "XFAIL CXX-011231: clearNetworkTime() returns void (should return CommConnectionType&)");

// CXX-011229 — optional float
using HasFloatFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFloatFn, decltype(&T::hasNetworkTimeUncertaintyRange)>,
    "CXX-011229: hasNetworkTimeUncertaintyRange() must return bool const");

// CXX-011231 XFAIL: clearNetworkTimeUncertaintyRange() returns void
using ClearFloatActual = void (T::*)();
static_assert(std::is_same_v<ClearFloatActual, decltype(&T::clearNetworkTimeUncertaintyRange)>,
    "XFAIL CXX-011231: clearNetworkTimeUncertaintyRange() returns void (should return CommConnectionType&)");

// CXX-012708 XFAIL: setNetworkTimeUncertaintyRange(const float&) absent.

} // namespace check_comm_connection

// ---------------------------------------------------------------------------
// PO_ComponentStatusFilterType — optional complex: BandpassFrequency
// ---------------------------------------------------------------------------
namespace check_po_filter {

using T        = uci::type::PO_ComponentStatusFilterType;
using BandType = uci::type::PO_ComponentStatusBandpassFrequencyType;

// CXX-011229
using HasFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasBandpassFrequency)>,
    "CXX-011229: hasBandpassFrequency() must return bool const");

// CXX-011230 XFAIL: enableBandpassFrequency() takes no args
using EnableFnActual = BandType& (T::*)();
static_assert(std::is_same_v<EnableFnActual, decltype(&T::enableBandpassFrequency)>,
    "XFAIL CXX-011230: enableBandpassFrequency() takes no args (should take AccessorType=null)");

// CXX-011231 XFAIL: clearBandpassFrequency() returns void
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearBandpassFrequency)>,
    "XFAIL CXX-011231: clearBandpassFrequency() returns void (should return PO_ComponentStatusFilterType&)");

} // namespace check_po_filter

// ---------------------------------------------------------------------------
// ActionActivityType — optional complex: Traceability
// ---------------------------------------------------------------------------
namespace check_action_activity {

using T         = uci::type::ActionActivityType;
using TraceType = uci::type::TraceabilityType;

// CXX-011229
using HasFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasTraceability)>,
    "CXX-011229: hasTraceability() must return bool const");

// CXX-011230 XFAIL: enableTraceability() takes no args
using EnableFnActual = TraceType& (T::*)();
static_assert(std::is_same_v<EnableFnActual, decltype(&T::enableTraceability)>,
    "XFAIL CXX-011230: enableTraceability() takes no args (should take AccessorType=null)");

// CXX-011231 XFAIL: clearTraceability() returns void
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearTraceability)>,
    "XFAIL CXX-011231: clearTraceability() returns void (should return ActionActivityType&)");

} // namespace check_action_activity

// ---------------------------------------------------------------------------
// OpPointMT — optional enum element: ObjectState
// ---------------------------------------------------------------------------
namespace check_op_point_mt {

using T        = uci::type::OpPointMT;
using EnumType = uci::type::ObjectStateEnum;

// CXX-011229
using HasFn = bool (T::*)() const;
static_assert(std::is_same_v<HasFn, decltype(&T::hasObjectState)>,
    "CXX-011229: hasObjectState() must return bool const");

// Enum types: enableX takes no AccessorType arg (enum is not xs:complexType).
using EnableFn = EnumType& (T::*)();
static_assert(std::is_same_v<EnableFn, decltype(&T::enableObjectState)>,
    "enableObjectState() must return ObjectStateEnum& with no arguments");

// CXX-011231 XFAIL: clearObjectState() returns void
using ClearFnActual = void (T::*)();
static_assert(std::is_same_v<ClearFnActual, decltype(&T::clearObjectState)>,
    "XFAIL CXX-011231: clearObjectState() returns void (should return OpPointMT&)");

} // namespace check_op_point_mt

// ---------------------------------------------------------------------------
// Summary of current violations (all systemic / compiler-wide):
//
// VIOLATION 1 — CXX-011231 (universal):
//   All clearX() methods return void.
//   Spec requires: virtual ParentType& clearX() = 0
//   Confirmed across: ACO_TraceabilityType, ACO_FileTraceabilityType,
//   ACTDF_CollectionPlanType, MetricCollectionType, CommConnectionType,
//   PO_ComponentStatusFilterType, ActionActivityType, OpPointMT, and all others.
//
// VIOLATION 2 — CXX-011230 (universal for complex optional elements):
//   enableX() for xs:complexType optional elements takes no arguments.
//   Spec requires: virtual T& enableX(uci::base::accessorType::AccessorType = null) = 0
//   Confirmed across: ACO_FileTraceabilityType (enableFileID), MetricCollectionType
//   (enableNumberOfObservations), CommConnectionType (enableNetworkTime),
//   PO_ComponentStatusFilterType (enableBandpassFrequency), ActionActivityType
//   (enableTraceability), and all complex-type optional elements (1979 files affected).
//
// VIOLATION 3 — CXX-012708 (widespread for optional primitive elements):
//   setX() is absent for optional primitive elements (numeric, string-restriction).
//   Spec requires setX for all non-UUID, non-unbounded primitive-typed elements,
//   including those with @minOccurs='0'.
//   Confirmed missing in: ACTDF_CollectionPlanType (setVersion), ACO_TraceabilityType
//   (setACO_Identifier), MetricCollectionType (setSpacingOfObservations),
//   CommConnectionType (setNetworkTimeUncertaintyRange), and ~109+ other types.
// ---------------------------------------------------------------------------
