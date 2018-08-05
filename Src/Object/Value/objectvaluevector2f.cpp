#include "objectvaluevector2f.h"
#include "UI/Object/Value/vector2fvaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueVector2f::ObjectValueVector2f()
    : ObjectValueBase(ValueType::Vector2f)
    , value(0, 0)
{

}

ObjectValueVector2f::ObjectValueVector2f(const QJsonObject & obj)
    : ObjectValueVector2f()
{
    value.x = obj["x"].toDouble();
    value.y = obj["y"].toDouble();
}

QString ObjectValueVector2f::toString() const
{
    return "Valeur : " + QString::number(value.x) + " * " + QString::number(value.y);
}

QWidget* ObjectValueVector2f::createUi()
{
    return new Vector2fValueWidget(*this);
}

void ObjectValueVector2f::onSave(QJsonObject & obj) const
{
    obj.insert("x", value.x);
    obj.insert("y", value.y);
}

std::unique_ptr<ValueRendererBase> ObjectValueVector2f::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
