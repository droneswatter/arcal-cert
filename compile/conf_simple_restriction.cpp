// Compile-only conformance: xs:simpleType xs:restriction typedef shape.

#include "uci/base/PrimitiveAccessors.h"
#include "uci/type/AngleType.h"
#include "uci/type/DateTimeType.h"
#include "uci/type/DurationType.h"
#include "uci/type/PriorityRankType.h"
#include "uci/type/VisibleString256Type.h"
#include "uci/type/VisibleString32Type.h"
#include "xs/accessorType.h"

#include <type_traits>

static_assert(std::is_same_v<uci::type::AngleType, uci::base::DoubleAccessor>);
static_assert(std::is_same_v<uci::type::AngleTypeValue, xs::Double>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::AngleType>);
static_assert(std::is_same_v<decltype(std::declval<const uci::type::AngleType&>().getValue()), const double&>);
static_assert(std::is_same_v<decltype(std::declval<uci::type::AngleType&>().getValue()), double&>);
static_assert(std::is_same_v<decltype(std::declval<uci::type::AngleType&>().setValue(1.0)), void>);

static_assert(std::is_same_v<uci::type::PriorityRankType, uci::base::UnsignedShortAccessor>);
static_assert(std::is_same_v<uci::type::PriorityRankTypeValue, xs::UnsignedShort>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::PriorityRankType>);
static_assert(std::is_same_v<decltype(std::declval<const uci::type::PriorityRankType&>().getValue()), const uint16_t&>);
static_assert(std::is_same_v<decltype(std::declval<uci::type::PriorityRankType&>().setValue(uint16_t{1})), void>);

static_assert(std::is_same_v<uci::type::VisibleString256Type, xs::String>);
static_assert(std::is_same_v<uci::type::VisibleString32Type, xs::String>);
static_assert(std::is_same_v<uci::type::DurationType, xs::Duration>);
static_assert(std::is_same_v<uci::type::DateTimeType, xs::DateTime>);
