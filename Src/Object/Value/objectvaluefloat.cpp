#include "objectvaluefloat.h"
#include "UI/Object/Value/floatvaluewidget.h"

ObjectValueFloat::ObjectValueFloat()
    : ObjectValueBase(ValueType::Float)
    , value(0)
{

}

ObjectValueFloat::ObjectValueFloat(const QJsonObject & obj)
    : ObjectValueFloat()
{
    value = obj["value"].toDouble();
}

QString ObjectValueFloat::toString() const
{
    return "Valeur : " + QString::number(value);
}

QWidget* ObjectValueFloat::createUi()
{
    return new FloatValueWidget(*this);
}

void ObjectValueFloat::onSave(QJsonObject & obj) const
{
    obj.insert("value", value);
}
