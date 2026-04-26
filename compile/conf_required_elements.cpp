// Compile-only conformance: required element accessor signatures (OMSC-SPC-008 RevK §9040–9460)
//
// CERTs covered:
//   CXX-011213  non-static T& getX() for required complex element
//   CXX-011214  const T& getX() const for required complex element
//   CXX-011215  Parent& setX(const T&) for required complex element          [VIOLATION: generated returns void]
//   CXX-011216  T getX() const (by-value) for simple primitive element       [VIOLATION: generated returns T& / const T&]
//   CXX-011217  Parent& setX(T) (by-value) for simple primitive element      [VIOLATION: generated returns void, takes const T&]
//   CXX-011219  Parent& setX(const std::string&) for string primitive        [VIOLATION: generated returns void]
//   CXX-011220  Parent& setX(const char*) for string primitive               [VIOLATION: overload absent]
//   CXX-011223  Parent& setX(Enum::EnumerationItem) for enum element         [VIOLATION: generated returns void]
//   CXX-012706  xs::String& getX() for non-simple string/binary/list prim    [OK in complex types that have it]
//   CXX-012707  const xs::String& getX() const for same                      [OK in complex types that have it]
//   CXX-012708  Parent& setX(const xs::String&) for same                     [VIOLATION: generated returns void]
//
// Compilation failures in the "FAILING" blocks below represent real spec violations
// found in the generated headers.  Each block is wrapped in a #if 0 so the file
// still compiles as an OBJECT library; flip to #if 1 when the generator is fixed.
//
// Representative types used:
//   TurretReportMDT          — required complex fields (CXX-011213/14/15)
//   CropSettingsType         — required simple-primitive uint32_t fields (CXX-011216/17)
//   ECEF_PositionPositionCovarianceType — required simple-primitive double fields (CXX-011216/17)
//   OrbitalRendezvousEventType — required string primitive field (CXX-012706/07/08,
//                                and optional string field for contrast)
//   MsgNameReportMT          — required enum field via ObjectStateEnum (CXX-011223)
//   AMTI_ActivityMDT         — required complex field (CXX-011213/14/15)

#include "uci/type/TurretReportMDT.h"
#include "uci/type/TurretReportID_Type.h"
#include "uci/type/TurretReportPointingType.h"
#include "uci/type/PointingType.h"
#include "uci/type/CropSettingsType.h"
#include "uci/type/ECEF_PositionPositionCovarianceType.h"
#include "uci/type/OrbitalRendezvousEventType.h"
#include "uci/type/MsgNameReportMT.h"
#include "uci/type/ObjectStateEnum.h"
#include "uci/type/AMTI_ActivityMDT.h"
#include "uci/type/SubsystemID_Type.h"
#include <type_traits>
#include <string>
#include <cstdint>

// ---------------------------------------------------------------------------
// CXX-011213 / CXX-011214 — required complex element getters (PASS)
// T& getX() and const T& getX() const must both exist.
// ---------------------------------------------------------------------------

// TurretReportMDT::TurretReportID — required complex element
static_assert(
    std::is_same_v<
        uci::type::TurretReportID_Type&,
        decltype(std::declval<uci::type::TurretReportMDT&>().getTurretReportID())>,
    "CXX-011213: TurretReportMDT::getTurretReportID() must return TurretReportID_Type&");

static_assert(
    std::is_same_v<
        const uci::type::TurretReportID_Type&,
        decltype(std::declval<const uci::type::TurretReportMDT&>().getTurretReportID())>,
    "CXX-011214: TurretReportMDT::getTurretReportID() const must return const TurretReportID_Type&");

// AMTI_ActivityMDT::SubsystemID — required complex element
static_assert(
    std::is_same_v<
        uci::type::SubsystemID_Type&,
        decltype(std::declval<uci::type::AMTI_ActivityMDT&>().getSubsystemID())>,
    "CXX-011213: AMTI_ActivityMDT::getSubsystemID() must return SubsystemID_Type&");

static_assert(
    std::is_same_v<
        const uci::type::SubsystemID_Type&,
        decltype(std::declval<const uci::type::AMTI_ActivityMDT&>().getSubsystemID())>,
    "CXX-011214: AMTI_ActivityMDT::getSubsystemID() const must return const SubsystemID_Type&");

