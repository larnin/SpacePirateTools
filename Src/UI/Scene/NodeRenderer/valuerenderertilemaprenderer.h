#ifndef VALUERENDERERTILEMAPRENDERER_H
#define VALUERENDERERTILEMAPRENDERER_H

#include "valuerendererbase.h"
#include "Object/Value/objectvaluetilemaprenderer.h"
#include "Tilemap/tilemapdata.h"
#include "ressource.h"
#include <SFML/Graphics/VertexArray.hpp>

class ValueRendererTilemapRenderer : public ValueRendererBase
{
public:
    ValueRendererTilemapRenderer(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget & target) const override;
    void drawGizmos(sf::RenderTarget &) const override;
    void update() override;

private:
    void loadTilemap();

    ObjectValueTilemapRenderer * m_data;
    std::unique_ptr<TilemapData> m_tilemap;
    Texture m_texture;

    sf::VertexArray m_array;

    ObjectValueTilemapRenderer m_currentData;
};

#endif // VALUERENDERERTILEMAPRENDERER_H
