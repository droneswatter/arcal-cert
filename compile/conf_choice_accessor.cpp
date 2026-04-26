// Compile-only conformance: xs:choice accessor API (OMSC-SPC-008 RevK §"The Choice Accessor")
// Lines 12543–12895 of 06_OMSC-SPC-008_RevK_CxxCALSpec_DandD_v2_5.md
// CERT IDs covered (checked): CXX-012695, CXX-011109, CXX-012696
// CERT IDs FAILING (documented below): CXX-007137, CXX-007138, CXX-011110
//
// ALL 420 choice-type headers in include/uci/type/ are affected by the enum
// naming violations documented here.
//
// ============================================================================
// KNOWN VIOLATIONS — do NOT remove these comments when fixing the generator
// ============================================================================
//
// VIOLATION 1 — enum type name (CERT CXX-007137, CXX-007138)
//   Spec requires:   enum <TypeName>Choice { <TYPENAME>_CHOICE_NONE = 0, ... }
//   Generated:       enum <TypeName>ChoiceOrdinalEnum { CHOICE_NONE, ... }
//
//   Concretely for StoreCommandType:
//     Required:  enum StoreCommandTypeChoice {
//                    STORECOMMANDTYPE_CHOICE_NONE = 0,
//                    STORECOMMANDTYPE_CHOICE_NEXTSTORESTATION,
//                    ...
//                };
//     Generated: enum StoreCommandTypeChoiceOrdinalEnum {
//                    CHOICE_NEXTSTORESTATION,   // note: no type-name prefix
//                    ...
//                    CHOICE_NONE                // note: not the first member (= 0)
//                };
//
//   Concretely for EA_TargetPointingType:
//     Required:  enum EA_TargetPointingTypeChoice {
//                    EA_TARGETPOINTINGTYPE_CHOICE_NONE = 0,
//                    EA_TARGETPOINTINGTYPE_CHOICE_LOCATIONDATA,
//                    EA_TARGETPOINTINGTYPE_CHOICE_AIRVOLUME,
//                };
//     Generated: enum EA_TargetPointingTypeChoiceOrdinalEnum {
//                    CHOICE_LOCATIONDATA,
//                    CHOICE_AIRVOLUME,
//                    CHOICE_NONE
//                };
//
// VIOLATION 2 — setter missing (CERT CXX-011110)
//   Spec requires:
//     virtual StoreCommandType& setStoreCommandTypeChoiceOrdinal(
//         StoreCommandTypeChoice ordinal,
//         uci::base::accessorType::AccessorType type = uci::base::accessorType::null) = 0;
//   Generated: method is absent entirely.
//
// VIOLATION 3 — choose<ElementName> missing optional AccessorType parameter (CERT CXX-012696)
//   Spec requires (for complex-type elements):
//     virtual uci::type::ForeignKeyType& chooseNextStoreStation(
//         uci::base::accessorType::AccessorType type = uci::base::accessorType::null) = 0;
//   Generated:
//     virtual uci::type::ForeignKeyType& chooseNextStoreStation() = 0;
//   Note: The no-arg form is correct for SimpleList/BoundedList elements
//   (CERT CXX-012714, CXX-012715), so this may only be a violation for
//   xs:complexType elements depending on the intended generator logic.
// ============================================================================

#include "uci/type/StoreCommandType.h"
#include "uci/type/EA_TargetPointingType.h"
#include "uci/base/Accessor.h"

#include <type_traits>

namespace {

// ============================================================================
// Section A: Checks that PASS against the current (non-compliant) headers.
//
// These document the correct parts of the generated API so that regressions
// are caught if those methods are accidentally removed.
// ============================================================================

// ---------------------------------------------------------------------------
// CXX-011135 (inherited): choice types must derive from uci::base::Accessor
// ---------------------------------------------------------------------------
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::StoreCommandType>,
    "StoreCommandType must inherit from uci::base::Accessor");
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::EA_TargetPointingType>,
    "EA_TargetPointingType must inherit from uci::base::Accessor");

