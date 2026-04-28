// Compile-only conformance: xs:simpleType xs:restriction typedef shape.

#include "uci/base/PrimitiveAccessors.h"
#include "uci/type/AngleType.h"
#include "uci/type/DateTimeType.h"
#include "uci/type/DurationType.h"
#include "uci/type/VisibleString256Type.h"
#include "uci/type/VisibleString32Type.h"
#include "xs/accessorType.h"

#include <type_traits>

static_assert(std::is_same_v<uci::type::AngleType, uci::base::DoubleAccessor>);
static_assert(std::is_same_v<uci::type::AngleTypeValue, xs::Double>);

static_assert(std::is_same_v<uci::type::VisibleString256Type, xs::String>);
static_assert(std::is_same_v<uci::type::VisibleString32Type, xs::String>);
static_assert(std::is_same_v<uci::type::DurationType, xs::Duration>);
static_assert(std::is_same_v<uci::type::DateTimeType, xs::DateTime>);
