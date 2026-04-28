// Compile-only conformance: optional element accessor methods.

#include "uci/base/accessorType.h"
#include "uci/type/DateTimeType.h"
#include "uci/type/EntityFusionEligibilityEnum.h"
#include "uci/type/PlatformStatusType.h"
#include "uci/type/PositionReportMDT.h"
#include "uci/type/ProcessingStatusEnum.h"
#include "uci/type/SubsystemExtendedStatusPET.h"
#include "uci/type/SubsystemStatusMDT.h"
#include "uci/type/SystemIdentityType.h"
#include "uci/type/SystemStatusMDT.h"
#include "uci/type/VisibleString256Type.h"
#include "uci/type/VisibleString32Type.h"

#include <cstdint>
#include <type_traits>

namespace check_system_status_model {
using T = uci::type::SystemStatusMDT;
using ElemType = uci::type::VisibleString32Type;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasModel)>);
static_assert(std::is_same_v<ElemType& (T::*)(), decltype(&T::enableModel)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearModel)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setModel(
    std::declval<const ElemType&>()))>);
}

namespace check_system_status_identity {
using T = uci::type::SystemStatusMDT;
using ElemType = uci::type::SystemIdentityType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasIdentity)>);
static_assert(std::is_same_v<
    ElemType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableIdentity)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearIdentity)>);
}

namespace check_system_status_platform {
using T = uci::type::SystemStatusMDT;
using ElemType = uci::type::PlatformStatusType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasPlatformStatus)>);
static_assert(std::is_same_v<
    ElemType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enablePlatformStatus)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearPlatformStatus)>);
}

namespace check_subsystem_status_enum {
using T = uci::type::SubsystemStatusMDT;
using EnumType = uci::type::ProcessingStatusEnum;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasEraseStatus)>);
static_assert(std::is_same_v<EnumType& (T::*)(), decltype(&T::enableEraseStatus)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearEraseStatus)>);
}

namespace check_subsystem_status_extension {
using T = uci::type::SubsystemStatusMDT;
using ElemType = uci::type::SubsystemExtendedStatusPET;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasExtendedStatus)>);
static_assert(std::is_same_v<
    ElemType& (T::*)(uci::base::accessorType::AccessorType),
    decltype(&T::enableExtendedStatus)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearExtendedStatus)>);
}

namespace check_position_report_optionals {
using T = uci::type::PositionReportMDT;
using StringType = uci::type::VisibleString256Type;
using DateTimeType = uci::type::DateTimeType;

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasDisplayName)>);
static_assert(std::is_same_v<StringType& (T::*)(), decltype(&T::enableDisplayName)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearDisplayName)>);

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasTimestamp)>);
static_assert(std::is_same_v<DateTimeType& (T::*)(), decltype(&T::enableTimestamp)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearTimestamp)>);

static_assert(std::is_same_v<bool (T::*)() const, decltype(&T::hasSimulationTargetNumber)>);
static_assert(std::is_same_v<int64_t& (T::*)(), decltype(&T::enableSimulationTargetNumber)>);
static_assert(std::is_same_v<T& (T::*)(), decltype(&T::clearSimulationTargetNumber)>);
static_assert(std::is_same_v<T&, decltype(std::declval<T&>().setSimulationTargetNumber(
    std::declval<const int64_t&>()))>);
}
