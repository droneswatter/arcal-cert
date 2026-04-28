// Compile-only conformance: BoundedList element member patterns.

#include "uci/base/BoundedList.h"
#include "uci/base/accessorType.h"
#include "uci/type/CovarianceMatrixType.h"
#include "uci/type/EventSeverityEnum.h"
#include "uci/type/ServiceSettingType.h"
#include "uci/type/SubsystemEnabledSettingType.h"
#include "uci/type/SubsystemStateEnum.h"
#include "uci/type/SubsystemStatusMDT.h"

#include <type_traits>

static_assert(std::is_same_v<
    uci::type::SubsystemStatusMDT::CommandableSubsystemState,
    uci::base::BoundedList<uci::type::SubsystemStateEnum,
                           uci::type::accessorType::subsystemStateEnum>>);

static_assert(std::is_same_v<
    decltype(std::declval<const uci::type::SubsystemStatusMDT&>().getCommandableSubsystemState()),
    const uci::type::SubsystemStatusMDT::CommandableSubsystemState&>);
static_assert(std::is_same_v<
    decltype(std::declval<uci::type::SubsystemStatusMDT&>().getCommandableSubsystemState()),
    uci::type::SubsystemStatusMDT::CommandableSubsystemState&>);

using SetCommandableSubsystemStateFn =
    uci::type::SubsystemStatusMDT& (uci::type::SubsystemStatusMDT::*)
        (const uci::type::SubsystemStatusMDT::CommandableSubsystemState&);
static_assert(std::is_same_v<SetCommandableSubsystemStateFn,
    decltype(static_cast<SetCommandableSubsystemStateFn>(
        &uci::type::SubsystemStatusMDT::setCommandableSubsystemState))>);

static_assert(std::is_same_v<
    uci::type::SubsystemStatusMDT::EnabledSetting,
    uci::base::BoundedList<uci::type::SubsystemEnabledSettingType,
                           uci::type::accessorType::subsystemEnabledSettingType>>);

static_assert(std::is_same_v<
    uci::type::ServiceSettingType::EventSeverityClass,
    uci::base::BoundedList<uci::type::EventSeverityEnum,
                           uci::type::accessorType::eventSeverityEnum>>);

static_assert(std::is_same_v<
    uci::type::CovarianceMatrixType::Covariance,
    uci::base::BoundedList<uci::base::DoubleAccessor,
                           uci::base::accessorType::doubleAccessor>>);

static_assert(std::is_same_v<
    decltype(std::declval<const uci::type::CovarianceMatrixType&>().getCovariance()),
    const uci::type::CovarianceMatrixType::Covariance&>);
static_assert(std::is_same_v<
    decltype(std::declval<uci::type::CovarianceMatrixType&>().getCovariance()),
    uci::type::CovarianceMatrixType::Covariance&>);

using SetCovarianceFn =
    uci::type::CovarianceMatrixType& (uci::type::CovarianceMatrixType::*)
        (const uci::type::CovarianceMatrixType::Covariance&);
static_assert(std::is_same_v<SetCovarianceFn,
    decltype(static_cast<SetCovarianceFn>(
        &uci::type::CovarianceMatrixType::setCovariance))>);
