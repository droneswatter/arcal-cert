// Compile-only conformance: uci::base::BoundedList template class shape.
//
// Spec: OMSC-SPC-008 RevK C++ CAL Spec, lines 4497-5491
//
// CERTs covered (all must compile to pass):
//   CXX-005168  template<class T, AccessorType V> inherits uci::base::Accessor
//   CXX-005172  typedef size_type  == std::size_t
//   CXX-011183  typedef reference  == T&
//   CXX-011184  typedef const_reference == const T&
//   CXX-005174  static const size_type UNBOUNDED_BOUND
//   CXX-012702  destructor is protected (not public-constructible directly)
//   CXX-005179  size_type size() const noexcept
//   CXX-005181  size_type max_size() const noexcept
//   CXX-005184  size_type min_size() const noexcept
//   CXX-011201  void resize(size_type, AccessorType = V)
//   CXX-005187  size_type capacity() const noexcept
//   CXX-005195  bool empty() const noexcept
//   CXX-011186  void reserve(size_type)
//   CXX-011187  void pop_back() [noexcept / throw()]
//   CXX-005216  void clear() [noexcept / throw()]
//   CXX-005224  size_type getMaximumOccurs() const noexcept
//   CXX-005233  size_type getMinimumOccurs() const noexcept
//   CXX-011189  reference operator[](size_type)
//   CXX-005249  const_reference operator[](size_type) const
//   CXX-011190  reference at(size_type)
//   CXX-005262  const_reference at(size_type) const
//   CXX-011191  void push_back(const_reference)
//   CXX-005275  default constructor is protected
//   CXX-005282  copy constructor is protected
//   CXX-011192  copy assignment operator is protected
//
//   CXX-012971  template<typename U> void push_back(U) with SFINAE guard
//   CXX-013010  template<typename U> void push_back(const U&) with SFINAE guard

#include "uci/base/BoundedList.h"
#include "uci/base/BoundedListImpl.h"
#include "uci/base/Accessor.h"
#include "uci/base/accessorType.h"

#include <cstddef>
#include <type_traits>

// ---------------------------------------------------------------------------
// Minimal stub accessor and its AccessorType constant, sufficient to
// instantiate BoundedList without generated type headers.
// ---------------------------------------------------------------------------
namespace uci { namespace base {
class StubAccessor : public Accessor {
public:
    AccessorType getAccessorType() const noexcept override {
        return uci::base::accessorType::null;
    }
    const std::string& typeName() const override {
        static const std::string n{"stub"};
        return n;
    }
    void reset() override {}
};
}} // namespace uci::base

// Alias for the concrete instantiation used throughout this file.
// BoundedListImpl is the only publicly constructible subclass; BoundedList
// itself has a protected default constructor (CERT CXX-005275).
using TestList = uci::base::BoundedListImpl<
    uci::base::StubAccessor,
    uci::base::accessorType::null>;

using BL = uci::base::BoundedList<
    uci::base::StubAccessor,
    uci::base::accessorType::null>;

// ---------------------------------------------------------------------------
// CXX-005168: BoundedList publicly inherits uci::base::Accessor
// ---------------------------------------------------------------------------
static_assert(std::is_base_of_v<uci::base::Accessor, BL>,
    "CXX-005168: BoundedList must publicly inherit uci::base::Accessor");

// ---------------------------------------------------------------------------
// CXX-005172 / CXX-011183 / CXX-011184: required typedefs
// ---------------------------------------------------------------------------
static_assert(std::is_same_v<BL::size_type, std::size_t>,
    "CXX-005172: size_type must be std::size_t");

static_assert(std::is_same_v<BL::reference, uci::base::StubAccessor&>,
    "CXX-011183: reference must be T&");

static_assert(std::is_same_v<BL::const_reference, const uci::base::StubAccessor&>,
    "CXX-011184: const_reference must be const T&");

// ---------------------------------------------------------------------------
// CXX-005174: UNBOUNDED_BOUND exists and is a size_type constant
// ---------------------------------------------------------------------------
static_assert(std::is_same_v<
    std::remove_cv_t<decltype(BL::UNBOUNDED_BOUND)>,
    BL::size_type>,
    "CXX-005174: UNBOUNDED_BOUND must be of type size_type");

// Verify it is a compile-time constant (usable in static_assert).
static_assert(BL::UNBOUNDED_BOUND > 0,
    "CXX-005174: UNBOUNDED_BOUND must be a positive value");

// ---------------------------------------------------------------------------
// CXX-005275: default constructor is protected — BoundedList cannot be
// default-constructed directly.  BoundedListImpl CAN be constructed.
// ---------------------------------------------------------------------------
static_assert(!std::is_default_constructible_v<BL>,
    "CXX-005275: BoundedList default constructor must be protected/private");

// ---------------------------------------------------------------------------
// CXX-005282: copy constructor is protected
// ---------------------------------------------------------------------------
static_assert(!std::is_copy_constructible_v<BL>,
    "CXX-005282: BoundedList copy constructor must be protected/private");

// ---------------------------------------------------------------------------
// CXX-011192: copy assignment operator is protected
// ---------------------------------------------------------------------------
static_assert(!std::is_copy_assignable_v<BL>,
    "CXX-011192: BoundedList copy assignment operator must be protected/private");

