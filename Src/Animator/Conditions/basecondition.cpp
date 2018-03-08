#include "basecondition.h"
#include <stdexcept>

QString ConditionTypeToString(ConditionType type)
{
    switch(type)
    {
    case ConditionType::And:
        return "Et";
    case ConditionType::Or:
        return "Ou";
    case ConditionType::XOr:
        return "Ou exclusif";
    case ConditionType::Not:
        return "Non";
    case ConditionType::AnimationFinished:
        return "Animation terminée";
    case ConditionType::PropertyMore:
        return "Propriété supérieur";
    case ConditionType::PropertyLess:
        return "Propriété inférieur";
    case ConditionType::PropertyMoreEqual:
        return "Propriété supérieur ou égal";
    case ConditionType::PropertyLessEqual:
        return "Propriété inférieur ou égal";
    case ConditionType::PropertyEqual:
        return "Propriété égal";
    case ConditionType::PropertyInequal:
        return "Propriété inégal";
    case ConditionType::PropertyBetween:
        return "Propriété intervalle";
    case ConditionType::PropertyOutside:
        return "Propriété hors intervalle";
    default:
        break;
    }
    return "";
}

BaseCondition::BaseCondition(ConditionType type)
    : m_conditionType(type)
{

}

std::unique_ptr<BaseCondition> BaseCondition::load(const QJsonObject & obj)
{
    auto typeIt = obj.find("conditionType");
    if(typeIt == obj.end())
    {
        throw std::runtime_error("Condition mal formatée");
        return {};
    }

    ConditionType type = static_cast<ConditionType>(typeIt->toInt());
    switch (type)
    {

    default:
        break;
    }

    return {};
}

QJsonObject BaseCondition::save() const
{
    QJsonObject obj;
    obj.insert("conditionType", static_cast<int>(m_conditionType));

    onSave(obj);

    return obj;
}
