// Compile-only conformance: required element accessor signatures
// OMSC-SPC-008 RevK §9040-9460
//
// CERTs covered:
//   CXX-011213  non-static T& getX() for required complex element
//   CXX-011214  const T& getX() const for required complex element
//   CXX-011215  Parent& setX(const T&) for required complex element
//   CXX-011216  T getX() const (by-value) for simple primitive element
//   CXX-011217  Parent& setX(T) (by-value) for simple primitive element
//   CXX-011219  Parent& setX(const std::string&) for string primitive
//   CXX-011220  Parent& setX(const char*) for string primitive
//   CXX-011223  Parent& setX(Enum::EnumerationItem) for enum element
//   CXX-012706  xs::String& getX() for non-simple string/binary/list primitive
//   CXX-012707  const xs::String& getX() const for same
//   CXX-012708  Parent& setX(const xs::String&) for same

#include "uci/type/AMTI_ActivityMDT.h"
#include "uci/type/CropSettingsType.h"
#include "uci/type/ECEF_PositionPositionCovarianceType.h"
#include "uci/type/MsgNameReportMT.h"
#include "uci/type/ObjectStateEnum.h"
#include "uci/type/OrbitalRendezvousEventType.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/TurretReportID_Type.h"
#include "uci/type/TurretReportMDT.h"

#include <cstdint>
#include <string>
#include <type_traits>

// CXX-011213 / CXX-011214
static_assert(std::is_same_v<
    uci::type::TurretReportID_Type&,
    decltype(std::declval<uci::type::TurretReportMDT&>().getTurretReportID())>);
static_assert(std::is_same_v<
    const uci::type::TurretReportID_Type&,
    decltype(std::declval<const uci::type::TurretReportMDT&>().getTurretReportID())>);

static_assert(std::is_same_v<
    uci::type::SubsystemID_Type&,
    decltype(std::declval<uci::type::AMTI_ActivityMDT&>().getSubsystemID())>);
static_assert(std::is_same_v<
    const uci::type::SubsystemID_Type&,
    decltype(std::declval<const uci::type::AMTI_ActivityMDT&>().getSubsystemID())>);

// CXX-011215
static_assert(std::is_same_v<
    uci::type::TurretReportMDT&,
    decltype(std::declval<uci::type::TurretReportMDT&>().setTurretReportID(
        std::declval<const uci::type::TurretReportID_Type&>()))>);
static_assert(std::is_same_v<
    uci::type::AMTI_ActivityMDT&,
    decltype(std::declval<uci::type::AMTI_ActivityMDT&>().setSubsystemID(
        std::declval<const uci::type::SubsystemID_Type&>()))>);

// CXX-011216 / CXX-011217
static_assert(std::is_same_v<
    double,
    decltype(std::declval<const uci::type::ECEF_PositionPositionCovarianceType&>().getPxPx())>);
static_assert(std::is_same_v<
    uint32_t,
    decltype(std::declval<const uci::type::CropSettingsType&>().getX_Position())>);

static_assert(std::is_same_v<
    uci::type::ECEF_PositionPositionCovarianceType&,
    decltype(std::declval<uci::type::ECEF_PositionPositionCovarianceType&>().setPxPx(0.0))>);
static_assert(std::is_same_v<
    uci::type::CropSettingsType&,
    decltype(std::declval<uci::type::CropSettingsType&>().setX_Position(uint32_t{0}))>);

// CXX-012706 / CXX-012707 / CXX-012708 / CXX-011219 / CXX-011220
static_assert(std::is_same_v<
    std::string&,
    decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().getMinimumRangeAnalysisDuration())>);
static_assert(std::is_same_v<
    const std::string&,
    decltype(std::declval<const uci::type::OrbitalRendezvousEventType&>().getMinimumRangeAnalysisDuration())>);
static_assert(std::is_same_v<
    uci::type::OrbitalRendezvousEventType&,
    decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().setMinimumRangeAnalysisDuration(
        std::declval<const std::string&>()))>);
static_assert(std::is_same_v<
    uci::type::OrbitalRendezvousEventType&,
    decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().setMinimumRangeAnalysisDuration(
        static_cast<const char*>(nullptr)))>);

// Optional enum getter pair still uses enable/get/clear shape.
static_assert(std::is_same_v<
    uci::type::ObjectStateEnum&,
    decltype(std::declval<uci::type::MsgNameReportMT&>().getObjectState())>);
static_assert(std::is_same_v<
    const uci::type::ObjectStateEnum&,
    decltype(std::declval<const uci::type::MsgNameReportMT&>().getObjectState())>);

// CXX-011223
static_assert(std::is_same_v<
    uci::type::MsgNameReportMT&,
    decltype(std::declval<uci::type::MsgNameReportMT&>().setObjectState(
        uci::type::ObjectStateEnum::NEW))>);
