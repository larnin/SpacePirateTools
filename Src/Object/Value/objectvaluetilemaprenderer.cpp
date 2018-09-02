#include "objectvaluetilemaprenderer.h"
#include "UI/Scene/NodeRenderer/valuerenderertilemaprenderer.h"
#include "UI/Object/Value/tilemaprenderervaluewidget.h"

ObjectValueTilemapRenderer::ObjectValueTilemapRenderer()
    : ObjectValueBase(ValueType::TilemapRenderer)
    , tileSize(0)
    , tileDelta(0)
{

}

ObjectValueTilemapRenderer::ObjectValueTilemapRenderer(const QJsonObject & obj)
    : ObjectValueTilemapRenderer()
{
    tilemapName = obj["tilemap"].toString();
    textureName = obj["texture"].toString();
    tileSize = obj["size"].toInt();
    tileDelta = obj["delta"].toInt();
    offset.x = obj["x"].toDouble();
    offset.y = obj["y"].toDouble();
}

std::unique_ptr<ValueRendererBase> ObjectValueTilemapRenderer::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererTilemapRenderer>(node, this);
}

QString ObjectValueTilemapRenderer::toString() const
{
    return "Tilemap : " + tilemapName + "\nTexture : " + textureName + "\nTaille : " + QString::number(tileSize) + "\nDelta : " + QString::number(tileDelta) + "\nOffset : " + QString::number(offset.x, 'g', 2) + " * " + QString::number(offset.y, 'g', 2);
}

QWidget* ObjectValueTilemapRenderer::createUi()
{
    return new TilemapRendererValueWidget(*this);
}

void ObjectValueTilemapRenderer::onSave(QJsonObject & obj) const
{
    obj.insert("tilemap", tilemapName);
    obj.insert("texture", textureName);
    obj.insert("size", static_cast<int>(tileSize));
    obj.insert("delta", static_cast<int>(tileDelta));
    obj.insert("x", offset.x);
    obj.insert("y", offset.y);
}
