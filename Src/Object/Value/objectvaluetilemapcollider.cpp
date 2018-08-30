#include "objectvaluetilemapcollider.h"
#include "UI/Scene/NodeRenderer/valuerenderertilemapcollider.h"
#include "UI/Object/Value/tilemapcollidervaluewidget.h"

ObjectValueTilemapCollider::ObjectValueTilemapCollider()
    : ObjectValueBase (ValueType::TilemapCollider)
    , tileSize(1)
{

}

ObjectValueTilemapCollider::ObjectValueTilemapCollider(const QJsonObject & obj)
    : ObjectValueTilemapCollider()
{
    tilemapName = obj["tilemap"].toString();
    tileSize = obj["size"].toInt();
    offset.x = obj["x"].toDouble();
    offset.y = obj["y"].toDouble();
}

std::unique_ptr<ValueRendererBase> ObjectValueTilemapCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererTilemapCollider>(node, this);
}

QString ObjectValueTilemapCollider::toString() const
{
    return "Tilemap : " + tilemapName + "\nTaille : " + QString::number(tileSize) + "\nOffset : " + QString::number(offset.x, 'g', 2) + " * " + QString::number(offset.y, 'g', 2);
}

QWidget* ObjectValueTilemapCollider::createUi()
{
    return new TilemapColliderValueWidget(*this);
}

void ObjectValueTilemapCollider::onSave(QJsonObject & obj) const
{
    obj.insert("tilemap", tilemapName);
    obj.insert("size", static_cast<int>(tileSize));
    obj.insert("x", offset.x);
    obj.insert("y", offset.y);
}
