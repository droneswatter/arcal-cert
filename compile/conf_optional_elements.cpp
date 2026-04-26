// Compile-only conformance: optional element accessor methods
// OMSC-SPC-008 RevK §9595-9762
//
// CERT IDs:
//   CXX-011229  hasX()
//   CXX-011230  enableX(AccessorType = null) for complex types
//   CXX-012709  enableX() for binary/list/simple primitive wrappers
//   CXX-011231  clearX() -> Parent&
//   CXX-012708  setX(const T&) -> Parent& for optional primitive fields

#include "uci/base/accessorType.h"
#include "uci/type/ACO_FileTraceabilityType.h"
#include "uci/type/ACO_TraceabilityType.h"
#include "uci/type/ACTDF_CollectionPlanType.h"
#include "uci/type/ActionActivityType.h"
#include "uci/type/CommConnectionType.h"
#include "uci/type/MetricCollectionType.h"
#include "uci/type/OpPointMT.h"
#include "uci/type/PO_ComponentStatusFilterType.h"

#include <cstdint>
#include <type_traits>

namespace check_aco_traceability {
using T = uci::type::ACO_TraceabilityType;
using ElemType = uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasACO_Identifier)>);
static_assert(std::is_same_v<ElemType& (T::*)(), decltype(&T::enableACO_Identifier)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearACO_Identifier)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setACO_Identifier(
    std::declval<const ElemType&>()))>);
}

namespace check_aco_file_traceability {
using T = uci::type::ACO_FileTraceabilityType;
using ElemType = uci::type::FileMetadataID_Type;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasFileID)>);
static_assert(std::is_same_v<
    ElemType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableFileID)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearFileID)>);
}

namespace check_actdf_collection_plan {
using T = uci::type::ACTDF_CollectionPlanType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasVersion)>);
static_assert(std::is_same_v<double& (T::*)(), decltype(&T::enableVersion)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearVersion)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setVersion(
    std::declval<const double&>()))>);
}

namespace check_metric_collection {
using T = uci::type::MetricCollectionType;
using ObsType = uci::type::ObservationsPerTrackLimitsType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasNumberOfObservations)>);
static_assert(std::is_same_v<
    ObsType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableNumberOfObservations)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearNumberOfObservations)>);

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasSpacingOfObservations)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearSpacingOfObservations)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setSpacingOfObservations(
    std::declval<const int32_t&>()))>);
}

namespace check_comm_connection {
using T = uci::type::CommConnectionType;
using DateTimeType = uci::type::DateTimeType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasNetworkTime)>);
// DateTimeType is generated as a string-family simple primitive wrapper in ARCAL,
// so the RevK primitive-style no-arg enableX() path applies here.
static_assert(std::is_same_v<DateTimeType& (T::*)(), decltype(&T::enableNetworkTime)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearNetworkTime)>);

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasNetworkTimeUncertaintyRange)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearNetworkTimeUncertaintyRange)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setNetworkTimeUncertaintyRange(
    std::declval<const float&>()))>);
}

namespace check_po_filter {
using T = uci::type::PO_ComponentStatusFilterType;
using BandType = uci::type::PO_ComponentStatusBandpassFrequencyType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasBandpassFrequency)>);
static_assert(std::is_same_v<
    BandType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableBandpassFrequency)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearBandpassFrequency)>);
}

namespace check_action_activity {
using T = uci::type::ActionActivityType;
using TraceType = uci::type::TraceabilityType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasTraceability)>);
static_assert(std::is_same_v<
    TraceType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableTraceability)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearTraceability)>);
}

namespace check_op_point_mt {
using T = uci::type::OpPointMT;
using EnumType = uci::type::ObjectStateEnum;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasObjectState)>);
static_assert(std::is_same_v<EnumType& (T::*)(), decltype(&T::enableObjectState)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearObjectState)>);
}
