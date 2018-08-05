#include "objectvaluebox2dcollider.h"
#include "UI/Object/Value/box2dcollidervaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueBox2DCollider::ObjectValueBox2DCollider()
    : ObjectValueBase(ValueType::Box2DCollider)
    , center(0, 0)
    , size(100, 100)
{

}

ObjectValueBox2DCollider::ObjectValueBox2DCollider(const QJsonObject & obj)
    : ObjectValueBox2DCollider()
{
    center.x = obj["cx"].toDouble();
    center.y = obj["cy"].toDouble();
    size.x = obj["sx"].toDouble();
    size.y = obj["sy"].toDouble();
}

QString ObjectValueBox2DCollider::toString() const
{
    return "Center : " + QString::number(center.x) + " * " + QString::number(center.y) + "\n"
            + "Taille : " + QString::number(size.x) + " * " + QString::number(size.y);
}

QWidget* ObjectValueBox2DCollider::createUi()
{
    return new Box2DColliderValueWidget(*this);
}

void ObjectValueBox2DCollider::onSave(QJsonObject & obj) const
{
    obj.insert("cx", center.x);
    obj.insert("cy", center.y);
    obj.insert("sx", size.x);
    obj.insert("sy", size.y);
}

std::unique_ptr<ValueRendererBase> ObjectValueBox2DCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