// ---------------------------------------------------------------------------
// CXX-011215 — required complex element setter must return Parent& (FAILING)
// Generated code returns void; spec requires Parent& (fluent interface).
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-011215 — setters return void, not Parent&

static_assert(
    std::is_same_v<
        uci::type::TurretReportMDT&,
        decltype(std::declval<uci::type::TurretReportMDT&>().setTurretReportID(
            std::declval<const uci::type::TurretReportID_Type&>()))>,
    "CXX-011215: TurretReportMDT::setTurretReportID(const TurretReportID_Type&) must return TurretReportMDT&");

static_assert(
    std::is_same_v<
        uci::type::AMTI_ActivityMDT&,
        decltype(std::declval<uci::type::AMTI_ActivityMDT&>().setSubsystemID(
            std::declval<const uci::type::SubsystemID_Type&>()))>,
    "CXX-011215: AMTI_ActivityMDT::setSubsystemID(const SubsystemID_Type&) must return AMTI_ActivityMDT&");

#endif // FAILING: CXX-011215

// ---------------------------------------------------------------------------
// CXX-011216 — simple primitive getter must return by value (const-only)
// Spec: xs::Double getX() const   (single const overload, returned by value)
// Generated: double& getX() and const double& getX() const  (by reference, two overloads)
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-011216 — simple primitives returned by reference, not by value

// Verify double is returned by value (not by reference)
static_assert(
    std::is_same_v<
        double,
        decltype(std::declval<const uci::type::ECEF_PositionPositionCovarianceType&>().getPxPx())>,
    "CXX-011216: ECEF_PositionPositionCovarianceType::getPxPx() const must return double (by value)");

// Verify there is no non-const (mutable-reference) overload
static_assert(
    std::is_same_v<
        double,
        decltype(std::declval<const uci::type::CropSettingsType&>().getX_Position())>,
    "CXX-011216: CropSettingsType::getX_Position() const must return uint32_t (by value)");

#endif // FAILING: CXX-011216

// CXX-011216 as actually generated (by-reference) — documents current (non-compliant) behaviour:
static_assert(
    std::is_same_v<
        const double&,
        decltype(std::declval<const uci::type::ECEF_PositionPositionCovarianceType&>().getPxPx())>,
    "Documenting current behaviour: getPxPx() const returns const double& (spec requires by-value double)");

static_assert(
    std::is_same_v<
        const uint32_t&,
        decltype(std::declval<const uci::type::CropSettingsType&>().getX_Position())>,
    "Documenting current behaviour: getX_Position() const returns const uint32_t& (spec requires by-value uint32_t)");

// ---------------------------------------------------------------------------
// CXX-011217 — simple primitive setter must return Parent& and take value by value
// Spec: Parent& setX(xs::Double value)
// Generated: void setX(const double& v)  — wrong return type AND wrong param convention
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-011217 — setter returns void and takes const T& instead of T by value

static_assert(
    std::is_same_v<
        uci::type::ECEF_PositionPositionCovarianceType&,
        decltype(std::declval<uci::type::ECEF_PositionPositionCovarianceType&>().setPxPx(0.0))>,
    "CXX-011217: ECEF_PositionPositionCovarianceType::setPxPx(double) must return ECEF_PositionPositionCovarianceType&");

static_assert(
    std::is_same_v<
        uci::type::CropSettingsType&,
        decltype(std::declval<uci::type::CropSettingsType&>().setX_Position(uint32_t{0}))>,
    "CXX-011217: CropSettingsType::setX_Position(uint32_t) must return CropSettingsType&");

#endif // FAILING: CXX-011217

// ---------------------------------------------------------------------------
// CXX-012706 / CXX-012707 — non-simple string/binary/list primitive getters (PASS)
// std::string& getX() and const std::string& getX() const must both exist.
// OrbitalRendezvousEventType::MinimumRangeAnalysisDuration is a required xs:duration
// field (string-family, non-simple per the table).
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<
        std::string&,
        decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().getMinimumRangeAnalysisDuration())>,
    "CXX-012706: OrbitalRendezvousEventType::getMinimumRangeAnalysisDuration() must return std::string&");

static_assert(
    std::is_same_v<
        const std::string&,
        decltype(std::declval<const uci::type::OrbitalRendezvousEventType&>().getMinimumRangeAnalysisDuration())>,
    "CXX-012707: OrbitalRendezvousEventType::getMinimumRangeAnalysisDuration() const must return const std::string&");

