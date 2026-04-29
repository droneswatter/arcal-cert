// Compile-only conformance: uci::base::Accessor class shape.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, Section 9.4 (lines 2996–3256)
//
// CERT IDs verified here:
//   CXX-004987 — class uci::base::Accessor exists in namespace uci::base
//   CXX-011090 — destructor ~Accessor() is protected (not publicly accessible)
//   CXX-004993 — public const getAccessorType() is non-throwing (noexcept / throw())
//   CXX-004997 — public non-static void reset() is declared
//   CXX-004998 — default constructor Accessor() is protected
//   CXX-004999 — copy constructor Accessor(const Accessor&) is protected
//   CXX-011148 — copy-assignment operator=(const Accessor&) is protected
//
// Successful compilation IS the test. No runtime, no DDS required.

#include "uci/base/Accessor.h"
#include "uci/base/accessorType.h"

#include <type_traits>

// ---------------------------------------------------------------------------
// CXX-004987: class uci::base::Accessor exists in that namespace.
// A forward-declaration alone would satisfy the namespace check; using the
// full include ensures the complete class definition is present.
// ---------------------------------------------------------------------------
static_assert(std::is_class_v<uci::base::Accessor>,
    "CXX-004987: uci::base::Accessor must be a class");

// ---------------------------------------------------------------------------
// CXX-011090: destructor is protected (not publicly destructible).
// std::is_destructible is false when the destructor is inaccessible.
// ---------------------------------------------------------------------------
static_assert(!std::is_destructible_v<uci::base::Accessor>,
    "CXX-011090: ~Accessor() must be protected, not public");

// ---------------------------------------------------------------------------
// CXX-004993: getAccessorType() is public, const, and non-throwing.
//
// We verify the return type and noexcept-ness via a member-function pointer.
// The pointer is formed in a context where protected members are NOT
// accessible, so a compilation error here would also flag a visibility issue.
// ---------------------------------------------------------------------------
namespace {

// Concrete subclass used only to satisfy the pure-virtual interface;
// it must live in an anonymous namespace so it cannot be used externally.
struct ConcreteAccessor : public uci::base::Accessor {
    uci::base::accessorType::AccessorType getAccessorType() const noexcept override {
        return uci::base::accessorType::null;
    }
    void reset() noexcept override {}
    const std::string& typeName() const override {
        static const std::string n{"ConcreteAccessor"};
        return n;
    }
};

// CXX-004993 — return type is uci::base::accessorType::AccessorType and noexcept.
using GetAccessorTypeFn = uci::base::accessorType::AccessorType (uci::base::Accessor::*)() const noexcept;
static_assert(std::is_same_v<
    decltype(static_cast<GetAccessorTypeFn>(&uci::base::Accessor::getAccessorType)),
    GetAccessorTypeFn>,
    "CXX-004993: getAccessorType() must be public, const, return AccessorType, and be noexcept");

// CXX-004997 — void reset() is public.
using ResetFn = void (uci::base::Accessor::*)();
static_assert(std::is_same_v<
    decltype(static_cast<ResetFn>(&uci::base::Accessor::reset)),
    ResetFn>,
    "CXX-004997: void reset() must be a public non-static member function");

// ---------------------------------------------------------------------------
// CXX-004998: default constructor is protected (not publicly constructible).
// CXX-004999: copy constructor is protected (not publicly copy-constructible).
// CXX-011148: copy-assignment is protected (not publicly copy-assignable).
//
// std::is_default_constructible / is_copy_constructible / is_copy_assignable
// return false when the respective special member is inaccessible.
// ---------------------------------------------------------------------------
static_assert(!std::is_default_constructible_v<uci::base::Accessor>,
    "CXX-004998: Accessor() must be protected, not public");

static_assert(!std::is_copy_constructible_v<uci::base::Accessor>,
    "CXX-004999: Accessor(const Accessor&) must be protected, not public");

static_assert(!std::is_copy_assignable_v<uci::base::Accessor>,
    "CXX-011148: operator=(const Accessor&) must be protected, not public");

// ---------------------------------------------------------------------------
// Sanity check: the protected members ARE accessible from within a subclass.
// This verifies the header actually provides the protected members (rather
// than deleting them), satisfying the intent of the spec.
// ---------------------------------------------------------------------------
static_assert(std::is_default_constructible_v<ConcreteAccessor>,
    "Subclass of Accessor must be default-constructible via the protected ctor");
static_assert(std::is_copy_constructible_v<ConcreteAccessor>,
    "Subclass of Accessor must be copy-constructible via the protected copy ctor");
static_assert(std::is_copy_assignable_v<ConcreteAccessor>,
    "Subclass of Accessor must be copy-assignable via the protected operator=");

} // anonymous namespace
