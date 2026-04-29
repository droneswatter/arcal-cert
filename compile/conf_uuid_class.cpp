// Compile-only conformance: uci::base::UUID class shape (OMSC-SPC-008 RevK).
//
// CERT CXX-005296  — class UUID in namespace uci::base
// CERT CXX-005300  — m_numberOfOctets == 16
// CERT CXX-012548  — m_sizeOfNodeAddress == 6
// CERT CXX-005307  — Octet = uint8_t
// CERT CXX-005310  — Octets = std::vector<Octet>
// CERT CXX-005311  — NodeAddress = std::vector<uint8_t>
// CERT CXX-005312  — Timestamp = uint64_t
// CERT CXX-005314  — ClockSequence = uint16_t
// CERT CXX-005316  — Variant enum with correct enumerators
// CERT CXX-005317  — Version enum with correct enumerators
// CERT CXX-005318  — ValueUUID struct exists
// CERT CXX-005319  — ValueUUID::mostSignificantBits is uint64_t
// CERT CXX-005320  — ValueUUID::leastSignificantBits is uint64_t
// CERT CXX-011150  — static UUID fromString(const std::string&)
// CERT CXX-011152  — static UUID fromOctets(const Octets&)
// CERT CXX-011165  — static UUID generateUUID()
// CERT CXX-012574  — static UUID getNamespaceUUID()
// CERT CXX-012587  — static UUID createVersion3UUID(const UUID&, const std::string&)
// CERT CXX-012600  — static UUID createVersion3UUID(const std::string&)
// CERT CXX-005328  — Octets getOctets() const
// CERT CXX-005329  — ValueUUID getValueUUID() const
// CERT CXX-005331  — std::string toString() const
// CERT CXX-005332  — Variant getVariant() const
// CERT CXX-005334  — Version getVersion() const
// CERT CXX-005336  — ClockSequence getClockSequence() const
// CERT CXX-005337  — Timestamp getTimestamp() const
// CERT CXX-005338  — NodeAddress getNodeAddress() const
// CERT CXX-005339  — bool operator==(const UUID&) const
// CERT CXX-005340  — bool operator!=(const UUID&) const
// CERT CXX-005351  — bool operator<(const UUID&) const
// CERT CXX-005358  — bool operator<=(const UUID&) const
// CERT CXX-005365  — bool operator>(const UUID&) const
// CERT CXX-005372  — bool operator>=(const UUID&) const
// CERT CXX-005379  — bool isNil() const
// CERT CXX-012615  — bool isValid() const
// CERT CXX-005387  — static const char* toString(Variant) noexcept
// CERT CXX-005396  — static const char* toString(Version) noexcept
// CERT CXX-012628  — explicit UUID(const ValueUUID& = ValueUUID())
// CERT CXX-012641  — UUID(const char*)
// CERT CXX-012654  — UUID(uint64_t, uint64_t)
// CERT CXX-005411  — public copy constructor UUID(const UUID&)
// CERT CXX-011154  — UUID& operator=(const UUID&)
// CERT CXX-012657  — std::hash<uci::base::UUID> specialization enabled on C++11+

#include "uci/base/UUID.h"

#include <cstdint>
#include <functional>
#include <string>
#include <type_traits>
#include <vector>

using UUID = uci::base::UUID;

