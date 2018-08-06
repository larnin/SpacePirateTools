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
}

QString ObjectValueCircleCollider::toString() const
{
    return "Center : " + QString::number(center.x) + " * " + QString::number(center.y) + "\n"
            + "Taille : " + QString::number(size);
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
}

std::unique_ptr<ValueRendererBase> ObjectValueCircleCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererCircleCollider>(node, this);
}
