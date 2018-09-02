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

inline bool operator==(const ObjectValueTilemapRenderer & a, const ObjectValueTilemapRenderer & b)
{
    if(a.tilemapName != b.tilemapName)
        return false;
    if(a.textureName != b.textureName)
        return false;
    if(a.tileSize != b.tileSize)
        return false;
    if(a.tileDelta != b.tileDelta)
        return false;
    if(a.offset != b.offset)
        return false;
    return true;
}

inline bool operator!=(const ObjectValueTilemapRenderer & a, const ObjectValueTilemapRenderer & b)
{
    return !(a==b);
}

#endif // OBJECTVALUETILEMAPRENDERER_H
