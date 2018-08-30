#ifndef VALUERENDERERTILEMAPCOLLIDER_H
#define VALUERENDERERTILEMAPCOLLIDER_H

#include "valuerendererbase.h"
#include "Object/Value/objectvaluetilemapcollider.h"
#include "Tilemap/tilemapdata.h"
#include <memory>

class ValueRendererTilemapCollider : public ValueRendererBase
{
public:
    ValueRendererTilemapCollider(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &) const override;
    void drawGizmos(sf::RenderTarget & target) const override;
    void update() override;

private:
    void loadTilemap();

    ObjectValueTilemapCollider * m_collider;
    std::unique_ptr<TilemapData> m_tilemap;

    QString m_currentTilemapName;
    sf::VertexArray m_array;
};

#endif // VALUERENDERERTILEMAPCOLLIDER_H
