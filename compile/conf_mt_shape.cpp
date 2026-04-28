// Compile-only conformance: nested Listener/Reader/Writer classes inside *MT headers.

#include "uci/type/PositionReportMT.h"
#include "uci/type/ServiceStatusMT.h"
#include "uci/type/SubsystemStatusMT.h"
#include "uci/type/SystemStatusMT.h"

#include <type_traits>

template <typename Msg>
struct MtShapeChecks {
    using L = typename Msg::Listener;
    using R = typename Msg::Reader;
    using W = typename Msg::Writer;

    static_assert(!std::is_default_constructible_v<L>);
    static_assert(!std::is_default_constructible_v<R>);
    static_assert(!std::is_default_constructible_v<W>);
    static_assert(!std::is_copy_constructible_v<L>);
    static_assert(!std::is_copy_constructible_v<R>);
    static_assert(!std::is_copy_constructible_v<W>);
    static_assert(!std::is_copy_assignable_v<L>);
    static_assert(!std::is_copy_assignable_v<R>);
    static_assert(!std::is_copy_assignable_v<W>);
    static_assert(!std::is_destructible_v<R>);
    static_assert(!std::is_destructible_v<W>);
    static_assert(std::is_destructible_v<L>);
    static_assert(!std::is_destructible_v<Msg>);
};

template struct MtShapeChecks<uci::type::ServiceStatusMT>;
template struct MtShapeChecks<uci::type::SystemStatusMT>;
template struct MtShapeChecks<uci::type::SubsystemStatusMT>;
template struct MtShapeChecks<uci::type::PositionReportMT>;
