// Compile-only conformance: xs:simpleType xs:restriction (non-enum) API shape
// Spec: OMSC-SPC-008 RevK §"The SimpleRestriction Accessor" (lines 10946-11035)
//
// CERTs under test
// ─────────────────────────────────────────────────────────────────────────────
// CXX-006143 — simpleType restricting a Simple Primitive (xs:double, xs:float,
//              xs:int, xs:boolean, …) MUST be a typedef to
//              uci::base::<PrimitiveName>Accessor, NOT a class.
//
// CXX-006144 — A companion typedef <TypeName>Value MUST also be generated,
//              equivalent to xs::<PrimitiveName> (the raw C++ primitive).
//
// CXX-006553 — simpleType restricting a String/Binary/List Primitive MUST be a
//              typedef to xs::<PrimitiveName> (currently xs::String), NOT a
//              class.
//
// Current status: ALL THREE ARE VIOLATED.
//
// The schema compiler emits a full abstract class for every simpleType
// restriction — regardless of whether the base is a numeric primitive (double,
// float, …) or a string primitive.  No typedefs are generated, no
// <TypeName>Value alias exists, and the string variants are mis-tagged
// ACCESSOR_TYPE_SIMPLE_PRIMITIVE instead of a string type.
//
// Total affected headers (as of 2026-04-25):
//   • 38 numeric simple-primitive restriction classes (CXX-006143, CXX-006144)
//   • 206 string-primitive restriction classes (CXX-006553)
//     (all 244 ACCESSOR_TYPE_SIMPLE_PRIMITIVE files; 206 hold std::string values)
//
// ─────────────────────────────────────────────────────────────────────────────
// HOW THIS FILE IS STRUCTURED
// ─────────────────────────────────────────────────────────────────────────────
// Part A  — #if 0 blocks: the SPEC-REQUIRED typedef shapes.
//           Guarded so they do not block the build today.
//           Flip each block to #if 1 once the schema compiler is fixed.
//
// Part B  — Active static_asserts: document the CURRENT (non-compliant) shape
//           so that regressions in the existing class structure are caught and
//           the full non-compliance is visible in the build record.
// ─────────────────────────────────────────────────────────────────────────────

#include "uci/base/Accessor.h"
#include "uci/base/StringAccessor.h"
#include "uci/type/UnitBallDoubleType.h"
#include "uci/type/UnitIntervalDoubleType.h"
#include "uci/type/UnitBallFloatType.h"
#include "uci/type/UnitIntervalFloatType.h"
#include "uci/type/VisibleString256Type.h"
#include "uci/type/AlphanumericDashSpaceUnderscoreStringLength20Type.h"

#include <type_traits>

// ═════════════════════════════════════════════════════════════════════════════
// PART A — SPEC-REQUIRED SHAPES (currently non-compilable; enable after fix)
// ═════════════════════════════════════════════════════════════════════════════

// ─── CXX-006143 / CXX-006144: numeric simple-primitive restrictions ───────────
// The schema compiler MUST generate (example from the spec §10966-10978):
//
//   namespace uci { namespace type {
//     typedef uci::base::DoubleAccessor UnitBallDoubleType;     // CXX-006143
//     typedef xs::Double                UnitBallDoubleTypeValue; // CXX-006144
//   }}
//
// Because uci::base::DoubleAccessor and xs::Double do not exist yet, and
// because UnitBallDoubleType is currently a class (not an alias), these
// static_asserts cannot compile today.
#if 0  // TODO(CXX-006143, CXX-006144): enable once schema compiler is fixed

// CXX-006143 — typedef, not a class
static_assert(!std::is_class_v<uci::type::UnitBallDoubleType>,
    "CERT CXX-006143: UnitBallDoubleType must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::UnitBallDoubleType, uci::base::DoubleAccessor>,
    "CERT CXX-006143: UnitBallDoubleType must be typedef to uci::base::DoubleAccessor");

static_assert(!std::is_class_v<uci::type::UnitIntervalDoubleType>,
    "CERT CXX-006143: UnitIntervalDoubleType must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::UnitIntervalDoubleType, uci::base::DoubleAccessor>,
    "CERT CXX-006143: UnitIntervalDoubleType must be typedef to uci::base::DoubleAccessor");

static_assert(!std::is_class_v<uci::type::UnitBallFloatType>,
    "CERT CXX-006143: UnitBallFloatType must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::UnitBallFloatType, uci::base::FloatAccessor>,
    "CERT CXX-006143: UnitBallFloatType must be typedef to uci::base::FloatAccessor");

static_assert(!std::is_class_v<uci::type::UnitIntervalFloatType>,
    "CERT CXX-006143: UnitIntervalFloatType must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::UnitIntervalFloatType, uci::base::FloatAccessor>,
    "CERT CXX-006143: UnitIntervalFloatType must be typedef to uci::base::FloatAccessor");

// CXX-006144 — companion Value typedefs (xs:: primitives)
static_assert(std::is_same_v<uci::type::UnitBallDoubleTypeValue, xs::Double>,
    "CERT CXX-006144: UnitBallDoubleTypeValue must be typedef to xs::Double");
static_assert(std::is_same_v<uci::type::UnitIntervalDoubleTypeValue, xs::Double>,
    "CERT CXX-006144: UnitIntervalDoubleTypeValue must be typedef to xs::Double");
