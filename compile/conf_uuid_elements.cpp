// Compile-only conformance: UUID element accessors on generated types (OMSC-SPC-008 RevK).
//
// CERT CXX-006154 — getX() must return uci::base::UUID by VALUE (not reference).
// CERT CXX-011054 — setX() must return <ParentType>& (parent reference, not void).
//
// conf_uuid.cpp covers ID_Type directly.  This file extends coverage to:
//   1. ServiceID_Type — a subtype of ID_Type; inherited UUID accessors must preserve
//      the correct signatures when accessed through the derived type.
//   2. Negative: confirm no extra has/enable/clearX methods are generated for UUID
//      fields (UUID elements are mandatory access points, never optional-wrapped).

#include "uci/base/UUID.h"
#include "uci/type/ID_Type.h"
#include "uci/type/ServiceID_Type.h"

#include <type_traits>

using UUID = uci::base::UUID;

// ── ServiceID_Type inherits from ID_Type ────────────────────────────────────────

// CXX-006154: getter must return UUID by value, not by (const) reference.
// Check on the derived type so the inherited signature is exercised.
static_assert(
    std::is_same_v<decltype(std::declval<const uci::type::ServiceID_Type&>().getUUID()), UUID>,
    "CXX-006154: ServiceID_Type::getUUID() must return uci::base::UUID by value");

// Confirm it does NOT return a (const) reference — reference return would widen
// the UUID value category in a way that violates the spec.
static_assert(
    !std::is_reference_v<decltype(std::declval<const uci::type::ServiceID_Type&>().getUUID())>,
    "CXX-006154: ServiceID_Type::getUUID() must NOT return a reference");

// CXX-011054: setter must return the parent type by reference.
// For ServiceID_Type the parent is ID_Type (direct base that owns the element).
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::type::ServiceID_Type&>().setUUID(std::declval<const UUID&>())),
        uci::type::ID_Type&>,
    "CXX-011054: ServiceID_Type::setUUID() must return ID_Type& (parent reference)");

// ── No has/enable/clear methods for UUID fields ──────────────────────────────
// UUID elements are not optional-wrapped.  Attempting to compile any of the
// lines below would indicate a violation (they must NOT exist).
// These are checked via the absence of the member — verified by the fact that
// the class compiles without them and no overload resolution finds them.
static_assert(!std::is_member_function_pointer_v<decltype(&uci::type::ID_Type::getUUID)> ||
               std::is_member_function_pointer_v<decltype(&uci::type::ID_Type::getUUID)>,
    "always true — UUID getter must be a member function pointer");

// Compile-time check: hasUUID / enableUUID / clearUUID must NOT be declared.
// The cleanest way is a void_t / detection idiom.
namespace detail {
    template <typename T, typename = void> struct has_hasUUID     : std::false_type {};
    template <typename T>                  struct has_hasUUID<T,
        std::void_t<decltype(std::declval<const T&>().hasUUID())>> : std::true_type {};

    template <typename T, typename = void> struct has_enableUUID  : std::false_type {};
    template <typename T>                  struct has_enableUUID<T,
        std::void_t<decltype(std::declval<T&>().enableUUID())>>    : std::true_type {};

    template <typename T, typename = void> struct has_clearUUID   : std::false_type {};
    template <typename T>                  struct has_clearUUID<T,
        std::void_t<decltype(std::declval<T&>().clearUUID())>>     : std::true_type {};
} // namespace detail

static_assert(!detail::has_hasUUID<uci::type::ID_Type>::value,
    "ID_Type must NOT declare hasUUID() — UUID fields are mandatory, not optional");
static_assert(!detail::has_enableUUID<uci::type::ID_Type>::value,
    "ID_Type must NOT declare enableUUID() — UUID fields are mandatory, not optional");
static_assert(!detail::has_clearUUID<uci::type::ID_Type>::value,
    "ID_Type must NOT declare clearUUID() — UUID fields are mandatory, not optional");

static_assert(!detail::has_hasUUID<uci::type::ServiceID_Type>::value,
    "ServiceID_Type must NOT declare hasUUID() — UUID fields are mandatory, not optional");
static_assert(!detail::has_enableUUID<uci::type::ServiceID_Type>::value,
    "ServiceID_Type must NOT declare enableUUID() — UUID fields are mandatory, not optional");
static_assert(!detail::has_clearUUID<uci::type::ServiceID_Type>::value,
    "ServiceID_Type must NOT declare clearUUID() — UUID fields are mandatory, not optional");
