// Compile-only conformance: uci::base::<T>Accessor SimplePrimitive accessor classes.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, Section "The SimplePrimitive Accessor Class"
//       (lines 10748–10945 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md)
//       Primitive type table: Table 9.1-1 (lines 2429–2537)
//
// CERTs covered:
//   CXX-005765 — <T>Accessor exists in uci::base, publicly inherits uci::base::Accessor
//   CXX-005775 — xs::<T> get<T>Value() const
//   CXX-011087 — uci::base::<T>Accessor& set<T>Value(xs::<T>)
//   CXX-011088 — uci::base::<T>Accessor& operator=(const <T>Accessor&)
//   CXX-013023 — uci::base::<T>Accessor& operator=(xs::<T>)
//   CXX-011089 — operator xs::<T>() const conversion operator
//
// Primitive types from Table 9.1-1:
//   Boolean (bool), Long (int64_t), Int (int32_t), Short (int16_t),
//   Byte (int8_t), UnsignedInt (uint32_t), UnsignedShort (uint16_t),
//   UnsignedByte (uint8_t), Double (double), Float (float),
//   Duration, Time, DateTime
//
// Successful compilation IS the test for the properties that hold.

#include "uci/base/PrimitiveAccessors.h"
#include "xs/accessorType.h"

#include <cstdint>
#include <type_traits>

// ---------------------------------------------------------------------------
// Helper: verify that a type alias resolves in uci::base and that it publicly
// inherits uci::base::Accessor (CXX-005765).
// ---------------------------------------------------------------------------

// CXX-005765: primitive accessors exist in uci::base and publicly inherit
// uci::base::Accessor.

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::BooleanAccessor>,
    "CXX-005765: BooleanAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::ByteAccessor>,
    "CXX-005765: ByteAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::ShortAccessor>,
    "CXX-005765: ShortAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::IntAccessor>,
    "CXX-005765: IntAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::LongAccessor>,
    "CXX-005765: LongAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::FloatAccessor>,
    "CXX-005765: FloatAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::DoubleAccessor>,
    "CXX-005765: DoubleAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::UnsignedByteAccessor>,
    "CXX-005765: UnsignedByteAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::UnsignedShortAccessor>,
    "CXX-005765: UnsignedShortAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::UnsignedIntAccessor>,
    "CXX-005765: UnsignedIntAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::UnsignedLongAccessor>,
    "CXX-005765: UnsignedLongAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::DurationAccessor>,
    "CXX-005765: DurationAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::TimeAccessor>,
    "CXX-005765: TimeAccessor must publicly inherit uci::base::Accessor");

static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::DateTimeAccessor>,
    "CXX-005765: DateTimeAccessor must publicly inherit uci::base::Accessor");

// ---------------------------------------------------------------------------
// CXX-011088: operator=(const <T>Accessor&) returns <T>Accessor& — public.
//
// Copy-assignment is public and returns the concrete accessor type.
// ---------------------------------------------------------------------------

static_assert(std::is_copy_assignable_v<uci::base::BooleanAccessor>,
    "CXX-011088: BooleanAccessor& operator=(const BooleanAccessor&) must be public");

static_assert(std::is_copy_assignable_v<uci::base::DoubleAccessor>,
    "CXX-011088: DoubleAccessor& operator=(const DoubleAccessor&) must be public");

static_assert(std::is_copy_assignable_v<uci::base::UnsignedIntAccessor>,
    "CXX-011088: UnsignedIntAccessor& operator=(const UnsignedIntAccessor&) must be public");

static_assert(std::is_copy_assignable_v<uci::base::LongAccessor>,
    "CXX-011088: LongAccessor& operator=(const LongAccessor&) must be public");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::DoubleAccessor&>() = std::declval<const uci::base::DoubleAccessor&>()),
        uci::base::DoubleAccessor&>,
    "CXX-011088: DoubleAccessor::operator=(const DoubleAccessor&) must return DoubleAccessor&");

// ---------------------------------------------------------------------------
// CXX-013023: operator=(xs::<T>) returns <T>Accessor& — public.
// Verify return type for representative types.
// ---------------------------------------------------------------------------

// operator=(xs::Boolean) → BooleanAccessor&
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::BooleanAccessor&>() = std::declval<xs::Boolean>()),
        uci::base::BooleanAccessor&>,
    "CXX-013023: BooleanAccessor::operator=(xs::Boolean) must return BooleanAccessor&");

// operator=(xs::Double) → DoubleAccessor&
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::DoubleAccessor&>() = std::declval<xs::Double>()),
        uci::base::DoubleAccessor&>,
    "CXX-013023: DoubleAccessor::operator=(xs::Double) must return DoubleAccessor&");

