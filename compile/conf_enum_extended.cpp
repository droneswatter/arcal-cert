// Compile-only conformance: gaps not covered by conf_enum.cpp
// Covers CERTs: CXX-006211, CXX-011062, CXX-011149, CXX-006240,
//               CXX-006323, CXX-006340, CXX-006357, CXX-006374,
//               CXX-006391, CXX-006408, CXX-006417, CXX-006424,
//               CXX-006457
// Reference type: uci::type::SystemStateEnum
#include "uci/type/SystemStateEnum.h"
#include <ostream>
#include <sstream>
#include <string>
#include <type_traits>

using E = uci::type::SystemStateEnum;

// ── CERT CXX-011149 ──────────────────────────────────────────────────────────
// getValue() must accept bool testForValidity=true as a default parameter.
// Verify both arities resolve.
static_assert(
    std::is_same_v<
        decltype(std::declval<const E>().getValue(true)),
        E::EnumerationItem>,
    "CERT CXX-011149: getValue(bool=true) overload must exist");

static_assert(
    std::is_same_v<
        decltype(std::declval<const E>().getValue(false)),
        E::EnumerationItem>,
    "CERT CXX-011149: getValue(bool=false) overload must exist");

// ── CERT CXX-006240 ──────────────────────────────────────────────────────────
// getNumberOfItems() must be a non-static const instance method (not static).
// A static method cannot be called on a const instance expression as a member
// function; we verify the instance call resolves and yields int.
static_assert(
    std::is_same_v<
        decltype(std::declval<const E>().getNumberOfItems()),
        int>,
    "CERT CXX-006240: const int getNumberOfItems() instance method must exist");

// The spec says non-static, so verify it is NOT callable as E::getNumberOfItems().
// (If the generated code provides it as a static method this static_assert fails.)
// We express this as: a pointer-to-member-function must be formable.
static_assert(
    std::is_same_v<
        decltype(&E::getNumberOfItems),
        int (E::*)() const>,
    "CERT CXX-006240: getNumberOfItems must be a non-static const member, not static");

// ── CERT CXX-006211 ──────────────────────────────────────────────────────────
// Public non-static T& operator=(const T&) must exist.
// (Protected =default is insufficient; the spec requires a public overload.)
static_assert(
    std::is_same_v<
        decltype(std::declval<E&>() = std::declval<const E&>()),
        E&>,
    "CERT CXX-006211: public E& operator=(const E&) must exist");

// ── CERT CXX-011062 ──────────────────────────────────────────────────────────
// Public T& operator=(EnumerationItem) must exist.
static_assert(
    std::is_same_v<
        decltype(std::declval<E&>() = E::enumNotSet),
        E&>,
    "CERT CXX-011062: public E& operator=(EnumerationItem) must exist");

// ── CERT CXX-006417 ──────────────────────────────────────────────────────────
// static std::string toName(EnumerationItem) must exist alongside instance toName().
static_assert(
    std::is_same_v<
        decltype(E::toName(E::enumNotSet)),
        std::string>,
    "CERT CXX-006417: static std::string toName(EnumerationItem) must exist");

// The instance variant must still be present (CERT CXX-011059, covered separately).
static_assert(
    std::is_same_v<
        decltype(std::declval<const E>().toName()),
        std::string>,
    "CERT CXX-011059: std::string toName() const instance method must exist");

// ── CERT CXX-006424 ──────────────────────────────────────────────────────────
// The spec names the method "fromName", not "valueFromName".
static_assert(
    std::is_same_v<
        decltype(E::fromName(std::string{})),
        E::EnumerationItem>,
    "CERT CXX-006424: static EnumerationItem fromName(const std::string&) must exist");

// ── CERTs CXX-006323 / CXX-006340 ────────────────────────────────────────────
// friend bool operator==(EnumerationItem lhs, const T& rhs)
// friend bool operator!=(EnumerationItem lhs, const T& rhs)
// These are injected as hidden friends; test via ADL through a function call.
void test_reversed_eq_operators() {
    E& e = E::create(nullptr);
    bool r1 = (E::enumNotSet == e);   // CERT CXX-006323
    bool r2 = (E::enumNotSet != e);   // CERT CXX-006340
    (void)r1; (void)r2;
    E::destroy(e);
}

// ── CERTs CXX-006349/CXX-006357 — operator<(EnumerationItem lhs, const T&) ───
void test_reversed_lt_operator() {
    E& e = E::create(nullptr);
    bool r = (E::enumNotSet < e);     // CERT CXX-006357
    (void)r;
    E::destroy(e);
}

// ── CERTs CXX-006366/CXX-006374 — operator<=(EnumerationItem lhs, const T&) ─
void test_reversed_le_operator() {
    E& e = E::create(nullptr);
    bool r = (E::enumNotSet <= e);    // CERT CXX-006374
    (void)r;
    E::destroy(e);
}

// ── CERTs CXX-006383/CXX-006391 — operator>(EnumerationItem lhs, const T&) ──
void test_reversed_gt_operator() {
    E& e = E::create(nullptr);
    bool r = (E::enumNotSet > e);     // CERT CXX-006391
    (void)r;
    E::destroy(e);
}

// ── CERTs CXX-006400/CXX-006408 — operator>=(EnumerationItem lhs, const T&) ─
void test_reversed_ge_operator() {
    E& e = E::create(nullptr);
    bool r = (E::enumNotSet >= e);    // CERT CXX-006408
    (void)r;
    E::destroy(e);
}

// ── CERT CXX-006457 ──────────────────────────────────────────────────────────
// operator<< must be a free function template in the global namespace:
//   template<typename charT, typename traits>
//   std::basic_ostream<charT,traits>& operator<<(
//       std::basic_ostream<charT,traits>&, const T&)
// A non-template friend operator<< inside the class satisfies std::ostream but
// NOT std::wostringstream.  This test catches the narrow-only implementation.
void test_wide_stream_operator() {
    E& e = E::create(nullptr);
    std::wostringstream wos;
    wos << e;   // must compile via the template overload
    E::destroy(e);
}
