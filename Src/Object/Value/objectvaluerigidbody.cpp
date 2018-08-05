#include "objectvaluerigidbody.h"
#include "UI/Object/Value/rigidbodyvaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueRigidbody::ObjectValueRigidbody()
    : ObjectValueBase(ValueType::Rigidbody)
    , mass(1)
{

}

ObjectValueRigidbody::ObjectValueRigidbody(const QJsonObject & obj)
    : ObjectValueRigidbody()
{
    mass = obj["mass"].toDouble();
}

QString ObjectValueRigidbody::toString() const
{
    return "Mass : " + QString::number(mass);
}

QWidget* ObjectValueRigidbody::createUi()
{
    return new RigidbodyValueWidget(*this);
}

void ObjectValueRigidbody::onSave(QJsonObject & obj) const
{
    obj.insert("mass", mass);
}

std::unique_ptr<ValueRendererBase> ObjectValueRigidbody::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
