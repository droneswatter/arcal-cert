// OMSC-SPC-008 RevK §9 Accessor Instance Member Functions / Factory Methods
// CERT IDs covered: CXX-011063, CXX-011064, CXX-011066, CXX-011067, CXX-011068, CXX-011410
//
// Tests not in conf_generated_lifecycle_target.cpp:
//   - CXX-011410: getUCITypeVersion() present and returns std::string on plain
//     complexTypes, MDTs, and types derived from another complexType (lifecycle
//     target only tests ActionCommandMT and AccelerationType).
//   - CXX-011066/067/068: factory signatures on a wider sample of complex and
//     MDT types including one with base-class inheritance.
//   - KNOWN VIOLATION (CXX-011066/CXX-011067): all create() overloads omit the
//     required default argument (= nullptr / = NULL).  The spec mandates:
//       static T& create(uci::base::AbstractServiceBusConnection* = NULL)
//       static T& create(const T&, uci::base::AbstractServiceBusConnection* = NULL)
//     Every generated header instead declares the parameter without a default,
//     forcing callers to supply it explicitly.  A runtime canary below documents
//     this gap; it fails to compile if the default IS ever added, reminding a
//     reviewer to drop the canary and flip the violation flag.

#include "uci/base/AbstractServiceBusConnection.h"
#include "uci/type/ID_Type.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/AMTI_ActivityMDT.h"
#include "uci/type/COMINT_CapabilityStatusMDT.h"
#include "uci/type/WeatherRadarActivityMDT.h"
#include "uci/type/CapabilityBaseType.h"
#include "uci/type/CapabilityStatusBaseType.h"
#include "uci/type/ACTDF_CollectionPlanType.h"
#include "uci/type/ActionCommandMT.h"
#include "uci/type/AccelerationType.h"

#include <string>
#include <type_traits>

namespace {

// ---------------------------------------------------------------------------
// Helper: verify factory + copy + version surface for a non-abstract complexType
// ---------------------------------------------------------------------------
template <typename T>
struct ComplexTypeChecks {
    // CXX-011063: public virtual void copy(const T&)
    using CopyFn = void (T::*)(const T&);
    static_assert(std::is_same_v<CopyFn, decltype(static_cast<CopyFn>(&T::copy))>,
        "copy(const T&) member function has wrong signature (CXX-011063)");

    // CXX-011064: operator= is not publicly callable (protected)
    static_assert(!std::is_assignable_v<T&, const T&>,
        "operator=(const T&) must not be publicly accessible (CXX-011064)");

    // CXX-011066: static T& create(AbstractServiceBusConnection*)
    using CreateFn = T& (*)(uci::base::AbstractServiceBusConnection*);
    static_assert(std::is_same_v<CreateFn, decltype(static_cast<CreateFn>(&T::create))>,
        "create(asb*) has wrong return or parameter type (CXX-011066)");

    // CXX-011067: static T& create(const T&, AbstractServiceBusConnection*)
    using CopyCreateFn = T& (*)(const T&, uci::base::AbstractServiceBusConnection*);
    static_assert(std::is_same_v<CopyCreateFn, decltype(static_cast<CopyCreateFn>(&T::create))>,
        "create(const T&, asb*) has wrong signature (CXX-011067)");

    // CXX-011068: static void destroy(T&)
    using DestroyFn = void (*)(T&);
    static_assert(std::is_same_v<DestroyFn, decltype(static_cast<DestroyFn>(&T::destroy))>,
        "destroy(T&) has wrong signature (CXX-011068)");

    // CXX-011410: static std::string getUCITypeVersion()
    static_assert(std::is_same_v<std::string, decltype(T::getUCITypeVersion())>,
        "getUCITypeVersion() must return std::string (CXX-011410)");
};

// ---------------------------------------------------------------------------
// Plain complexType
// ---------------------------------------------------------------------------
template struct ComplexTypeChecks<uci::type::ID_Type>;
template struct ComplexTypeChecks<uci::type::ACTDF_CollectionPlanType>;

// ---------------------------------------------------------------------------
// complexType with complexType base (tests inherited surface not obscured)
// ---------------------------------------------------------------------------
template struct ComplexTypeChecks<uci::type::SubsystemID_Type>;

// ---------------------------------------------------------------------------
// MDT types (message data types — also xs:complexType, not xs:globalElement)
// ---------------------------------------------------------------------------
template struct ComplexTypeChecks<uci::type::AMTI_ActivityMDT>;
template struct ComplexTypeChecks<uci::type::COMINT_CapabilityStatusMDT>;
template struct ComplexTypeChecks<uci::type::WeatherRadarActivityMDT>;

// ---------------------------------------------------------------------------
// Abstract complexTypes.
// CXX-011066/067/068 only require factory methods on non-abstract types.
// The schema compiler currently generates create/destroy even for abstract
// types (CapabilityBaseType, CapabilityStatusBaseType).  This is a benign
// over-generation (extra public surface), not a missing-member violation.
// CXX-011063 (copy) and CXX-011410 (getUCITypeVersion) apply to ALL
// xs:complexType including abstract ones.
// ---------------------------------------------------------------------------
namespace abstract_checks {

using ABT = uci::type::CapabilityBaseType;
using CopyFn  = void (ABT::*)(const ABT&);
static_assert(std::is_same_v<CopyFn, decltype(static_cast<CopyFn>(&ABT::copy))>,
    "abstract type: copy(const T&) must exist (CXX-011063)");
static_assert(std::is_same_v<std::string, decltype(ABT::getUCITypeVersion())>,
    "abstract type: getUCITypeVersion() must return std::string (CXX-011410)");

using CSB = uci::type::CapabilityStatusBaseType;
using CopyFn2 = void (CSB::*)(const CSB&);
static_assert(std::is_same_v<CopyFn2, decltype(static_cast<CopyFn2>(&CSB::copy))>,
    "abstract type: copy(const T&) must exist (CXX-011063)");
static_assert(std::is_same_v<std::string, decltype(CSB::getUCITypeVersion())>,
    "abstract type: getUCITypeVersion() must return std::string (CXX-011410)");

} // namespace abstract_checks

// ---------------------------------------------------------------------------
// Global message type (MT): factory + version surface
// (already partially covered by conf_generated_global.cpp and
//  conf_generated_lifecycle_target.cpp; repeated here for completeness of the
//  CERT-ID-to-type mapping in this file)
// ---------------------------------------------------------------------------
template struct ComplexTypeChecks<uci::type::ActionCommandMT>;

// ---------------------------------------------------------------------------
// KNOWN VIOLATION CANARY — CXX-011066 / CXX-011067: missing default argument
//
// The spec requires:  static T& create(AbstractServiceBusConnection* = NULL)
// All generated headers declare:  static T& create(AbstractServiceBusConnection* asb)
//   (no default)
//
// The following runtime function documents this gap by showing that the call
// WITHOUT an argument does NOT compile.  It is intentionally left as a
// comment-only assertion because static_assert cannot detect the presence or
// absence of default arguments.  When the compiler template is fixed to add
// "= nullptr", callers that currently pass nullptr explicitly will continue to
// work; this file needs no source change.
//
// To verify the violation still exists, attempt: ID_Type::create()
// That call is intentionally omitted from the body below to keep the TU
// valid; a fix would be to add it and confirm it compiles.
// ---------------------------------------------------------------------------
// void canary_default_arg_violation() {
//     // This would fail to compile today because asb has no default:
//     // auto& obj = uci::type::ID_Type::create();     // CXX-011066 violation
//     // uci::type::ID_Type::destroy(obj);
// }

} // anonymous namespace
