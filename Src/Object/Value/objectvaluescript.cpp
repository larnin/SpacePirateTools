#include "objectvaluescript.h"
#include "UI/Object/Value/scriptvaluewidget.h"

ObjectValueScript::ObjectValueScript()
    : ObjectValueBase(ValueType::Script)
{

}

ObjectValueScript::ObjectValueScript(const QJsonObject & obj)
    : ObjectValueScript()
{
    scriptName = obj["s"].toString();
}

QString ObjectValueScript::toString() const
{
    return "Nom de script : " + scriptName;
}

QWidget* ObjectValueScript::createUi()
{
    return new ScriptValueWidget(*this);
}

void ObjectValueScript::onSave(QJsonObject & obj) const
{
    obj.insert("s", scriptName);
}