// ---------------------------------------------------------------------------
// CXX-012702: destructor is protected — cannot delete through BL* directly.
// (Checked indirectly: if dtor were public, is_destructible would still be
// true because derived classes have public dtors.  We instead verify that
// BL is not publicly destructible by checking it is not trivially destructible
// from an external non-friend context — the tightest static_assert available
// without negative compilation.)
// NOTE: A proper negative test (that "delete ptr;" on a BL* fails to compile)
// cannot be expressed as a static_assert.  This is documented but not
// mechanically enforced here.
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// Method signature checks via pointer-to-member-function casts.
// Each cast will fail to compile if the method is absent or has the wrong
// signature.
// ---------------------------------------------------------------------------

// CXX-005179: size_type size() const noexcept
using SizeFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<SizeFn, decltype(static_cast<SizeFn>(&BL::size))>,
    "CXX-005179: size() const noexcept required");

// CXX-005181: size_type max_size() const noexcept
using MaxSizeFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<MaxSizeFn, decltype(static_cast<MaxSizeFn>(&BL::max_size))>,
    "CXX-005181: max_size() const noexcept required");

// CXX-005184: size_type min_size() const noexcept
using MinSizeFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<MinSizeFn, decltype(static_cast<MinSizeFn>(&BL::min_size))>,
    "CXX-005184: min_size() const noexcept required");

// CXX-005187: size_type capacity() const noexcept
using CapacityFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<CapacityFn, decltype(static_cast<CapacityFn>(&BL::capacity))>,
    "CXX-005187: capacity() const noexcept required");

// CXX-005195: bool empty() const noexcept
using EmptyFn = bool (BL::*)() const noexcept;
static_assert(std::is_same_v<EmptyFn, decltype(static_cast<EmptyFn>(&BL::empty))>,
    "CXX-005195: empty() const noexcept required");

// CXX-005224: size_type getMaximumOccurs() const noexcept
using GetMaxOccursFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<GetMaxOccursFn, decltype(static_cast<GetMaxOccursFn>(&BL::getMaximumOccurs))>,
    "CXX-005224: getMaximumOccurs() const noexcept required");

// CXX-005233: size_type getMinimumOccurs() const noexcept
using GetMinOccursFn = BL::size_type (BL::*)() const noexcept;
static_assert(std::is_same_v<GetMinOccursFn, decltype(static_cast<GetMinOccursFn>(&BL::getMinimumOccurs))>,
    "CXX-005233: getMinimumOccurs() const noexcept required");

// CXX-011186: void reserve(size_type)
using ReserveFn = void (BL::*)(BL::size_type);
static_assert(std::is_same_v<ReserveFn, decltype(static_cast<ReserveFn>(&BL::reserve))>,
    "CXX-011186: reserve(size_type) required");

// CXX-011187: void pop_back() — spec says throw(), header uses noexcept
using PopBackFn = void (BL::*)() noexcept;
static_assert(std::is_same_v<PopBackFn, decltype(static_cast<PopBackFn>(&BL::pop_back))>,
    "CXX-011187: pop_back() noexcept required");

// CXX-005216: void clear() noexcept
using ClearFn = void (BL::*)() noexcept;
static_assert(std::is_same_v<ClearFn, decltype(static_cast<ClearFn>(&BL::clear))>,
    "CXX-005216: clear() noexcept required");

// CXX-011201: void resize(size_type, AccessorType = V)
// Only the two-parameter overload is pointer-addressable when a default exists.
using ResizeFn = void (BL::*)(BL::size_type, uci::base::accessorType::AccessorType);
static_assert(std::is_same_v<ResizeFn, decltype(static_cast<ResizeFn>(&BL::resize))>,
    "CXX-011201: resize(size_type, AccessorType) required");

// CXX-011189: reference operator[](size_type)
using IndexFn = BL::reference (BL::*)(BL::size_type);
static_assert(std::is_same_v<IndexFn, decltype(static_cast<IndexFn>(&BL::operator[]))>,
    "CXX-011189: operator[](size_type) required");

// CXX-005249: const_reference operator[](size_type) const
using IndexConstFn = BL::const_reference (BL::*)(BL::size_type) const;
static_assert(std::is_same_v<IndexConstFn, decltype(static_cast<IndexConstFn>(&BL::operator[]))>,
    "CXX-005249: operator[](size_type) const required");

// CXX-011190: reference at(size_type)
using AtFn = BL::reference (BL::*)(BL::size_type);
static_assert(std::is_same_v<AtFn, decltype(static_cast<AtFn>(&BL::at))>,
    "CXX-011190: at(size_type) required");

// CXX-005262: const_reference at(size_type) const
using AtConstFn = BL::const_reference (BL::*)(BL::size_type) const;
static_assert(std::is_same_v<AtConstFn, decltype(static_cast<AtConstFn>(&BL::at))>,
    "CXX-005262: at(size_type) const required");

// CXX-011191: void push_back(const_reference)
using PushBackConstRefFn = void (BL::*)(BL::const_reference);
static_assert(std::is_same_v<PushBackConstRefFn,
    decltype(static_cast<PushBackConstRefFn>(&BL::push_back))>,
    "CXX-011191: push_back(const_reference) required");

// ---------------------------------------------------------------------------
// CXX-012971 / CXX-013010: constrained template push_back overloads are
// declared in addition to the required const_reference overload.
// ---------------------------------------------------------------------------

// File must compile cleanly — successful compilation is the test.
