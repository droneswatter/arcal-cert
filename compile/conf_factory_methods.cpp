// OMSC-SPC-008 RevK §9 Accessor Instance Member Functions / Factory Methods
// CERT IDs covered: CXX-011063, CXX-011064, CXX-011066, CXX-011067,
// CXX-011068, CXX-011410

#include "uci/base/AbstractServiceBusConnection.h"
#include "uci/type/ACTDF_CollectionPlanType.h"
#include "uci/type/AMTI_ActivityMDT.h"
#include "uci/type/ActionCommandMT.h"
#include "uci/type/COMINT_CapabilityStatusMDT.h"
#include "uci/type/CapabilityBaseType.h"
#include "uci/type/CapabilityStatusBaseType.h"
#include "uci/type/ID_Type.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/WeatherRadarActivityMDT.h"

#include <string>
#include <type_traits>

namespace {

template <typename T>
struct ComplexTypeChecks {
    using CopyFn = void (T::*)(const T&);
    static_assert(std::is_same_v<CopyFn, decltype(static_cast<CopyFn>(&T::copy))>);

    static_assert(!std::is_assignable_v<T&, const T&>);

    using CreateFn = T& (*)(uci::base::AbstractServiceBusConnection*);
    static_assert(std::is_same_v<CreateFn, decltype(static_cast<CreateFn>(&T::create))>);

    using CopyCreateFn = T& (*)(const T&, uci::base::AbstractServiceBusConnection*);
    static_assert(std::is_same_v<CopyCreateFn, decltype(static_cast<CopyCreateFn>(&T::create))>);

    using DestroyFn = void (*)(T&);
    static_assert(std::is_same_v<DestroyFn, decltype(static_cast<DestroyFn>(&T::destroy))>);

    static_assert(std::is_same_v<std::string, decltype(T::getUCITypeVersion())>);
};

template struct ComplexTypeChecks<uci::type::ID_Type>;
template struct ComplexTypeChecks<uci::type::ACTDF_CollectionPlanType>;
template struct ComplexTypeChecks<uci::type::SubsystemID_Type>;
template struct ComplexTypeChecks<uci::type::AMTI_ActivityMDT>;
template struct ComplexTypeChecks<uci::type::COMINT_CapabilityStatusMDT>;
template struct ComplexTypeChecks<uci::type::WeatherRadarActivityMDT>;
template struct ComplexTypeChecks<uci::type::ActionCommandMT>;

namespace abstract_checks {
using ABT = uci::type::CapabilityBaseType;
using CopyFn = void (ABT::*)(const ABT&);
static_assert(std::is_same_v<CopyFn, decltype(static_cast<CopyFn>(&ABT::copy))>);
static_assert(std::is_same_v<std::string, decltype(ABT::getUCITypeVersion())>);

using CSB = uci::type::CapabilityStatusBaseType;
using CopyFn2 = void (CSB::*)(const CSB&);
static_assert(std::is_same_v<CopyFn2, decltype(static_cast<CopyFn2>(&CSB::copy))>);
static_assert(std::is_same_v<std::string, decltype(CSB::getUCITypeVersion())>);
} // namespace abstract_checks

// Default-argument canary for CXX-011066 / CXX-011067.
void canary_default_arg_support() {
    auto& obj = uci::type::ID_Type::create();
    auto& copy = uci::type::ID_Type::create(obj);
    uci::type::ID_Type::destroy(copy);
    uci::type::ID_Type::destroy(obj);
}

} // anonymous namespace