namespace {

// ── CXX-005296: class exists in uci::base ────────────────────────────────────
static_assert(std::is_class_v<UUID>,
    "CXX-005296: uci::base::UUID must be a class");

// ── CXX-005300 / CXX-012548: static size constants ───────────────────────────
static_assert(UUID::m_numberOfOctets == 16,
    "CXX-005300: m_numberOfOctets must equal 16");
static_assert(UUID::m_sizeOfNodeAddress == 6,
    "CXX-012548: m_sizeOfNodeAddress must equal 6");
static_assert(std::is_same_v<decltype(UUID::m_numberOfOctets), const std::size_t>,
    "CXX-005300: m_numberOfOctets must be of type std::size_t");
static_assert(std::is_same_v<decltype(UUID::m_sizeOfNodeAddress), const std::size_t>,
    "CXX-012548: m_sizeOfNodeAddress must be of type std::size_t");

// ── CXX-005307: Octet = uint8_t ──────────────────────────────────────────────
static_assert(std::is_same_v<UUID::Octet, uint8_t>,
    "CXX-005307: UUID::Octet must be equivalent to uint8_t");

// ── CXX-005310: Octets = std::vector<Octet> ──────────────────────────────────
static_assert(std::is_same_v<UUID::Octets, std::vector<UUID::Octet>>,
    "CXX-005310: UUID::Octets must be equivalent to std::vector<Octet>");

// ── CXX-005311: NodeAddress = std::vector<uint8_t> ───────────────────────────
static_assert(std::is_same_v<UUID::NodeAddress, std::vector<uint8_t>>,
    "CXX-005311: UUID::NodeAddress must be equivalent to std::vector<uint8_t>");

// ── CXX-005312: Timestamp = uint64_t ─────────────────────────────────────────
static_assert(std::is_same_v<UUID::Timestamp, uint64_t>,
    "CXX-005312: UUID::Timestamp must be equivalent to uint64_t");

// ── CXX-005314: ClockSequence = uint16_t ─────────────────────────────────────
static_assert(std::is_same_v<UUID::ClockSequence, uint16_t>,
    "CXX-005314: UUID::ClockSequence must be equivalent to uint16_t");

// ── CXX-005316: Variant enum enumerators ─────────────────────────────────────
static_assert(std::is_enum_v<UUID::Variant>,
    "CXX-005316: UUID::Variant must be an enum");
// Verify each required enumerator compiles and is a Variant value.
constexpr UUID::Variant v0 = UUID::variantNCS;
constexpr UUID::Variant v1 = UUID::variantMicrosoft;
constexpr UUID::Variant v2 = UUID::variantCurrent;
constexpr UUID::Variant v3 = UUID::variantFuture;
constexpr UUID::Variant v4 = UUID::variantUnknown;
static_assert(v0 == UUID::variantNCS && v1 == UUID::variantMicrosoft &&
              v2 == UUID::variantCurrent && v3 == UUID::variantFuture &&
              v4 == UUID::variantUnknown,
    "CXX-005316: all required UUID::Variant enumerators must compile");

// ── CXX-005317: Version enum enumerators ─────────────────────────────────────
static_assert(std::is_enum_v<UUID::Version>,
    "CXX-005317: UUID::Version must be an enum");
constexpr UUID::Version ver0 = UUID::versionNil;
constexpr UUID::Version ver1 = UUID::versionTimeBased;
constexpr UUID::Version ver2 = UUID::versionDceSecurity;
constexpr UUID::Version ver3 = UUID::versionNameBasedMD5;
constexpr UUID::Version ver4 = UUID::versionRandomNumber;
constexpr UUID::Version ver5 = UUID::versionNameBasedSHA1;
constexpr UUID::Version ver6 = UUID::versionUnknown;
static_assert(ver0 == UUID::versionNil && ver1 == UUID::versionTimeBased &&
              ver2 == UUID::versionDceSecurity && ver3 == UUID::versionNameBasedMD5 &&
              ver4 == UUID::versionRandomNumber && ver5 == UUID::versionNameBasedSHA1 &&
              ver6 == UUID::versionUnknown,
    "CXX-005317: all required UUID::Version enumerators must compile");

// ── CXX-005318: ValueUUID struct ─────────────────────────────────────────────
static_assert(std::is_class_v<UUID::ValueUUID>,
    "CXX-005318: UUID::ValueUUID must be a struct/class");

// ── CXX-005319 / CXX-005320: ValueUUID fields are uint64_t ───────────────────
static_assert(std::is_same_v<decltype(UUID::ValueUUID::mostSignificantBits), uint64_t>,
    "CXX-005319: ValueUUID::mostSignificantBits must be uint64_t");
static_assert(std::is_same_v<decltype(UUID::ValueUUID::leastSignificantBits), uint64_t>,
    "CXX-005320: ValueUUID::leastSignificantBits must be uint64_t");

// ── CXX-011150: static UUID fromString(const std::string&) ───────────────────
static_assert(
    std::is_same_v<decltype(UUID::fromString(std::declval<const std::string&>())), UUID>,
    "CXX-011150: UUID::fromString(const std::string&) must return UUID by value");

// ── CXX-011152: static UUID fromOctets(const Octets&) ────────────────────────
static_assert(
    std::is_same_v<decltype(UUID::fromOctets(std::declval<const UUID::Octets&>())), UUID>,
    "CXX-011152: UUID::fromOctets(const Octets&) must return UUID by value");

// ── CXX-011165: static UUID generateUUID() ───────────────────────────────────
static_assert(
    std::is_same_v<decltype(UUID::generateUUID()), UUID>,
    "CXX-011165: UUID::generateUUID() must return UUID by value");

// ── CXX-012574: static UUID getNamespaceUUID() ───────────────────────────────
static_assert(
    std::is_same_v<decltype(UUID::getNamespaceUUID()), UUID>,
    "CXX-012574: UUID::getNamespaceUUID() must return UUID by value");

// ── CXX-012587: static UUID createVersion3UUID(const UUID&, const std::string&)
static_assert(
    std::is_same_v<
        decltype(UUID::createVersion3UUID(std::declval<const UUID&>(), std::declval<const std::string&>())),
        UUID>,
    "CXX-012587: UUID::createVersion3UUID(const UUID&, const std::string&) must return UUID by value");

// ── CXX-012600: static UUID createVersion3UUID(const std::string&) ───────────
static_assert(
    std::is_same_v<
        decltype(UUID::createVersion3UUID(std::declval<const std::string&>())),
        UUID>,
    "CXX-012600: UUID::createVersion3UUID(const std::string&) must return UUID by value");

// ── CXX-005328: Octets getOctets() const ─────────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getOctets()), UUID::Octets>,
    "CXX-005328: UUID::getOctets() must return Octets by value");

