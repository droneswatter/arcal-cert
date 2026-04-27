// Compile-only conformance: xs:simpleType xs:restriction (non-enum) typedef shape
// Spec: OMSC-SPC-008 RevK §"The SimpleRestriction Accessor"
// CERTs covered: CXX-006143, CXX-006144, CXX-006553

#include "uci/base/PrimitiveAccessors.h"
#include "uci/type/AlphanumericDashSpaceUnderscoreStringLength20Type.h"
#include "uci/type/UnitBallDoubleType.h"
#include "uci/type/UnitBallFloatType.h"
#include "uci/type/UnitIntervalDoubleType.h"
#include "uci/type/UnitIntervalFloatType.h"
#include "uci/type/VisibleString256Type.h"
#include "xs/accessorType.h"

#include <type_traits>

static_assert(std::is_same_v<uci::type::UnitBallDoubleType, uci::base::DoubleAccessor>,
    "CXX-006143: UnitBallDoubleType must typedef to uci::base::DoubleAccessor");
static_assert(std::is_same_v<uci::type::UnitIntervalDoubleType, uci::base::DoubleAccessor>,
    "CXX-006143: UnitIntervalDoubleType must typedef to uci::base::DoubleAccessor");
static_assert(std::is_same_v<uci::type::UnitBallFloatType, uci::base::FloatAccessor>,
    "CXX-006143: UnitBallFloatType must typedef to uci::base::FloatAccessor");
static_assert(std::is_same_v<uci::type::UnitIntervalFloatType, uci::base::FloatAccessor>,
    "CXX-006143: UnitIntervalFloatType must typedef to uci::base::FloatAccessor");

static_assert(std::is_same_v<uci::type::UnitBallDoubleTypeValue, xs::Double>,
    "CXX-006144: UnitBallDoubleTypeValue must typedef to xs::Double");
static_assert(std::is_same_v<uci::type::UnitIntervalDoubleTypeValue, xs::Double>,
    "CXX-006144: UnitIntervalDoubleTypeValue must typedef to xs::Double");
static_assert(std::is_same_v<uci::type::UnitBallFloatTypeValue, xs::Float>,
    "CXX-006144: UnitBallFloatTypeValue must typedef to xs::Float");
static_assert(std::is_same_v<uci::type::UnitIntervalFloatTypeValue, xs::Float>,
    "CXX-006144: UnitIntervalFloatTypeValue must typedef to xs::Float");

static_assert(std::is_same_v<uci::type::VisibleString256Type, xs::String>,
    "CXX-006553: VisibleString256Type must typedef to xs::String");
static_assert(std::is_same_v<uci::type::AlphanumericDashSpaceUnderscoreStringLength20Type, xs::String>,
    "CXX-006553: AlphanumericDashSpaceUnderscoreStringLength20Type must typedef to xs::String");
