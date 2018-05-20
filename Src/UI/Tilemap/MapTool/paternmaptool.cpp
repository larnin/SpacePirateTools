#include "paternmaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <chrono>

PaternMapTool::PaternMapTool(TilemapData & data, const BrushPatern & brush)
    : BaseMapTool(data)
    , m_brush(brush)
{

}

void PaternMapTool::onAddTile(const sf::Vector2u & pos)
{
    if(m_blocks.size() > 0)
        return;

    auto brushSize(m_brush.getSize());
    auto size(m_data.tiles.getSize());

    for(unsigned int i(0) ; i < brushSize.x ; i++)
        for(unsigned int j(0) ; j < brushSize.y ; j++)
        {
            sf::Vector2u tilePos(pos.x + i - brushSize.x/2, pos.y + j - brushSize.y/2);
            if(tilePos.x < size.x && tilePos.y < size.y)
            {
                auto tile = m_brush[sf::Vector2u(i, j)];
                m_blocks.push_back({tilePos, TileInfos{tile.id, tile.collider}});
            }
        }
}

void PaternMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    if(pos.x >= m_data.tiles.getSize().x || pos.y >= m_data.tiles.getSize().y)
        return;

    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = m_data.tileSize;
    auto delta = m_data.tileDelta;

    auto brushSize(m_brush.getSize());

    sf::RectangleShape shape(sf::Vector2f(size * brushSize.x, size * brushSize.y));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f - brushSize.x/2) * size, (pos.y - 0.5f - brushSize.y/2) * size));

    target.draw(shape);

    if(!m_texture.isValid())
        return;

    unsigned int tileInWidth((m_texture->getSize().x + delta) / (size + delta));

    sf::Sprite sprite(*m_texture);
    sprite.setColor(sf::Color(255, 255, 255, a));

    for(unsigned int i(0) ; i < brushSize.x ; i++)
        for(unsigned int j(0) ; j < brushSize.y ; j++)
        {
            sf::Vector2u tilePos(pos.x + i - brushSize.x/2, pos.y + j - brushSize.y/2);

            if(tilePos.x >= m_data.tiles.getSize().x || tilePos.y >= m_data.tiles.getSize().y)
                continue;

            auto id = m_brush[sf::Vector2u(i, j)].id;
            auto x = id % tileInWidth;
            auto y = id / tileInWidth;
            sprite.setTextureRect(sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
            sprite.setPosition((tilePos.x - 0.5f) * size, (tilePos.y - 0.5f) * size);

            target.draw(sprite);
        }
}
