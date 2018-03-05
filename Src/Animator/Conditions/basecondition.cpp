#include "basecondition.h"
#include <stdexcept>

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
