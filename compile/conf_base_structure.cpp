// Compile-only conformance: Accessor Instance Definitions
// OMSC-SPC-008 RevK §"Accessor Instance Definitions" (approx. lines 8832–8966)
// CERT IDs covered: CXX-005456, CXX-011135
//
// These checks verify the inheritance relationships required by the spec:
//   CXX-011135 — types with no XSD extension base must inherit from uci::base::Accessor
//   CXX-005456 — types with an XSD extension base must inherit from their translated base type
//                (which itself ultimately derives from uci::base::Accessor)
//
// Note: constructor/destructor access (CXX-012705, CXX-005464, CXX-005465, CXX-011064)
// is already covered by conf_generated_lifecycle_target.cpp.

#include "uci/base/Accessor.h"
#include "uci/type/ID_Type.h"
#include "uci/type/MessageType.h"
#include "uci/type/HeaderType.h"
#include "uci/type/SecurityInformationType.h"
#include "uci/type/AMTI_ActivityMDT.h"
#include "uci/type/TransceiverType.h"
#include "uci/type/SubsystemID_Type.h"
#include "uci/type/FileMetadataID_Type.h"
#include "uci/type/ACO_TraceabilityType.h"
#include "uci/type/ACO_FileTraceabilityType.h"
#include "uci/type/ActionCommandMT.h"
#include "uci/type/AMTI_ActivityMT.h"

#include <type_traits>

namespace {

// ---------------------------------------------------------------------------
// CXX-011135: types without an XSD extension base → must derive from
// uci::base::Accessor (directly or transitively).
// ---------------------------------------------------------------------------

// ID_Type: xs:complexType with no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ID_Type>,
    "CXX-011135: ID_Type must inherit from uci::base::Accessor");

// MessageType: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::MessageType>,
    "CXX-011135: MessageType must inherit from uci::base::Accessor");

// HeaderType: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::HeaderType>,
    "CXX-011135: HeaderType must inherit from uci::base::Accessor");

// SecurityInformationType: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::SecurityInformationType>,
    "CXX-011135: SecurityInformationType must inherit from uci::base::Accessor");

// AMTI_ActivityMDT: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::AMTI_ActivityMDT>,
    "CXX-011135: AMTI_ActivityMDT must inherit from uci::base::Accessor");

// TransceiverType: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::TransceiverType>,
    "CXX-011135: TransceiverType must inherit from uci::base::Accessor");

// ACO_TraceabilityType: complex type, no extension base
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ACO_TraceabilityType>,
    "CXX-011135: ACO_TraceabilityType must inherit from uci::base::Accessor");

// ---------------------------------------------------------------------------
// CXX-005456: types WITH an XSD extension base → must derive from the
// translated base type (which is itself an Accessor subtype).
// The immediate base is checked first; transitive Accessor derivation follows.
// ---------------------------------------------------------------------------

// SubsystemID_Type extends ID_Type
static_assert(std::is_base_of_v<uci::type::ID_Type, uci::type::SubsystemID_Type>,
    "CXX-005456: SubsystemID_Type must inherit from ID_Type");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::SubsystemID_Type>,
    "CXX-005456: SubsystemID_Type must transitively inherit from uci::base::Accessor");

// FileMetadataID_Type extends ID_Type
static_assert(std::is_base_of_v<uci::type::ID_Type, uci::type::FileMetadataID_Type>,
    "CXX-005456: FileMetadataID_Type must inherit from ID_Type");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::FileMetadataID_Type>,
    "CXX-005456: FileMetadataID_Type must transitively inherit from uci::base::Accessor");

// ACO_FileTraceabilityType extends ACO_TraceabilityType
static_assert(std::is_base_of_v<uci::type::ACO_TraceabilityType, uci::type::ACO_FileTraceabilityType>,
    "CXX-005456: ACO_FileTraceabilityType must inherit from ACO_TraceabilityType");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ACO_FileTraceabilityType>,
    "CXX-005456: ACO_FileTraceabilityType must transitively inherit from uci::base::Accessor");

// ActionCommandMT extends MessageType (global message type)
static_assert(std::is_base_of_v<uci::type::MessageType, uci::type::ActionCommandMT>,
    "CXX-005456: ActionCommandMT must inherit from MessageType");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::ActionCommandMT>,
    "CXX-005456: ActionCommandMT must transitively inherit from uci::base::Accessor");

// AMTI_ActivityMT extends MessageType (global message type)
static_assert(std::is_base_of_v<uci::type::MessageType, uci::type::AMTI_ActivityMT>,
    "CXX-005456: AMTI_ActivityMT must inherit from MessageType");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::AMTI_ActivityMT>,
    "CXX-005456: AMTI_ActivityMT must transitively inherit from uci::base::Accessor");

} // namespace