static_assert(std::is_same_v<uci::type::UnitBallFloatTypeValue, xs::Float>,
    "CERT CXX-006144: UnitBallFloatTypeValue must be typedef to xs::Float");
static_assert(std::is_same_v<uci::type::UnitIntervalFloatTypeValue, xs::Float>,
    "CERT CXX-006144: UnitIntervalFloatTypeValue must be typedef to xs::Float");

#endif // CXX-006143, CXX-006144


// ─── CXX-006553: string-primitive restrictions ────────────────────────────────
// The schema compiler MUST generate (spec §11029):
//
//   namespace uci { namespace type {
//     typedef xs::String VisibleString256Type;
//   }}
//
// xs::String does not exist in the current headers (the implementation uses
// std::string directly), and VisibleString256Type is a class today.
#if 0  // TODO(CXX-006553): enable once schema compiler is fixed

static_assert(!std::is_class_v<uci::type::VisibleString256Type>,
    "CERT CXX-006553: VisibleString256Type must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::VisibleString256Type, xs::String>,
    "CERT CXX-006553: VisibleString256Type must be typedef to xs::String");

static_assert(!std::is_class_v<uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type>,
    "CERT CXX-006553: AlphanumericDashSpaceUnderscoreStringLength20Type must be a typedef alias, not a class");
static_assert(std::is_same_v<uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type, xs::String>,
    "CERT CXX-006553: AlphanumericDashSpaceUnderscoreStringLength20Type must be typedef to xs::String");

#endif // CXX-006553


// ═════════════════════════════════════════════════════════════════════════════
// PART B — CURRENT (NON-COMPLIANT) SHAPE — active static_asserts
//
// These document the class structure that was generated incorrectly.
// They compile today and guard against regression in the existing wrong shape.
// Comments note the specific CERT each assertion violates.
// ═════════════════════════════════════════════════════════════════════════════

// ── Numeric simple-primitive restrictions: generated as abstract classes ──────
//    VIOLATES CXX-006143 (should be typedef, not class)
//    VIOLATES CXX-006144 (no companion Value typedef exists)

// UnitBallDoubleType (xs:restriction base="xs:double")
static_assert(std::is_class_v<uci::type::UnitBallDoubleType>,
    "NON-COMPLIANT(CXX-006143): UnitBallDoubleType is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::UnitBallDoubleType>,
    "NON-COMPLIANT(CXX-006143): UnitBallDoubleType is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::UnitBallDoubleType>,
    "Current shape: UnitBallDoubleType extends uci::base::Accessor");

// UnitIntervalDoubleType (xs:restriction base="xs:double")
static_assert(std::is_class_v<uci::type::UnitIntervalDoubleType>,
    "NON-COMPLIANT(CXX-006143): UnitIntervalDoubleType is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::UnitIntervalDoubleType>,
    "NON-COMPLIANT(CXX-006143): UnitIntervalDoubleType is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::UnitIntervalDoubleType>,
    "Current shape: UnitIntervalDoubleType extends uci::base::Accessor");

// UnitBallFloatType (xs:restriction base="xs:float")
static_assert(std::is_class_v<uci::type::UnitBallFloatType>,
    "NON-COMPLIANT(CXX-006143): UnitBallFloatType is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::UnitBallFloatType>,
    "NON-COMPLIANT(CXX-006143): UnitBallFloatType is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::UnitBallFloatType>,
    "Current shape: UnitBallFloatType extends uci::base::Accessor");

// UnitIntervalFloatType (xs:restriction base="xs:float")
static_assert(std::is_class_v<uci::type::UnitIntervalFloatType>,
    "NON-COMPLIANT(CXX-006143): UnitIntervalFloatType is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::UnitIntervalFloatType>,
    "NON-COMPLIANT(CXX-006143): UnitIntervalFloatType is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::UnitIntervalFloatType>,
    "Current shape: UnitIntervalFloatType extends uci::base::Accessor");

// ── String-primitive restrictions: generated as abstract classes ──────────────
//    VIOLATES CXX-006553 (should be typedef to xs::String, not a class)
//    Note: also mis-tagged ACCESSOR_TYPE_SIMPLE_PRIMITIVE instead of a string
//    category, which is a secondary defect in the same generated code.

// VisibleString256Type (xs:restriction base="xs:string")
static_assert(std::is_class_v<uci::type::VisibleString256Type>,
    "NON-COMPLIANT(CXX-006553): VisibleString256Type is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::VisibleString256Type>,
    "NON-COMPLIANT(CXX-006553): VisibleString256Type is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::VisibleString256Type>,
    "Current shape: VisibleString256Type extends uci::base::Accessor");

// AlphanumericDashSpaceUnderscoreStringLength20Type (xs:restriction base="xs:string" or similar)
static_assert(std::is_class_v<uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type>,
    "NON-COMPLIANT(CXX-006553): AlphanumericDashSpaceUnderscoreStringLength20Type is a class, not a typedef");
static_assert(std::is_abstract_v<uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type>,
    "NON-COMPLIANT(CXX-006553): AlphanumericDashSpaceUnderscoreStringLength20Type is abstract (should be a typedef alias)");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type>,
    "Current shape: AlphanumericDashSpaceUnderscoreStringLength20Type extends uci::base::Accessor");
