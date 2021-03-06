#include "objectvaluetransform.h"
#include "UI/Object/Value/transformvaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueTransform::ObjectValueTransform()
    : ObjectValueBase(ValueType::Transform)
    , position(0, 0)
    , scale(1, 1)
    , rotation(0)
{

}

ObjectValueTransform::ObjectValueTransform(const QJsonObject & obj)
    : ObjectValueTransform()
{
    position.x = obj["px"].toDouble();
    position.y = obj["py"].toDouble();
    scale.x = obj["sx"].toDouble();
    scale.y = obj["sy"].toDouble();
    rotation = obj["rot"].toDouble();
}

QString ObjectValueTransform::toString() const
{
    return "Position : " + QString::number(position.x) + " * " + QString::number(position.y) + "\n"
            + "Scale : " + QString::number(scale.x) + " * " + QString::number(scale.y) + "\n"
            + "Rotation : " + QString::number(rotation);
}

QWidget* ObjectValueTransform::createUi()
{
    return new TransformValueWidget(*this);
}

void ObjectValueTransform::onSave(QJsonObject & obj) const
{
    obj.insert("px", position.x);
    obj.insert("py", position.y);
    obj.insert("sx", scale.x);
    obj.insert("sy", scale.y);
    obj.insert("rot", rotation);
}

sf::Transform ObjectValueTransform::getSFMLLocalTransform() const
{
    sf::Transform t;
    t.translate(position).rotate(rotation).scale(scale);
    return t;
}

std::unique_ptr<ValueRendererBase> ObjectValueTransform::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
