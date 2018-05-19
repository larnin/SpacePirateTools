#ifndef TILEMAPRENDERER_H
#define TILEMAPRENDERER_H

#include "Tilemap/tilemapdata.h"
#include "ressource.h"
#include <SFML/Graphics/RenderTarget.hpp>

class TilemapRenderer
{
public:
    TilemapRenderer(const TilemapData & data);
    void setTexture(Texture texture){m_texture = texture;}

    void drawTiles(sf::RenderTarget & target) const;
    void drawColliders(sf::RenderTarget & target) const;

private:
    static void drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect);

    const TilemapData & m_data;
    Texture m_texture;
};

#endif // TILEMAPRENDERER_H
