// Compile-only conformance: generated accessor factory methods.

#include "uci/base/AbstractServiceBusConnection.h"
#include "uci/type/CovarianceMatrixType.h"
#include "uci/type/ID_Type.h"
#include "uci/type/PositionReportMDT.h"
#include "uci/type/ServiceID_Type.h"
#include "uci/type/ServiceStatusMT.h"
#include "uci/type/SubsystemStatusMDT.h"
#include "uci/type/SystemStatusMDT.h"

#include <string>
#include <type_traits>

namespace {

template <typename T>
struct AccessorFactoryChecks {
    using CopyFn = void (T::*)(const T&);
    static_assert(std::is_same_v<CopyFn, decltype(static_cast<CopyFn>(&T::copy))>);
    static_assert(!std::is_assignable_v<T&, const T&>);

    using CreateFn = T& (*)(uci::base::AbstractServiceBusConnection*);
    using CopyCreateFn = T& (*)(const T&, uci::base::AbstractServiceBusConnection*);
    using DestroyFn = void (*)(T&);

    static_assert(std::is_same_v<CreateFn, decltype(static_cast<CreateFn>(&T::create))>);
    static_assert(std::is_same_v<CopyCreateFn, decltype(static_cast<CopyCreateFn>(&T::create))>);
    static_assert(std::is_same_v<DestroyFn, decltype(static_cast<DestroyFn>(&T::destroy))>);
    static_assert(std::is_same_v<std::string, decltype(T::getUCITypeVersion())>);
};

template struct AccessorFactoryChecks<uci::type::ID_Type>;
template struct AccessorFactoryChecks<uci::type::ServiceID_Type>;
template struct AccessorFactoryChecks<uci::type::ServiceStatusMT>;
template struct AccessorFactoryChecks<uci::type::SystemStatusMDT>;
template struct AccessorFactoryChecks<uci::type::SubsystemStatusMDT>;
template struct AccessorFactoryChecks<uci::type::PositionReportMDT>;
template struct AccessorFactoryChecks<uci::type::CovarianceMatrixType>;

void canary_default_arg_support() {
    auto& obj = uci::type::ID_Type::create();
    auto& copy = uci::type::ID_Type::create(obj);
    uci::type::ID_Type::destroy(copy);
    uci::type::ID_Type::destroy(obj);
}

} // namespace
