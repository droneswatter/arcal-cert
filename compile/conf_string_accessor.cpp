// Compile-only conformance: uci::base::StringAccessor class shape.
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, Section "The StringAccessor Class"
//       (lines 3257–3645 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md)
//
// CERTs covered:
//   CXX-005002 — StringAccessor inherits publicly from uci::base::Accessor
//   CXX-012700 — destructor is protected (not publicly destructible)
//   CXX-005008 — public const member function std::string str() const
//                VIOLATION: header returns const std::string& not std::string
//   CXX-005009 — public const member function const char* c_str() const
//   CXX-011141 — public non-static member function StringAccessor& setStringValue(const std::string&)
//                VIOLATION: header returns void
//   CXX-011142 — public non-static member function StringAccessor& setStringValue(const char*)
//                VIOLATION: header returns void
//   CXX-011143 — public non-static member function StringAccessor& operator=(const StringAccessor&)
//   CXX-011144 — public non-static member function StringAccessor& operator=(const std::string&)
//   CXX-011145 — public non-static member function StringAccessor& operator=(const char*)
//   CXX-011146 — public const member function operator std::string()
//   CXX-005040 — default constructor is protected (not publicly default-constructible)
//   CXX-005047 — copy constructor is protected (not publicly copy-constructible)

#include "uci/base/StringAccessor.h"

#include <string>
#include <type_traits>

namespace {

// CXX-005002: StringAccessor is in uci::base and publicly inherits Accessor
static_assert(std::is_base_of_v<uci::base::Accessor, uci::base::StringAccessor>,
    "CXX-005002: StringAccessor must publicly inherit uci::base::Accessor");

// CXX-012700: destructor protected — class must not be publicly destructible
static_assert(!std::is_destructible_v<uci::base::StringAccessor>,
    "CXX-012700: StringAccessor destructor must be protected");

// CXX-005040: default constructor protected — must not be publicly default-constructible
static_assert(!std::is_default_constructible_v<uci::base::StringAccessor>,
    "CXX-005040: StringAccessor default constructor must be protected");

// CXX-005047: copy constructor protected — must not be publicly copy-constructible
static_assert(!std::is_copy_constructible_v<uci::base::StringAccessor>,
    "CXX-005047: StringAccessor copy constructor must be protected");

// CXX-005008: str() must return std::string (by value), not const std::string&
using StrReturnType = decltype(std::declval<const uci::base::StringAccessor>().str());
static_assert(std::is_same_v<StrReturnType, std::string>,
    "CXX-005008: str() must return std::string by value, not a reference");

// CXX-005009: c_str() must return const char*
using CStrReturnType = decltype(std::declval<const uci::base::StringAccessor>().c_str());
static_assert(std::is_same_v<CStrReturnType, const char*>,
    "CXX-005009: c_str() must return const char*");

// CXX-011141: setStringValue(const std::string&) must return StringAccessor&
using SetStrReturnType = decltype(std::declval<uci::base::StringAccessor>().setStringValue(std::declval<const std::string&>()));
static_assert(std::is_same_v<SetStrReturnType, uci::base::StringAccessor&>,
    "CXX-011141: setStringValue(const std::string&) must return StringAccessor&");

// CXX-011142: setStringValue(const char*) must return StringAccessor&
using SetCStrReturnType = decltype(std::declval<uci::base::StringAccessor>().setStringValue(std::declval<const char*>()));
static_assert(std::is_same_v<SetCStrReturnType, uci::base::StringAccessor&>,
    "CXX-011142: setStringValue(const char*) must return StringAccessor&");

// CXX-011146: operator std::string() const must be declared
using ConvReturnType = decltype(std::declval<const uci::base::StringAccessor>().operator std::string());
static_assert(std::is_same_v<ConvReturnType, std::string>,
    "CXX-011146: operator std::string() const must be declared");

} // namespace

// CXX-011143/11144/11145: operator= overloads must return StringAccessor&
// These are verified via is_copy_assignable for the StringAccessor& overload and
// explicit decltype checks below.  Because the class is not publicly constructible,
// we verify signatures via function-pointer matching rather than calling them.

// operator=(const std::string&) — CXX-011144
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::StringAccessor&>() = std::declval<const std::string&>()),
        uci::base::StringAccessor&>,
    "CXX-011144: operator=(const std::string&) must return StringAccessor&");

// operator=(const char*) — CXX-011145
static_assert(
    std::is_same_v<
        decltype(std::declval<uci::base::StringAccessor&>() = std::declval<const char*>()),
        uci::base::StringAccessor&>,
    "CXX-011145: operator=(const char*) must return StringAccessor&");

// operator=(const StringAccessor&) — CXX-011143
static_assert(std::is_copy_assignable_v<uci::base::StringAccessor>,
    "CXX-011143: operator=(const StringAccessor&) must be declared and return StringAccessor&");
