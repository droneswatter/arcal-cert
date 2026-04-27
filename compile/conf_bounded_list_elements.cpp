// Compile-only conformance: BoundedList element member patterns in generated type headers.
// Covers CERT CXX-007053 (inner typedef), CXX-011226 (const getter), CXX-011227 (non-const getter),
// CXX-011228 (setter), CXX-012712 (string/binary typedef), CXX-012713 (simple-primitive typedef).
//
// OMSC-SPC-008 RevK §12.x (LocalElement Accessor) requirements under test:
//
//   CXX-007053: Each complex-type BoundedList element must be exposed via an inner typedef:
//     typedef uci::base::BoundedList<uci::type::ElemType,
//         uci::type::accessorType::elemType> ElemName;
//
//   CXX-012712: String/binary BoundedList element: inner typedef using xs::accessorType.
//
//   CXX-012713: Simple-primitive BoundedList element: inner typedef using
//     uci::base::BoundedList<uci::base::<Prim>Accessor, uci::base::accessorType::<prim>Accessor>.
//
//   CXX-011226: const getter  -> virtual const ElemName& getElemName() const = 0
//   CXX-011227: non-const getter -> virtual ElemName& getElemName() = 0
//   CXX-011228: setter         -> virtual ParentType& setElemName(const ElemName&) = 0
//
// Current status (2026-04-25): ALL three structural requirements (typedef, correct accessorType
// constant, setter) are VIOLATED in every generated header.  The static_asserts below are written
// to the SPEC-REQUIRED form so they will fail to compile until the schema compiler is fixed,
// providing a permanent regression gate.
//
// Resolved in ARCAL conformance plan:
//   - TASK-005 bounded-list typedef/setter generation (implemented)

#include "uci/base/Accessor.h"
#include "uci/base/BoundedList.h"
#include "uci/base/accessorType.h"

// --- Representative generated headers that contain BoundedList fields ---
#include "uci/type/OrbitChangeCapabilityType.h"     // BoundedList of enum type
#include "uci/type/AMTI_ActivityCommandType.h"      // BoundedList of complex type
#include "uci/type/CovarianceMatrixType.h"          // BoundedList<double> — simple primitive
#include "uci/type/CommLink16_ControlType.h"        // BoundedList of string-restriction type

#include <type_traits>

// ---------------------------------------------------------------------------
// CXX-007053 / CXX-011226 / CXX-011227 / CXX-011228
// Representative check: OrbitChangeCapabilityType::CapabilityType
// (BoundedList element whose element type is an enum)
//
// Spec requires an inner typedef inside OrbitChangeCapabilityType:
//   typedef uci::base::BoundedList<uci::type::OrbitChangeCapabilityEnum,
//       uci::type::accessorType::orbitChangeCapabilityEnum> CapabilityType;
//
// And the three member function signatures referencing that typedef:
//   virtual CapabilityType& getCapabilityType() = 0;                       (CXX-011227)
//   virtual const CapabilityType& getCapabilityType() const = 0;           (CXX-011226)
//   virtual OrbitChangeCapabilityType& setCapabilityType(const CapabilityType&) = 0; (CXX-011228)
// ---------------------------------------------------------------------------

// CXX-007053: inner typedef must exist
static_assert(
    std::is_same_v<
        uci::type::OrbitChangeCapabilityType::CapabilityType,
        uci::base::BoundedList<
            uci::type::OrbitChangeCapabilityEnum,
            uci::type::accessorType::orbitChangeCapabilityEnum>
    >,
    "CXX-007053: OrbitChangeCapabilityType::CapabilityType inner typedef missing or has wrong type/accessorType constant");

// CXX-011226: const getter return type
static_assert(
    std::is_same_v<
        decltype(std::declval<const uci::type::OrbitChangeCapabilityType&>().getCapabilityType()),
        const uci::type::OrbitChangeCapabilityType::CapabilityType&
    >,
    "CXX-011226: OrbitChangeCapabilityType::getCapabilityType() const must return const CapabilityType&");

// CXX-011227: non-const getter return type
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::type::OrbitChangeCapabilityType&>().getCapabilityType()),
        uci::type::OrbitChangeCapabilityType::CapabilityType&
    >,
    "CXX-011227: OrbitChangeCapabilityType::getCapabilityType() must return CapabilityType&");

// CXX-011228: setter signature — returns parent& and takes const CapabilityType&
using SetCapabilityTypeFn =
    uci::type::OrbitChangeCapabilityType& (uci::type::OrbitChangeCapabilityType::*)
        (const uci::type::OrbitChangeCapabilityType::CapabilityType&);
static_assert(
    std::is_same_v<SetCapabilityTypeFn,
        decltype(static_cast<SetCapabilityTypeFn>(
            &uci::type::OrbitChangeCapabilityType::setCapabilityType))>,
    "CXX-011228: OrbitChangeCapabilityType::setCapabilityType must take const CapabilityType& and return OrbitChangeCapabilityType&");

// ---------------------------------------------------------------------------
// CXX-007053 check for complex-type BoundedList element:
// AMTI_ActivityCommandType::TargetVolume
// Expected typedef:
//   typedef uci::base::BoundedList<uci::type::AirTargetVolumeCommandType,
//       uci::type::accessorType::airTargetVolumeCommandType> TargetVolume;
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<
        uci::type::AMTI_ActivityCommandType::TargetVolume,
        uci::base::BoundedList<
            uci::type::AirTargetVolumeCommandType,
            uci::type::accessorType::airTargetVolumeCommandType>
    >,
    "CXX-007053: AMTI_ActivityCommandType::TargetVolume inner typedef missing or wrong accessorType constant");

