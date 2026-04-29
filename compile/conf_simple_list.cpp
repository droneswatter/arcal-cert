// Compile-only conformance: SimpleList template shape.
// OMSC-SPC-008 RevK §9.5 (lines 3623–4495)
//
// CERTs exercised:
//   CXX-005049  — class SimpleList<class T, AccessorType V> in uci::base, inherits Accessor
//   CXX-005054  — size_type = std::size_t
//   CXX-011156  — reference = T&
//   CXX-011157  — const_reference = const T&
//   CXX-005056  — static const size_type MAXIMUM_LENGTH
//   CXX-012701  — destructor is protected (not publicly callable)
//   CXX-005152  — default constructor is protected (not publicly callable)
//   CXX-005159  — copy constructor is protected (not publicly callable)
//   CXX-011180  — copy-assignment operator is protected (not publicly callable)
//   CXX-005061  — size_type size() const noexcept
//   CXX-005063  — size_type max_size() const noexcept
//   CXX-005066  — size_type min_size() const noexcept
//   CXX-011200  — void resize(size_type, AccessorType = V)
//   CXX-005068  — size_type capacity() const noexcept
//   CXX-005070  — bool empty() const noexcept
//   CXX-011159  — void reserve(size_type)
//   CXX-011160  — void pop_back() noexcept
//   CXX-005084  — void clear() noexcept
//   CXX-005091  — size_type getMaximumLength() const noexcept
//   CXX-005100  — size_type getMinimumLength() const noexcept
//   CXX-005109  — size_type getLength() const noexcept
//   CXX-011163  — reference operator[](size_type)
//   CXX-005125  — const_reference operator[](size_type) const
//   CXX-011178  — reference at(size_type)
//   CXX-005139  — const_reference at(size_type) const
//   CXX-011179  — void push_back(const_reference)

#include "uci/base/SimpleList.h"
#include "uci/base/SimpleListImpl.h"
#include "uci/base/Accessor.h"
#include "uci/base/accessorType.h"

#include <cstddef>
#include <type_traits>

// Use DoubleAccessor (defined in PrimitiveAccessors.h) as a concrete element type.
#include "uci/base/PrimitiveAccessors.h"

namespace {

using ElemT = uci::base::DoubleAccessor;
static constexpr uci::base::accessorType::AccessorType kV =
    uci::base::accessorType::doubleAccessor;

using SL  = uci::base::SimpleList<ElemT, kV>;
using SLI = uci::base::SimpleListImpl<ElemT, kV>;

// ── CXX-005049 ─────────────────────────────────────────────────────────────
// SimpleList<T,V> must be in uci::base and inherit from uci::base::Accessor.
static_assert(std::is_base_of_v<uci::base::Accessor, SL>,
    "CXX-005049: SimpleList must inherit from uci::base::Accessor");

// ── CXX-005054 ─────────────────────────────────────────────────────────────
// size_type must equal std::size_t.
static_assert(std::is_same_v<SL::size_type, std::size_t>,
    "CXX-005054: size_type must be std::size_t");

// ── CXX-011156 ─────────────────────────────────────────────────────────────
// reference must be T&.
static_assert(std::is_same_v<SL::reference, ElemT&>,
    "CXX-011156: reference must be T&");

// ── CXX-011157 ─────────────────────────────────────────────────────────────
// const_reference must be const T&.
static_assert(std::is_same_v<SL::const_reference, const ElemT&>,
    "CXX-011157: const_reference must be const T&");

// ── CXX-005056 ─────────────────────────────────────────────────────────────
// MAXIMUM_LENGTH must be a public static const size_type.
static_assert(std::is_same_v<
    std::remove_cv_t<decltype(SL::MAXIMUM_LENGTH)>,
    SL::size_type>,
    "CXX-005056: MAXIMUM_LENGTH must be size_type");

// ── CXX-012701 / CXX-005152 / CXX-005159 / CXX-011180 ────────────────────
// Destructor, default ctor, copy ctor, copy-assignment must be protected
// (not publicly constructible/destructible from outside the class hierarchy).
static_assert(!std::is_default_constructible_v<SL>,
    "CXX-005152: default constructor of SimpleList must be protected");
static_assert(!std::is_copy_constructible_v<SL>,
    "CXX-005159: copy constructor of SimpleList must be protected");
static_assert(!std::is_copy_assignable_v<SL>,
    "CXX-011180: copy-assignment operator of SimpleList must be protected");
static_assert(!std::is_destructible_v<SL>,
    "CXX-012701: destructor of SimpleList must be protected");

// ── Method signatures (exercised via member-pointer type matching) ──────────

// CXX-005061: size_type size() const noexcept
using SizeFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<SizeFn, decltype(static_cast<SizeFn>(&SL::size))>,
    "CXX-005061: size() const noexcept signature mismatch");

