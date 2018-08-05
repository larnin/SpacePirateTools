#include "objectvaluevector2i.h"
#include "UI/Object/Value/vector2ivaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueVector2i::ObjectValueVector2i()
    : ObjectValueBase(ValueType::Vector2i)
    , value(0, 0)
{

}

ObjectValueVector2i::ObjectValueVector2i(const QJsonObject & obj)
    : ObjectValueVector2i()
{
    value.x = obj["x"].toInt();
    value.y = obj["y"].toInt();
}

QString ObjectValueVector2i::toString() const
{
    return "Valeur : " + QString::number(value.x) + " * " + QString::number(value.y);
}

QWidget* ObjectValueVector2i::createUi()
{
    return new Vector2iValueWidget(*this);
}

void ObjectValueVector2i::onSave(QJsonObject & obj) const
{
    obj.insert("x", value.x);
    obj.insert("y", value.y);
}

std::unique_ptr<ValueRendererBase> ObjectValueVector2i::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
