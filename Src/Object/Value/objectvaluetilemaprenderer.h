#ifndef OBJECTVALUETILEMAPRENDERER_H
#define OBJECTVALUETILEMAPRENDERER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>
#include <QString>

class ObjectValueTilemapRenderer : public ObjectValueBase
{
public:
    ObjectValueTilemapRenderer();
    ObjectValueTilemapRenderer(const QJsonObject & obj);
    ObjectValueTilemapRenderer(const ObjectValueTilemapRenderer &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueTilemapRenderer>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    QString tilemapName;
    QString textureName;

    unsigned int tileSize;
    unsigned int tileDelta;

    sf::Vector2f offset;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUETILEMAPRENDERER_H
