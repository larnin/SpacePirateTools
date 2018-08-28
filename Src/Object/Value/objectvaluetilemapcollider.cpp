#include "objectvaluetilemapcollider.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"

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
}

std::unique_ptr<ValueRendererBase> ObjectValueTilemapCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}

QString ObjectValueTilemapCollider::toString() const
{
    return "Tilemap : " + tilemapName + "\nTaille : " + QString::number(tileSize);
}

QWidget* ObjectValueTilemapCollider::createUi()
{
    return nullptr;
}

void ObjectValueTilemapCollider::onSave(QJsonObject & obj) const
{
    obj.insert("tilemap", tilemapName);
    obj.insert("size", static_cast<int>(tileSize));
}
