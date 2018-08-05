#include "objectvaluecolor.h"
#include "UI/Object/Value/colorvaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

ObjectValueColor::ObjectValueColor()
    : ObjectValueBase(ValueType::Color)
    , color(255, 255, 255)
{

}

ObjectValueColor::ObjectValueColor(const QJsonObject & obj)
    : ObjectValueColor()
{
    color.r = obj["r"].toInt();
    color.g = obj["g"].toInt();
    color.b = obj["b"].toInt();
    color.a = obj["a"].toInt();
}

QString ObjectValueColor::toString() const
{
    return "Couleur : r(" + QString::number(color.r) + ") g(" + QString::number(color.g) + ") b(" + QString::number(color.b) + ") a(" + QString::number(color.a) + ")";
}

QWidget* ObjectValueColor::createUi()
{
    return new ColorValueWidget(*this);
}

void ObjectValueColor::onSave(QJsonObject & obj) const
{
    obj.insert("r", color.r);
    obj.insert("g", color.g);
    obj.insert("b", color.b);
    obj.insert("a", color.a);
}

std::unique_ptr<ValueRendererBase> ObjectValueColor::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
