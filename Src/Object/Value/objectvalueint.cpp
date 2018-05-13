#include "objectvalueint.h"
#include "UI/Object/Value/intvaluewidget.h"

ObjectValueInt::ObjectValueInt()
    : ObjectValueBase(ValueType::Int)
    , value(0)
{

}

ObjectValueInt::ObjectValueInt(const QJsonObject & obj)
    : ObjectValueInt()
{
    value = obj["value"].toInt();
}

QString ObjectValueInt::toString() const
{
    return "Valeur : " + QString::number(value);
}

QWidget* ObjectValueInt::createUi()
{
    return new IntValueWidget(*this);
}

void ObjectValueInt::onSave(QJsonObject & obj) const
{
    obj.insert("value", value);
}