// operator=(xs::UnsignedInt) → UnsignedIntAccessor&
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::UnsignedIntAccessor&>() = std::declval<xs::UnsignedInt>()),
        uci::base::UnsignedIntAccessor&>,
    "CXX-013023: UnsignedIntAccessor::operator=(xs::UnsignedInt) must return UnsignedIntAccessor&");

// operator=(xs::Long) → LongAccessor&
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::LongAccessor&>() = std::declval<xs::Long>()),
        uci::base::LongAccessor&>,
    "CXX-013023: LongAccessor::operator=(xs::Long) must return LongAccessor&");

// ---------------------------------------------------------------------------
// CXX-011089: operator xs::<T>() const — conversion operator is public.
//
// Verify the operator is public via explicit calls and implicit conversion.
// ---------------------------------------------------------------------------

// Implicit conversion is accessible (operator const ValueType& is public):
static_assert(std::is_convertible_v<uci::base::BooleanAccessor, xs::Boolean>,
    "CXX-011089: BooleanAccessor must be implicitly convertible to xs::Boolean");

static_assert(std::is_convertible_v<uci::base::DoubleAccessor, xs::Double>,
    "CXX-011089: DoubleAccessor must be implicitly convertible to xs::Double");

static_assert(std::is_convertible_v<uci::base::IntAccessor, xs::Int>,
    "CXX-011089: IntAccessor must be implicitly convertible to xs::Int");

static_assert(std::is_convertible_v<uci::base::UnsignedIntAccessor, xs::UnsignedInt>,
    "CXX-011089: UnsignedIntAccessor must be implicitly convertible to xs::UnsignedInt");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::BooleanAccessor&>().operator xs::Boolean()), xs::Boolean>,
    "CXX-011089: BooleanAccessor::operator xs::Boolean() must return xs::Boolean");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DoubleAccessor&>().operator xs::Double()), xs::Double>,
    "CXX-011089: DoubleAccessor::operator xs::Double() must return xs::Double");

// ---------------------------------------------------------------------------
// CXX-005775 / CXX-011087: type-specific get/set value methods.
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::BooleanAccessor&>().getBooleanValue()), xs::Boolean>,
    "CXX-005775: BooleanAccessor::getBooleanValue() must return xs::Boolean");
static_assert(
    std::is_same_v<decltype(std::declval<uci::base::BooleanAccessor&>().setBooleanValue(std::declval<xs::Boolean>())),
                   uci::base::BooleanAccessor&>,
    "CXX-011087: BooleanAccessor::setBooleanValue(xs::Boolean) must return BooleanAccessor&");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DoubleAccessor&>().getDoubleValue()), xs::Double>,
    "CXX-005775: DoubleAccessor::getDoubleValue() must return xs::Double");
static_assert(
    std::is_same_v<decltype(std::declval<uci::base::DoubleAccessor&>().setDoubleValue(std::declval<xs::Double>())),
                   uci::base::DoubleAccessor&>,
    "CXX-011087: DoubleAccessor::setDoubleValue(xs::Double) must return DoubleAccessor&");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DurationAccessor&>().getDurationValue()), xs::Duration>,
    "CXX-005775: DurationAccessor::getDurationValue() must return xs::Duration");
static_assert(
    std::is_same_v<decltype(std::declval<uci::base::DurationAccessor&>().setDurationValue(std::declval<xs::Duration>())),
                   uci::base::DurationAccessor&>,
    "CXX-011087: DurationAccessor::setDurationValue(xs::Duration) must return DurationAccessor&");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::TimeAccessor&>().getTimeValue()), xs::Time>,
    "CXX-005775: TimeAccessor::getTimeValue() must return xs::Time");
static_assert(
    std::is_same_v<decltype(std::declval<uci::base::TimeAccessor&>().setTimeValue(std::declval<xs::Time>())),
                   uci::base::TimeAccessor&>,
    "CXX-011087: TimeAccessor::setTimeValue(xs::Time) must return TimeAccessor&");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DateTimeAccessor&>().getDateTimeValue()), xs::DateTime>,
    "CXX-005775: DateTimeAccessor::getDateTimeValue() must return xs::DateTime");
static_assert(
    std::is_same_v<decltype(std::declval<uci::base::DateTimeAccessor&>().setDateTimeValue(std::declval<xs::DateTime>())),
                   uci::base::DateTimeAccessor&>,
    "CXX-011087: DateTimeAccessor::setDateTimeValue(xs::DateTime) must return DateTimeAccessor&");
