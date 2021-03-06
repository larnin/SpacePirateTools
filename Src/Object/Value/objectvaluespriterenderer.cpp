#include "objectvaluespriterenderer.h"
#include "UI/Object/Value/spriterenderervaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderersprite.h"

ObjectValueSpriteRenderer::ObjectValueSpriteRenderer()
    : ObjectValueBase(ValueType::SpriteRenderer)
    , textureRect(0, 0, 100, 100)
{

}

ObjectValueSpriteRenderer::ObjectValueSpriteRenderer(const QJsonObject & obj)
    : ObjectValueSpriteRenderer()
{
    textureRect.left = obj["l"].toInt();
    textureRect.top = obj["t"].toInt();
    textureRect.height = obj["h"].toInt();
    textureRect.width = obj["w"].toInt();
    offset.x = obj["x"].toDouble();
    offset.y = obj["y"].toDouble();
    textureName = obj["texture"].toString();
}

QString ObjectValueSpriteRenderer::toString() const
{
    return "Origine : " + QString::number(textureRect.left) + " * " + QString::number(textureRect.top) + "\n"
            + "Taille : " + QString::number(textureRect.width) + " * " + QString::number(textureRect.height);
}

QWidget* ObjectValueSpriteRenderer::createUi()
{
    return new SpriteRendererValueWidget(*this);
}

void ObjectValueSpriteRenderer::onSave(QJsonObject & obj) const
{
    obj.insert("l", textureRect.left);
    obj.insert("t", textureRect.top);
    obj.insert("h", textureRect.height);
    obj.insert("w", textureRect.width);
    obj.insert("x", offset.x);
    obj.insert("y", offset.y);
    obj.insert("texture", textureName);
}

std::unique_ptr<ValueRendererBase> ObjectValueSpriteRenderer::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererSprite>(node, this);
}
