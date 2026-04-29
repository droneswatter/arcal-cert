// Compile-only conformance: uci::base::<T>Accessor SimplePrimitive accessor classes.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, Section "The SimplePrimitive Accessor Class"
//       (lines 10748–10945 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md)
//       Primitive type table: Table 9.1-1 (lines 2429–2537)
//
// CERTs covered:
//   CXX-004937 — xs::<T> type definitions match Table 9.1-1 "Type Definition" column
//   CXX-005765 — <T>Accessor exists in uci::base, publicly inherits uci::base::Accessor;
//                each type's class is defined when uci/base/<T>Accessor.h is included
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
//   Duration (int64_t), Time (int64_t), DateTime (int64_t)
//
// Successful compilation IS the test for the properties that hold.

// CXX-005765: each <T>Accessor class is defined when uci/base/<T>Accessor.h is included.
// Include the per-type forwarding headers here to verify the requirement.
#include "uci/base/BooleanAccessor.h"
#include "uci/base/LongAccessor.h"
#include "uci/base/IntAccessor.h"
#include "uci/base/ShortAccessor.h"
#include "uci/base/ByteAccessor.h"
#include "uci/base/UnsignedIntAccessor.h"
#include "uci/base/UnsignedShortAccessor.h"
#include "uci/base/UnsignedByteAccessor.h"
#include "uci/base/DoubleAccessor.h"
#include "uci/base/FloatAccessor.h"
#include "uci/base/DurationAccessor.h"
#include "uci/base/TimeAccessor.h"
#include "uci/base/DateTimeAccessor.h"

#include "xs/accessorType.h"

#include <cstdint>
#include <type_traits>

// ---------------------------------------------------------------------------
// CXX-004937: xs::<T> type definitions must match Table 9.1-1 exactly.
// Duration, Time, and DateTime must be int64_t (NOT std::string).
// ---------------------------------------------------------------------------

static_assert(std::is_same_v<xs::Boolean,      bool>,     "CXX-004937: xs::Boolean must be bool");
static_assert(std::is_same_v<xs::Long,          int64_t>,  "CXX-004937: xs::Long must be int64_t");
static_assert(std::is_same_v<xs::Int,           int32_t>,  "CXX-004937: xs::Int must be int32_t");
static_assert(std::is_same_v<xs::Short,         int16_t>,  "CXX-004937: xs::Short must be int16_t");
static_assert(std::is_same_v<xs::Byte,          int8_t>,   "CXX-004937: xs::Byte must be int8_t");
static_assert(std::is_same_v<xs::UnsignedInt,   uint32_t>, "CXX-004937: xs::UnsignedInt must be uint32_t");
static_assert(std::is_same_v<xs::UnsignedShort, uint16_t>, "CXX-004937: xs::UnsignedShort must be uint16_t");
static_assert(std::is_same_v<xs::UnsignedByte,  uint8_t>,  "CXX-004937: xs::UnsignedByte must be uint8_t");
static_assert(std::is_same_v<xs::Double,        double>,   "CXX-004937: xs::Double must be double");
static_assert(std::is_same_v<xs::Float,         float>,    "CXX-004937: xs::Float must be float");
static_assert(std::is_same_v<xs::Duration,      int64_t>,  "CXX-004937: xs::Duration must be int64_t (Table 9.1-1)");
static_assert(std::is_same_v<xs::Time,          int64_t>,  "CXX-004937: xs::Time must be int64_t (Table 9.1-1)");
static_assert(std::is_same_v<xs::DateTime,      int64_t>,  "CXX-004937: xs::DateTime must be int64_t (Table 9.1-1)");

// ---------------------------------------------------------------------------
// CXX-005765: <T>Accessor exists in uci::base and publicly inherits
// uci::base::Accessor for every type in Table 9.1-1.
// ---------------------------------------------------------------------------

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

// ---------------------------------------------------------------------------
// CXX-011089 (continued): operator xs::<T>() const for Duration, Time, DateTime.
// ---------------------------------------------------------------------------

static_assert(std::is_convertible_v<uci::base::DurationAccessor, xs::Duration>,
    "CXX-011089: DurationAccessor must be implicitly convertible to xs::Duration");

static_assert(std::is_convertible_v<uci::base::TimeAccessor, xs::Time>,
    "CXX-011089: TimeAccessor must be implicitly convertible to xs::Time");

static_assert(std::is_convertible_v<uci::base::DateTimeAccessor, xs::DateTime>,
    "CXX-011089: DateTimeAccessor must be implicitly convertible to xs::DateTime");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DurationAccessor&>().operator xs::Duration()), xs::Duration>,
    "CXX-011089: DurationAccessor::operator xs::Duration() must return xs::Duration");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::TimeAccessor&>().operator xs::Time()), xs::Time>,
    "CXX-011089: TimeAccessor::operator xs::Time() must return xs::Time");

static_assert(
    std::is_same_v<decltype(std::declval<const uci::base::DateTimeAccessor&>().operator xs::DateTime()), xs::DateTime>,
    "CXX-011089: DateTimeAccessor::operator xs::DateTime() must return xs::DateTime");

// ---------------------------------------------------------------------------
// CXX-013023 (continued): operator=(xs::<T>) for Duration, Time, DateTime.
// ---------------------------------------------------------------------------

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::DurationAccessor&>() = std::declval<xs::Duration>()),
        uci::base::DurationAccessor&>,
    "CXX-013023: DurationAccessor::operator=(xs::Duration) must return DurationAccessor&");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::TimeAccessor&>() = std::declval<xs::Time>()),
        uci::base::TimeAccessor&>,
    "CXX-013023: TimeAccessor::operator=(xs::Time) must return TimeAccessor&");

static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::DateTimeAccessor&>() = std::declval<xs::DateTime>()),
        uci::base::DateTimeAccessor&>,
    "CXX-013023: DateTimeAccessor::operator=(xs::DateTime) must return DateTimeAccessor&");

// ---------------------------------------------------------------------------
// CXX-011088 (continued): operator=(const <T>Accessor&) for Duration, Time, DateTime.
// ---------------------------------------------------------------------------

static_assert(std::is_copy_assignable_v<uci::base::DurationAccessor>,
    "CXX-011088: DurationAccessor& operator=(const DurationAccessor&) must be public");

static_assert(std::is_copy_assignable_v<uci::base::TimeAccessor>,
    "CXX-011088: TimeAccessor& operator=(const TimeAccessor&) must be public");

static_assert(std::is_copy_assignable_v<uci::base::DateTimeAccessor>,
    "CXX-011088: DateTimeAccessor& operator=(const DateTimeAccessor&) must be public");
