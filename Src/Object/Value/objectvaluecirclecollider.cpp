#include "objectvaluecirclecollider.h"
#include "UI/Object/Value/circlecollidervaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderercirclecollider.h"

ObjectValueCircleCollider::ObjectValueCircleCollider()
    : ObjectValueBase(ValueType::CircleCollider)
    , center(0, 0)
    , size(100)
{

}

ObjectValueCircleCollider::ObjectValueCircleCollider(const QJsonObject & obj)
    : ObjectValueCircleCollider()
{
    center.x = obj["cx"].toDouble();
    center.y = obj["cy"].toDouble();
    size = obj["s"].toDouble();
    collisionLayer = obj["layer"].toInt();
}

QString ObjectValueCircleCollider::toString() const
{
    return "Center : " + QString::number(center.x) + " * " + QString::number(center.y) + "\n"
            + "Taille : " + QString::number(size) + "\n"
            + "Collision layer : " + QString::number(collisionLayer);
}

QWidget* ObjectValueCircleCollider::createUi()
{
    return new CircleColliderValueWidget(*this);
}

void ObjectValueCircleCollider::onSave(QJsonObject & obj) const
{
    obj.insert("cx", center.x);
    obj.insert("cy", center.y);
    obj.insert("s", size);
    obj.insert("layer", static_cast<int>(collisionLayer));
}

std::unique_ptr<ValueRendererBase> ObjectValueCircleCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererCircleCollider>(node, this);
}
