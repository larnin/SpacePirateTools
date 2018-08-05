#include "objectvaluescript.h"
#include "UI/Object/Value/scriptvaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

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

std::unique_ptr<ValueRendererBase> ObjectValueScript::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