// ── CXX-005329: ValueUUID getValueUUID() const ───────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getValueUUID()), UUID::ValueUUID>,
    "CXX-005329: UUID::getValueUUID() must return ValueUUID by value");

// ── CXX-005331: std::string toString() const ─────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().toString()), std::string>,
    "CXX-005331: UUID::toString() must return std::string by value");

// ── CXX-005332: Variant getVariant() const ───────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getVariant()), UUID::Variant>,
    "CXX-005332: UUID::getVariant() must return Variant");

// ── CXX-005334: Version getVersion() const ───────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getVersion()), UUID::Version>,
    "CXX-005334: UUID::getVersion() must return Version");

// ── CXX-005336: ClockSequence getClockSequence() const ───────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getClockSequence()), UUID::ClockSequence>,
    "CXX-005336: UUID::getClockSequence() must return ClockSequence");

// ── CXX-005337: Timestamp getTimestamp() const ───────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getTimestamp()), UUID::Timestamp>,
    "CXX-005337: UUID::getTimestamp() must return Timestamp");

// ── CXX-005338: NodeAddress getNodeAddress() const ───────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().getNodeAddress()), UUID::NodeAddress>,
    "CXX-005338: UUID::getNodeAddress() must return NodeAddress");

// ── CXX-005339: bool operator==(const UUID&) const ───────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() == std::declval<const UUID&>()), bool>,
    "CXX-005339: UUID::operator==(const UUID&) must return bool");

// ── CXX-005340: bool operator!=(const UUID&) const ───────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() != std::declval<const UUID&>()), bool>,
    "CXX-005340: UUID::operator!=(const UUID&) must return bool");

// ── CXX-005351: bool operator<(const UUID&) const ────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() < std::declval<const UUID&>()), bool>,
    "CXX-005351: UUID::operator<(const UUID&) must return bool");

// ── CXX-005358: bool operator<=(const UUID&) const ───────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() <= std::declval<const UUID&>()), bool>,
    "CXX-005358: UUID::operator<=(const UUID&) must return bool");

// ── CXX-005365: bool operator>(const UUID&) const ────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() > std::declval<const UUID&>()), bool>,
    "CXX-005365: UUID::operator>(const UUID&) must return bool");

// ── CXX-005372: bool operator>=(const UUID&) const ───────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>() >= std::declval<const UUID&>()), bool>,
    "CXX-005372: UUID::operator>=(const UUID&) must return bool");