// CXX-005063: size_type max_size() const noexcept
using MaxSizeFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<MaxSizeFn, decltype(static_cast<MaxSizeFn>(&SL::max_size))>,
    "CXX-005063: max_size() const noexcept signature mismatch");

// CXX-005066: size_type min_size() const noexcept
using MinSizeFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<MinSizeFn, decltype(static_cast<MinSizeFn>(&SL::min_size))>,
    "CXX-005066: min_size() const noexcept signature mismatch");

// CXX-005068: size_type capacity() const noexcept
using CapacityFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<CapacityFn, decltype(static_cast<CapacityFn>(&SL::capacity))>,
    "CXX-005068: capacity() const noexcept signature mismatch");

// CXX-005070: bool empty() const noexcept
using EmptyFn = bool (SL::*)() const noexcept;
static_assert(std::is_same_v<EmptyFn, decltype(static_cast<EmptyFn>(&SL::empty))>,
    "CXX-005070: empty() const noexcept signature mismatch");

// CXX-005084: void clear() noexcept
using ClearFn = void (SL::*)() noexcept;
static_assert(std::is_same_v<ClearFn, decltype(static_cast<ClearFn>(&SL::clear))>,
    "CXX-005084: clear() noexcept signature mismatch");

// CXX-011160: void pop_back() noexcept
using PopBackFn = void (SL::*)() noexcept;
static_assert(std::is_same_v<PopBackFn, decltype(static_cast<PopBackFn>(&SL::pop_back))>,
    "CXX-011160: pop_back() noexcept signature mismatch");

// CXX-011159: void reserve(size_type)
using ReserveFn = void (SL::*)(SL::size_type);
static_assert(std::is_same_v<ReserveFn, decltype(static_cast<ReserveFn>(&SL::reserve))>,
    "CXX-011159: reserve(size_type) signature mismatch");

// CXX-011200: void resize(size_type, AccessorType = V)
using ResizeFn = void (SL::*)(SL::size_type, uci::base::accessorType::AccessorType);
static_assert(std::is_same_v<ResizeFn, decltype(static_cast<ResizeFn>(&SL::resize))>,
    "CXX-011200: resize(size_type, AccessorType) signature mismatch");

// CXX-011179: void push_back(const_reference)
using PushBackFn = void (SL::*)(SL::const_reference);
static_assert(std::is_same_v<PushBackFn, decltype(static_cast<PushBackFn>(&SL::push_back))>,
    "CXX-011179: push_back(const_reference) signature mismatch");

// CXX-011163: reference operator[](size_type)
using IndexFn = SL::reference (SL::*)(SL::size_type);
static_assert(std::is_same_v<IndexFn, decltype(static_cast<IndexFn>(&SL::operator[]))>,
    "CXX-011163: operator[](size_type) signature mismatch");

// CXX-005125: const_reference operator[](size_type) const
using ConstIndexFn = SL::const_reference (SL::*)(SL::size_type) const;
static_assert(std::is_same_v<ConstIndexFn, decltype(static_cast<ConstIndexFn>(&SL::operator[]))>,
    "CXX-005125: operator[](size_type) const signature mismatch");

// CXX-011178: reference at(size_type)
using AtFn = SL::reference (SL::*)(SL::size_type);
static_assert(std::is_same_v<AtFn, decltype(static_cast<AtFn>(&SL::at))>,
    "CXX-011178: at(size_type) signature mismatch");

// CXX-005139: const_reference at(size_type) const
using ConstAtFn = SL::const_reference (SL::*)(SL::size_type) const;
static_assert(std::is_same_v<ConstAtFn, decltype(static_cast<ConstAtFn>(&SL::at))>,
    "CXX-005139: at(size_type) const signature mismatch");

// CXX-005091: size_type getMaximumLength() const noexcept
using GetMaxLenFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<GetMaxLenFn, decltype(static_cast<GetMaxLenFn>(&SL::getMaximumLength))>,
    "CXX-005091: getMaximumLength() const noexcept signature mismatch");

// CXX-005100: size_type getMinimumLength() const noexcept
using GetMinLenFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<GetMinLenFn, decltype(static_cast<GetMinLenFn>(&SL::getMinimumLength))>,
    "CXX-005100: getMinimumLength() const noexcept signature mismatch");

// CXX-005109: size_type getLength() const noexcept
using GetLenFn = SL::size_type (SL::*)() const noexcept;
static_assert(std::is_same_v<GetLenFn, decltype(static_cast<GetLenFn>(&SL::getLength))>,
    "CXX-005109: getLength() const noexcept signature mismatch");

} // namespace