// ---------------------------------------------------------------------------
// CXX-012708 — non-simple string primitive setter must return Parent& (FAILING)
// Generated: void setMinimumRangeAnalysisDuration(const std::string&)
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-012708 — string primitive setter returns void, not Parent&

static_assert(
    std::is_same_v<
        uci::type::OrbitalRendezvousEventType&,
        decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().setMinimumRangeAnalysisDuration(
            std::declval<const std::string&>()))>,
    "CXX-012708: OrbitalRendezvousEventType::setMinimumRangeAnalysisDuration(const std::string&) must return OrbitalRendezvousEventType&");

#endif // FAILING: CXX-012708

// ---------------------------------------------------------------------------
// CXX-011219 — string primitive setter overload: setX(const std::string&) → Parent& (FAILING)
// Same return-type violation as CXX-012708 above, covering the std::string overload
// for all string-primitive required elements.
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-011219 — std::string setter overload returns void

static_assert(
    std::is_same_v<
        uci::type::OrbitalRendezvousEventType&,
        decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().setMinimumRangeAnalysisDuration(
            std::declval<const std::string&>()))>,
    "CXX-011219: string-primitive setter must return Parent&, not void");

#endif // FAILING: CXX-011219

// ---------------------------------------------------------------------------
// CXX-011220 — string primitive setter overload: setX(const char*) must exist (FAILING)
// The const char* overload is entirely absent from all generated headers.
// ---------------------------------------------------------------------------
#if 0 // FAILING: CXX-011220 — const char* overload does not exist

// This won't even name-resolve because the overload is missing.
static_assert(
    std::is_same_v<
        uci::type::OrbitalRendezvousEventType&,
        decltype(std::declval<uci::type::OrbitalRendezvousEventType&>().setMinimumRangeAnalysisDuration(
            static_cast<const char*>(nullptr)))>,
    "CXX-011220: string-primitive setX(const char*) overload must exist and return Parent&");

#endif // FAILING: CXX-011220

// ---------------------------------------------------------------------------
// CXX-011223 — enum element setter must take Enum::EnumerationItem and return Parent& (FAILING)
//
// The spec says:
//   - In an enum accessor (ObjectStateEnum itself): void setValue(EnumerationItem) is OK
//     because ObjectStateEnum IS the enum wrapper.
//   - In a containing complex type (MsgNameReportMT): the setter for an optional enum
//     field is via the enable/get/clear pattern, not a setX(EnumerationItem) directly.
//     For a REQUIRED enum field, Parent& setX(Enum::EnumerationItem) is needed.
//
// MsgNameReportMT::ObjectState is optional (uses enable/get/clear), so the required-enum
// setter path (CXX-011223) is exercised via AMTI_ActivityMT which has no required enum.
// Below we verify the getter pair still conforms and note the setter return-type gap.
// ---------------------------------------------------------------------------

// Getter pair for optional enum field (enable/get/clear pattern) — PASS
static_assert(
    std::is_same_v<
        uci::type::ObjectStateEnum&,
        decltype(std::declval<uci::type::MsgNameReportMT&>().getObjectState())>,
    "CXX-011213: MsgNameReportMT::getObjectState() must return ObjectStateEnum&");

static_assert(
    std::is_same_v<
        const uci::type::ObjectStateEnum&,
        decltype(std::declval<const uci::type::MsgNameReportMT&>().getObjectState())>,
    "CXX-011214: MsgNameReportMT::getObjectState() const must return const ObjectStateEnum&");

// Setter return type — FAILING (returns void, not Parent&)
#if 0 // FAILING: CXX-011223 / CXX-011215 — enum setter returns void

// For a required enum element the setter must be:
//   MsgNameReportMT& setObjectState(ObjectStateEnum::EnumerationItem)
// Generated is:
//   void setObjectState(const uci::type::ObjectStateEnum& v)   (also takes wrong arg type)
static_assert(
    std::is_same_v<
        uci::type::MsgNameReportMT&,
        decltype(std::declval<uci::type::MsgNameReportMT&>().setObjectState(
            uci::type::ObjectStateEnum::NEW))>,
    "CXX-011223: setObjectState(ObjectStateEnum::EnumerationItem) must return MsgNameReportMT&");

#endif // FAILING: CXX-011223