static_assert(
    std::is_same_v<
        decltype(std::declval<const uci::type::AMTI_ActivityCommandType&>().getTargetVolume()),
        const uci::type::AMTI_ActivityCommandType::TargetVolume&
    >,
    "CXX-011226: AMTI_ActivityCommandType::getTargetVolume() const must return const TargetVolume&");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::type::AMTI_ActivityCommandType&>().getTargetVolume()),
        uci::type::AMTI_ActivityCommandType::TargetVolume&
    >,
    "CXX-011227: AMTI_ActivityCommandType::getTargetVolume() must return TargetVolume&");

using SetTargetVolumeFn =
    uci::type::AMTI_ActivityCommandType& (uci::type::AMTI_ActivityCommandType::*)
        (const uci::type::AMTI_ActivityCommandType::TargetVolume&);
static_assert(
    std::is_same_v<SetTargetVolumeFn,
        decltype(static_cast<SetTargetVolumeFn>(
            &uci::type::AMTI_ActivityCommandType::setTargetVolume))>,
    "CXX-011228: AMTI_ActivityCommandType::setTargetVolume must take const TargetVolume& and return AMTI_ActivityCommandType&");

// ---------------------------------------------------------------------------
// CXX-012713: simple-primitive BoundedList element — CovarianceMatrixType::Covariance
// Spec requires:
//   typedef uci::base::BoundedList<uci::base::DoubleAccessor,
//       uci::base::accessorType::doubleAccessor> Covariance;
// (The C++ type for xs:double is uci::base::DoubleAccessor per the CAL spec primitives table.)
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<
        uci::type::CovarianceMatrixType::Covariance,
        uci::base::BoundedList<
            uci::base::DoubleAccessor,
            uci::base::accessorType::doubleAccessor>
    >,
    "CXX-012713: CovarianceMatrixType::Covariance inner typedef must use uci::base::DoubleAccessor / uci::base::accessorType::doubleAccessor");

static_assert(
    std::is_same_v<
        decltype(std::declval<const uci::type::CovarianceMatrixType&>().getCovariance()),
        const uci::type::CovarianceMatrixType::Covariance&
    >,
    "CXX-011226: CovarianceMatrixType::getCovariance() const must return const Covariance&");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::type::CovarianceMatrixType&>().getCovariance()),
        uci::type::CovarianceMatrixType::Covariance&
    >,
    "CXX-011227: CovarianceMatrixType::getCovariance() must return Covariance&");

using SetCovarianceFn =
    uci::type::CovarianceMatrixType& (uci::type::CovarianceMatrixType::*)
        (const uci::type::CovarianceMatrixType::Covariance&);
static_assert(
    std::is_same_v<SetCovarianceFn,
        decltype(static_cast<SetCovarianceFn>(
            &uci::type::CovarianceMatrixType::setCovariance))>,
    "CXX-011228: CovarianceMatrixType::setCovariance must take const Covariance& and return CovarianceMatrixType&");

// ---------------------------------------------------------------------------
// CXX-012712: string-restriction BoundedList element —
// CommLink16_ControlType::SecondarySourceTrackNumber
// Spec requires (element type is a string restriction, maps to xs::String accessor):
//   typedef uci::base::BoundedList<xs::String,
//       xs::accessorType::ACCESSOR_TYPE_STRING> SecondarySourceTrackNumber;
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<
        uci::type::CommLink16_ControlType::SecondarySourceTrackNumber,
        uci::base::BoundedList<
            xs::String,
            xs::accessorType::ACCESSOR_TYPE_STRING>
    >,
    "CXX-012712: CommLink16_ControlType::SecondarySourceTrackNumber inner typedef must use xs::String / xs::accessorType::ACCESSOR_TYPE_STRING");

static_assert(
    std::is_same_v<
        decltype(std::declval<const uci::type::CommLink16_ControlType&>().getSecondarySourceTrackNumber()),
        const uci::type::CommLink16_ControlType::SecondarySourceTrackNumber&
    >,
    "CXX-011226: CommLink16_ControlType::getSecondarySourceTrackNumber() const must return const SecondarySourceTrackNumber&");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::type::CommLink16_ControlType&>().getSecondarySourceTrackNumber()),
        uci::type::CommLink16_ControlType::SecondarySourceTrackNumber&
    >,
    "CXX-011227: CommLink16_ControlType::getSecondarySourceTrackNumber() must return SecondarySourceTrackNumber&");

using SetSecondarySourceTrackNumberFn =
    uci::type::CommLink16_ControlType& (uci::type::CommLink16_ControlType::*)
        (const uci::type::CommLink16_ControlType::SecondarySourceTrackNumber&);
static_assert(
    std::is_same_v<SetSecondarySourceTrackNumberFn,
        decltype(static_cast<SetSecondarySourceTrackNumberFn>(
            &uci::type::CommLink16_ControlType::setSecondarySourceTrackNumber))>,
    "CXX-011228: CommLink16_ControlType::setSecondarySourceTrackNumber must take const SecondarySourceTrackNumber& and return CommLink16_ControlType&");
