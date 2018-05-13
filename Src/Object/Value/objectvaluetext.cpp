#include "objectvaluetext.h"
#include "UI/Object/Value/textvaluewidget.h"

ObjectValueText::ObjectValueText()
    : ObjectValueBase(ValueType::Text)
{

}

ObjectValueText::ObjectValueText(const QJsonObject & obj)
    : ObjectValueText()
{
    text = obj["value"].toString();
}

QString ObjectValueText::toString() const
{
    return "Texte : " + text;
}

QWidget* ObjectValueText::createUi()
{
    return new TextValueWidget(*this);
}

void ObjectValueText::onSave(QJsonObject & obj) const
{
    obj.insert("value", text);
}