// ── CXX-005379: bool isNil() const ───────────────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().isNil()), bool>,
    "CXX-005379: UUID::isNil() must return bool");

// ── CXX-012615: bool isValid() const ─────────────────────────────────────────
static_assert(
    std::is_same_v<decltype(std::declval<const UUID&>().isValid()), bool>,
    "CXX-012615: UUID::isValid() must return bool");

// ── CXX-005387: static const char* toString(Variant) noexcept ────────────────
// Use a function-pointer check to verify the exact noexcept signature.
// The spec requires the function to be non-throwing (throw() / noexcept).
static_assert(
    std::is_same_v<decltype(UUID::toString(std::declval<UUID::Variant>())), const char*>,
    "CXX-005387: UUID::toString(Variant) must return const char*");
static_assert(
    noexcept(UUID::toString(std::declval<UUID::Variant>())),
    "CXX-005387: UUID::toString(Variant) must be declared noexcept (non-throwing)");

// ── CXX-005396: static const char* toString(Version) noexcept ────────────────
static_assert(
    std::is_same_v<decltype(UUID::toString(std::declval<UUID::Version>())), const char*>,
    "CXX-005396: UUID::toString(Version) must return const char*");
static_assert(
    noexcept(UUID::toString(std::declval<UUID::Version>())),
    "CXX-005396: UUID::toString(Version) must be declared noexcept (non-throwing)");

// ── CXX-012628: explicit UUID(const ValueUUID& = ValueUUID()) ────────────────
// The spec requires a SINGLE explicit constructor that accepts a ValueUUID with
// a default argument, making it also serve as the default constructor.
// Verify that default-construction and ValueUUID construction both compile,
// and that the ValueUUID overload is explicit (cannot be used implicitly).
static_assert(std::is_default_constructible_v<UUID>,
    "CXX-012628: UUID must be default-constructible via UUID(const ValueUUID& = ValueUUID())");
static_assert(std::is_constructible_v<UUID, const UUID::ValueUUID&>,
    "CXX-012628: UUID must be constructible from const ValueUUID&");
// The ValueUUID constructor must be explicit — copy-initialization from a
// ValueUUID prvalue must NOT compile.  Verified via is_convertible (implicit
// conversion path).  explicit constructors are not counted as implicit
// conversions, so this must be false.
static_assert(!std::is_convertible_v<UUID::ValueUUID, UUID>,
    "CXX-012628: UUID(const ValueUUID&) must be explicit — implicit conversion from ValueUUID must be rejected");

// ── CXX-012641: UUID(const char*) ────────────────────────────────────────────
static_assert(std::is_constructible_v<UUID, const char*>,
    "CXX-012641: UUID must be constructible from const char*");

// ── CXX-012654: UUID(uint64_t, uint64_t) ─────────────────────────────────────
static_assert(std::is_constructible_v<UUID, uint64_t, uint64_t>,
    "CXX-012654: UUID must be constructible from (uint64_t, uint64_t)");

// ── CXX-005411: public copy constructor UUID(const UUID&) ────────────────────
static_assert(std::is_copy_constructible_v<UUID>,
    "CXX-005411: UUID must have a public copy constructor");

// ── CXX-011154: UUID& operator=(const UUID&) ─────────────────────────────────
static_assert(std::is_copy_assignable_v<UUID>,
    "CXX-011154: UUID must have a public copy assignment operator");
static_assert(
    std::is_same_v<decltype(std::declval<UUID&>() = std::declval<const UUID&>()), UUID&>,
    "CXX-011154: UUID::operator=(const UUID&) must return UUID&");

// ── CXX-012657: std::hash<uci::base::UUID> specialization ────────────────────
// The spec requires the specialization to be enabled when __cplusplus >= 201103.
// Since this file is compiled as C++17 or later, the specialization must be
// present and callable.
static_assert(
    std::is_default_constructible_v<std::hash<UUID>>,
    "CXX-012657: std::hash<uci::base::UUID> must be defined (specialization must exist on C++11+)");
static_assert(
    std::is_invocable_r_v<std::size_t, std::hash<UUID>, const UUID&>,
    "CXX-012657: std::hash<uci::base::UUID>::operator() must return std::size_t and accept const UUID&");

} // namespace
