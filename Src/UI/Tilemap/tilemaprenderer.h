#ifndef TILEMAPRENDERER_H
#define TILEMAPRENDERER_H

#include "Tilemap/tilemapdata.h"
#include "ressource.h"
#include <SFML/Graphics/RenderTarget.hpp>

class TilemapRenderer
{
public:
    TilemapRenderer();
    TilemapRenderer(TilemapData & data);

    inline void setTexture(Texture texture){m_texture = texture;}
    inline void setData(TilemapData & data){m_data = &data;}

    void drawTiles(sf::RenderTarget & target) const;
    void drawColliders(sf::RenderTarget & target) const;

    static void drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect);
private:

    TilemapData * m_data;
    Texture m_texture;
};

#endif // TILEMAPRENDERER_H
