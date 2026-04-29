// Compile-only conformance: required element accessor signatures.

#include "uci/type/EnvironmentEnum.h"
#include "uci/type/InertialStateType.h"
#include "uci/type/PositionReportMDT.h"
#include "uci/type/ServiceID_Type.h"
#include "uci/type/ServiceStateEnum.h"
#include "uci/type/ServiceStatusMDT.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/SubsystemStateEnum.h"
#include "uci/type/SubsystemStatusMDT.h"
#include "uci/type/SystemID_Type.h"
#include "uci/type/SystemSourceEnum.h"
#include "uci/type/SystemStateEnum.h"
#include "uci/type/SystemStatusMDT.h"

#include <type_traits>

static_assert(std::is_same_v<
    uci::type::ServiceID_Type&,
    decltype(std::declval<uci::type::ServiceStatusMDT&>().getServiceID())>);
static_assert(std::is_same_v<
    const uci::type::ServiceID_Type&,
    decltype(std::declval<const uci::type::ServiceStatusMDT&>().getServiceID())>);
static_assert(std::is_same_v<
    uci::type::ServiceStatusMDT&,
    decltype(std::declval<uci::type::ServiceStatusMDT&>().setServiceID(
        std::declval<const uci::type::ServiceID_Type&>()))>);

static_assert(std::is_same_v<
    uci::type::DurationType&,
    decltype(std::declval<uci::type::ServiceStatusMDT&>().getTimeUp())>);
static_assert(std::is_same_v<
    const uci::type::DurationType&,
    decltype(std::declval<const uci::type::ServiceStatusMDT&>().getTimeUp())>);
static_assert(std::is_same_v<
    uci::type::ServiceStatusMDT&,
    decltype(std::declval<uci::type::ServiceStatusMDT&>().setTimeUp(
        std::declval<const uci::type::DurationType&>()))>);

static_assert(std::is_same_v<
    uci::type::ServiceStatusMDT&,
    decltype(std::declval<uci::type::ServiceStatusMDT&>().setServiceState(
        uci::type::ServiceStateEnum::NORMAL))>);

static_assert(std::is_same_v<
    uci::type::SystemStatusMDT&,
    decltype(std::declval<uci::type::SystemStatusMDT&>().setSystemState(
        uci::type::SystemStateEnum::OPERATIONAL))>);
static_assert(std::is_same_v<
    uci::type::SystemStatusMDT&,
    decltype(std::declval<uci::type::SystemStatusMDT&>().setSource(
        uci::type::SystemSourceEnum::ACTUAL))>);

static_assert(std::is_same_v<
    uci::type::SubsystemID_Type&,
    decltype(std::declval<uci::type::SubsystemStatusMDT&>().getSubsystemID())>);
static_assert(std::is_same_v<
    uci::type::SubsystemStatusMDT&,
    decltype(std::declval<uci::type::SubsystemStatusMDT&>().setSubsystemState(
        uci::type::SubsystemStateEnum::OPERATE))>);

static_assert(std::is_same_v<
    uci::type::SystemID_Type&,
    decltype(std::declval<uci::type::PositionReportMDT&>().getSystemID())>);
static_assert(std::is_same_v<
    uci::type::InertialStateType&,
    decltype(std::declval<uci::type::PositionReportMDT&>().getInertialState())>);
static_assert(std::is_same_v<
    uci::type::PositionReportMDT&,
    decltype(std::declval<uci::type::PositionReportMDT&>().setCurrentOperatingDomain(
        uci::type::EnvironmentEnum::AIR))>);
