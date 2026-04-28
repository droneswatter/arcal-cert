// Compile-only conformance: xs:choice accessor API.

#include "uci/base/Accessor.h"
#include "uci/type/ComponentElementIdentifierChoiceType.h"
#include "uci/type/ForeignKeyType.h"
#include "uci/type/NameValuePairValueType.h"
#include "uci/type/NATO_SpecialWordsType.h"
#include "uci/type/OperatorID_Type.h"
#include "uci/type/OperatorReferenceType.h"
#include "uci/type/OwnerProducerChoiceType.h"
#include "uci/type/VisibleString256Type.h"

#include <type_traits>

namespace {

static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::NameValuePairValueType>);
static_assert(std::is_base_of_v<uci::base::Accessor, uci::type::OperatorReferenceType>);

static_assert(uci::type::NameValuePairValueType::NAMEVALUEPAIRVALUETYPE_CHOICE_NONE == 0);
static_assert(uci::type::OperatorReferenceType::OPERATORREFERENCETYPE_CHOICE_NONE == 0);
static_assert(uci::type::NameValuePairValueType::NAMEVALUEPAIRVALUETYPE_CHOICE_DOUBLEVALUE > 0);
static_assert(uci::type::OperatorReferenceType::OPERATORREFERENCETYPE_CHOICE_OPERATORID > 0);

static_assert(std::is_same_v<
    uci::type::NameValuePairValueType::NameValuePairValueTypeChoice,
    decltype(std::declval<const uci::type::NameValuePairValueType>().getNameValuePairValueTypeChoiceOrdinal())>);
static_assert(std::is_same_v<
    uci::type::OperatorReferenceType::OperatorReferenceTypeChoice,
    decltype(std::declval<const uci::type::OperatorReferenceType>().getOperatorReferenceTypeChoiceOrdinal())>);

static_assert(std::is_same_v<
    uci::type::NameValuePairValueType&,
    decltype(std::declval<uci::type::NameValuePairValueType>().setNameValuePairValueTypeChoiceOrdinal(
        uci::type::NameValuePairValueType::NAMEVALUEPAIRVALUETYPE_CHOICE_NONE))>);

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::NameValuePairValueType>().isDoubleValue())>);
static_assert(std::is_same_v<double&,
    decltype(std::declval<uci::type::NameValuePairValueType>().chooseDoubleValue())>);
static_assert(std::is_same_v<const double&,
    decltype(std::declval<const uci::type::NameValuePairValueType>().getDoubleValue())>);

static_assert(std::is_same_v<bool,
    decltype(std::declval<const uci::type::NameValuePairValueType>().isStringValue())>);
static_assert(std::is_same_v<uci::type::VisibleString256Type&,
    decltype(std::declval<uci::type::NameValuePairValueType>().chooseStringValue())>);

static_assert(std::is_same_v<uci::type::OperatorID_Type&,
    decltype(std::declval<uci::type::OperatorReferenceType>().chooseOperatorID(
        uci::base::accessorType::null))>);
static_assert(std::is_same_v<const uci::type::OperatorID_Type&,
    decltype(std::declval<const uci::type::OperatorReferenceType>().getOperatorID())>);

static_assert(std::is_same_v<uint32_t&,
    decltype(std::declval<uci::type::ComponentElementIdentifierChoiceType>()
        .chooseComponentElementNumericIdentifier())>);
static_assert(std::is_same_v<uci::type::ForeignKeyType&,
    decltype(std::declval<uci::type::ComponentElementIdentifierChoiceType>()
        .chooseComponentElementKey(uci::base::accessorType::null))>);

static_assert(std::is_same_v<uci::type::NATO_SpecialWordsType&,
    decltype(std::declval<uci::type::OwnerProducerChoiceType>().chooseNATO_SpecialWord())>);

} // namespace
