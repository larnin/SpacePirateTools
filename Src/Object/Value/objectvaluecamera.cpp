#include "objectvaluecamera.h"
#include "UI/Scene/NodeRenderer/valuerenderercamera.h"
#include "UI/Object/Value/cameravaluewidget.h"

ObjectValueCamera::ObjectValueCamera()
    : ObjectValueBase(ValueType::Camera)
    , layerMask(0)
    , fixedSize(false)
    , value(0)
{

}

ObjectValueCamera::ObjectValueCamera(const QJsonObject & obj)
    : ObjectValueCamera()
{
    layerMask = obj["mask"].toInt();
    fixedSize = obj["fixed"].toBool();
    value = obj["value"].toDouble();
}

std::unique_ptr<ValueRendererBase> ObjectValueCamera::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererCamera>(node, this);
}

QString ObjectValueCamera::toString() const
{
    if(fixedSize)
        return "Fixed size camera\nMask : " + QString::number(layerMask) + "\nSize : " + QString::number(value);
    return "Window scaling camera\nMask : " + QString::number(layerMask) + "\nZoom : " + QString::number(value);
}

QWidget* ObjectValueCamera::createUi()
{
    return new CameraValueWidget(*this);
}

void ObjectValueCamera::onSave(QJsonObject & obj) const
{
    obj.insert("mask", static_cast<int>(layerMask));
    obj.insert("fixed", fixedSize);
    obj.insert("value", value);
}