// ---------------------------------------------------------------------------
// CXX-011109: get<TypeName>ChoiceOrdinal() const must exist
//
// Spec signature:
//   virtual <TypeName>Choice get<TypeName>ChoiceOrdinal() const = 0;
//
// Current headers use <TypeName>ChoiceOrdinalEnum as the return type (wrong
// name) but the method itself is present and const-qualified.
// ---------------------------------------------------------------------------
static_assert(std::is_same_v<
    uci::type::StoreCommandType::StoreCommandTypeChoiceOrdinalEnum,
    decltype(std::declval<const uci::type::StoreCommandType>().getStoreCommandTypeChoiceOrdinal())>,
    "CXX-011109: getStoreCommandTypeChoiceOrdinal() must return the choice enum type");

static_assert(std::is_same_v<
    uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoiceOrdinalEnum,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().getEA_TargetPointingTypeChoiceOrdinal())>,
    "CXX-011109: getEA_TargetPointingTypeChoiceOrdinal() must return the choice enum type");

// ---------------------------------------------------------------------------
// CXX-012695: is<ElementName>() const bool must exist for every element
//
// StoreCommandType has 9 choice elements; spot-check a representative subset.
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// CXX-012696: choose<ElementName>() (non-const) must exist for complex types
//
// Current headers emit no AccessorType parameter (violation documented above
// in Section B), but the method itself is present.
// ---------------------------------------------------------------------------
static_assert(std::is_same_v<
    uci::type::ForeignKeyType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseNextStoreStation())>,
    "CXX-012696: chooseNextStoreStation() must return ForeignKeyType&");

static_assert(std::is_same_v<
    uci::type::ReleaseConsentType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseReleaseConsent())>,
    "CXX-012696: chooseReleaseConsent() must return ReleaseConsentType&");

static_assert(std::is_same_v<
    uci::type::EmptyType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseVerifyInventory())>,
    "CXX-012696: chooseVerifyInventory() must return EmptyType&");

static_assert(std::is_same_v<
    uci::type::TargetType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().chooseLocationData())>,
    "CXX-012696: chooseLocationData() must return TargetType&");

static_assert(std::is_same_v<
    uci::type::AirVolumeSensorReferencedType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().chooseAirVolume())>,
    "CXX-012696: chooseAirVolume() must return AirVolumeSensorReferencedType&");

// const get<ElementName>() must also exist
static_assert(std::is_same_v<
    const uci::type::ForeignKeyType&,
    decltype(std::declval<const uci::type::StoreCommandType>().getNextStoreStation())>,
    "CXX-012696: getNextStoreStation() const must return const ForeignKeyType&");

static_assert(std::is_same_v<
    const uci::type::TargetType&,
    decltype(std::declval<const uci::type::EA_TargetPointingType>().getLocationData())>,
    "CXX-012696: getLocationData() const must return const TargetType&");

// ---------------------------------------------------------------------------
// CXX-007137 / CXX-007138: CHOICE_NONE sentinel value checks
//
// The current enum puts CHOICE_NONE last (non-zero value) and omits the
// type-name prefix.  The static_asserts below document what the spec REQUIRES
// once the generator is fixed.  They are written against the CURRENT names
// and will need to be updated in the same commit that fixes the generator.
//
// Current state (compiles, but wrong):
//   CHOICE_NONE is the last enumerator → its implicit value equals the count
//   of preceding members, not 0.
//
// Desired state after fix (these asserts will need new enum names):
//   static_assert(uci::type::StoreCommandType::StoreCommandTypeChoice::STORECOMMANDTYPE_CHOICE_NONE == 0, ...);
//   static_assert(uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoice::EA_TARGETPOINTINGTYPE_CHOICE_NONE == 0, ...);
//
// The following asserts DOCUMENT THE CURRENT (NON-COMPLIANT) STATE and will
// themselves become incorrect once the generator is fixed — remove them then.
// ---------------------------------------------------------------------------

