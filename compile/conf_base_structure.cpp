// Compile-only conformance: Accessor Instance Definitions.

#include "uci/base/Accessor.h"
#include "uci/type/HeaderType.h"
#include "uci/type/ID_Type.h"
#include "uci/type/MessageType.h"
#include "uci/type/PositionReportMDT.h"
#include "uci/type/ServiceID_Type.h"
#include "uci/type/ServiceStatusMT.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/SubsystemStatusMT.h"
#include "uci/type/SystemID_Type.h"
#include "uci/type/SystemStatusMDT.h"
#include "uci/type/SystemStatusMT.h"

#include <type_traits>

namespace {

static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ID_Type>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::MessageType>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::HeaderType>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::SystemStatusMDT>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::PositionReportMDT>);

static_assert(std::is_base_of_v<uci::type::ID_Type, uci::type::ServiceID_Type>);
static_assert(std::is_base_of_v<uci::type::ID_Type, uci::type::SystemID_Type>);
static_assert(std::is_base_of_v<uci::type::ID_Type, uci::type::SubsystemID_Type>);

static_assert(std::is_base_of_v<uci::type::MessageType, uci::type::ServiceStatusMT>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ServiceStatusMT>);
static_assert(std::is_base_of_v<uci::type::MessageType, uci::type::SystemStatusMT>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::SystemStatusMT>);
static_assert(std::is_base_of_v<uci::type::MessageType, uci::type::SubsystemStatusMT>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::SubsystemStatusMT>);

} // namespace
