// Compile-only conformance: xs:choice accessor API (OMSC-SPC-008 RevK §"The Choice Accessor")
// Lines 12543–12895 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md
// CERT IDs covered: CXX-007137, CXX-007138, CXX-011109, CXX-011110, CXX-012695, CXX-012696
//
// ALL 420 choice-type headers in include/uci/type/ are affected.
//
// Resolved in ARCAL conformance plan:
//   - TASK-009 choice accessor naming (implemented)

#include "uci/type/StoreCommandType.h"
#include "uci/type/EA_TargetPointingType.h"
#include "uci/base/Accessor.h"

#include <type_traits>

namespace {

// CXX-011135 (inherited): choice types must derive from uci::base::Accessor
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::StoreCommandType>,
    "StoreCommandType must inherit from uci::base::Accessor");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::EA_TargetPointingType>,
    "EA_TargetPointingType must inherit from uci::base::Accessor");

// CXX-007137: sentinel must be named <TYPENAME>_CHOICE_NONE with value 0
static_assert(
    uci::type::StoreCommandType::STORECOMMANDTYPE_CHOICE_NONE == 0,
    "CXX-007137: STORECOMMANDTYPE_CHOICE_NONE must equal 0");
static_assert(
    uci::type::EA_TargetPointingType::EA_TARGETPOINTINGTYPE_CHOICE_NONE == 0,
    "CXX-007137: EA_TARGETPOINTINGTYPE_CHOICE_NONE must equal 0");

// CXX-007138: each element enumerator has value > 0
static_assert(
    uci::type::StoreCommandType::STORECOMMANDTYPE_CHOICE_NEXTSTORESTATION > 0,
    "CXX-007138: STORECOMMANDTYPE_CHOICE_NEXTSTORESTATION must be > 0");
static_assert(
    uci::type::EA_TargetPointingType::EA_TARGETPOINTINGTYPE_CHOICE_LOCATIONDATA > 0,
    "CXX-007138: EA_TARGETPOINTINGTYPE_CHOICE_LOCATIONDATA must be > 0");

// CXX-011109: get<TypeName>ChoiceOrdinal() const must return <TypeName>Choice
static_assert(std::is_same_v<
    uci::type::StoreCommandType::StoreCommandTypeChoice,
    decltype(std::declval<const uci::type::StoreCommandType>().getStoreCommandTypeChoiceOrdinal())>,
    "CXX-011109: getStoreCommandTypeChoiceOrdinal() must return StoreCommandTypeChoice");

static_assert(std::is_same_v<
    uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoice,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().getEA_TargetPointingTypeChoiceOrdinal())>,
    "CXX-011109: getEA_TargetPointingTypeChoiceOrdinal() must return EA_TargetPointingTypeChoice");

// CXX-011110: set<TypeName>ChoiceOrdinal must exist with correct signature
static_assert(std::is_same_v<
    uci::type::StoreCommandType&,
    decltype(std::declval<uci::type::StoreCommandType>().setStoreCommandTypeChoiceOrdinal(
        uci::type::StoreCommandType::STORECOMMANDTYPE_CHOICE_NONE))>,
    "CXX-011110: setStoreCommandTypeChoiceOrdinal must return StoreCommandType&");

static_assert(std::is_same_v<
    uci::type::EA_TargetPointingType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().setEA_TargetPointingTypeChoiceOrdinal(
        uci::type::EA_TargetPointingType::EA_TARGETPOINTINGTYPE_CHOICE_NONE))>,
    "CXX-011110: setEA_TargetPointingTypeChoiceOrdinal must return EA_TargetPointingType&");

// CXX-012695: is<ElementName>() const bool must exist for every element
static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::StoreCommandType>().isNextStoreStation())>,
    "CXX-012695: isNextStoreStation() const bool must exist");

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::StoreCommandType>().isReleaseConsent())>,
    "CXX-012695: isReleaseConsent() const bool must exist");

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::StoreCommandType>().isVerifyInventory())>,
    "CXX-012695: isVerifyInventory() const bool must exist");

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().isLocationData())>,
    "CXX-012695: isLocationData() const bool must exist");

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().isAirVolume())>,
    "CXX-012695: isAirVolume() const bool must exist");

// CXX-012696: choose<ElementName>() for complex types must accept optional AccessorType
static_assert(std::is_same_v<
    uci::type::ForeignKeyType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseNextStoreStation(
        uci::base::accessorType::null))>,
    "CXX-012696: chooseNextStoreStation(AccessorType) must compile");

static_assert(std::is_same_v<
    uci::type::ReleaseConsentType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseReleaseConsent(
        uci::base::accessorType::null))>,
    "CXX-012696: chooseReleaseConsent(AccessorType) must compile");

static_assert(std::is_same_v<
    uci::type::EmptyType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseVerifyInventory())>,
    "CXX-012696: chooseVerifyInventory() must compile for simple-restriction choice elements");

static_assert(std::is_same_v<
    uci::type::TargetType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().chooseLocationData(
        uci::base::accessorType::null))>,
    "CXX-012696: chooseLocationData(AccessorType) must compile");

static_assert(std::is_same_v<
    uci::type::AirVolumeSensorReferencedType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().chooseAirVolume(
        uci::base::accessorType::null))>,
    "CXX-012696: chooseAirVolume(AccessorType) must compile");

// const get<ElementName>() must also exist
static_assert(std::is_same_v<
    const uci::type::ForeignKeyType&,
    decltype(std::declval<const uci::type::StoreCommandType>().getNextStoreStation())>,
    "CXX-012696: getNextStoreStation() const must return const ForeignKeyType&");

static_assert(std::is_same_v<
    const uci::type::TargetType&,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().getLocationData())>,
    "CXX-012696: getLocationData() const must return const TargetType&");

} // namespace