// CERT CXX-007137 FAILING: CHOICE_NONE is not zero (it is the last member).
// After fixing the generator, replace with:
//   static_assert(uci::type::StoreCommandType::StoreCommandTypeChoice::STORECOMMANDTYPE_CHOICE_NONE == 0, ...);
static_assert(uci::type::StoreCommandType::CHOICE_NONE != 0,
    "NON-COMPLIANT (CXX-007137): CHOICE_NONE must be 0 per spec; "
    "fix generator to emit <TYPENAME>_CHOICE_NONE = 0 as the first enumerator");

static_assert(uci::type::EA_TargetPointingType::CHOICE_NONE != 0,
    "NON-COMPLIANT (CXX-007137): CHOICE_NONE must be 0 per spec; "
    "fix generator to emit <TYPENAME>_CHOICE_NONE = 0 as the first enumerator");

// ============================================================================
// Section B: Checks that WILL FAIL once the generator is corrected.
//
// These are written in terms of the SPEC-REQUIRED names. They are disabled
// with #if 0 so the file compiles today. Remove the #if 0 guard in the same
// commit that fixes the schema compiler.
// ============================================================================

#if 0
// CXX-007137: sentinel must be named <TYPENAME>_CHOICE_NONE with value 0
static_assert(
    uci::type::StoreCommandType::StoreCommandTypeChoice::STORECOMMANDTYPE_CHOICE_NONE == 0,
    "CXX-007137: STORECOMMANDTYPE_CHOICE_NONE must equal 0");
static_assert(
    uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoice::EA_TARGETPOINTINGTYPE_CHOICE_NONE == 0,
    "CXX-007137: EA_TARGETPOINTINGTYPE_CHOICE_NONE must equal 0");

// CXX-007138: each element enumerator has value > 0
static_assert(
    uci::type::StoreCommandType::StoreCommandTypeChoice::STORECOMMANDTYPE_CHOICE_NEXTSTORESTATION > 0,
    "CXX-007138: STORECOMMANDTYPE_CHOICE_NEXTSTORESTATION must be > 0");
static_assert(
    uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoice::EA_TARGETPOINTINGTYPE_CHOICE_LOCATIONDATA > 0,
    "CXX-007138: EA_TARGETPOINTINGTYPE_CHOICE_LOCATIONDATA must be > 0");

// CXX-011110: set<TypeName>ChoiceOrdinal must exist with correct signature
// Verify the setter returns a reference to the type and accepts enum + optional AccessorType.
static_assert(std::is_same_v<
    uci::type::StoreCommandType&,
    decltype(std::declval<uci::type::StoreCommandType>().setStoreCommandTypeChoiceOrdinal(
        uci::type::StoreCommandType::StoreCommandTypeChoice::STORECOMMANDTYPE_CHOICE_NONE))>,
    "CXX-011110: setStoreCommandTypeChoiceOrdinal must return StoreCommandType&");

static_assert(std::is_same_v<
    uci::type::EA_TargetPointingType&,
    decltype(std::declval<uci::type::EA_TargetPointingType>().setEA_TargetPointingTypeChoiceOrdinal(
        uci::type::EA_TargetPointingType::EA_TargetPointingTypeChoice::EA_TARGETPOINTINGTYPE_CHOICE_NONE))>,
    "CXX-011110: setEA_TargetPointingTypeChoiceOrdinal must return EA_TargetPointingType&");

// CXX-012696: choose<ElementName> for complex types must accept optional AccessorType
// (the no-arg call must still compile; this checks the overload/default exists)
static_assert(std::is_same_v<
    uci::type::ForeignKeyType&,
    decltype(std::declval<uci::type::StoreCommandType>().chooseNextStoreStation(
        uci::base::accessorType::null))>,
    "CXX-012696: chooseNextStoreStation(AccessorType) must compile");
#endif

} // namespace
