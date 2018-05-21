#include "pastemaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <chrono>

PasteMapTool::PasteMapTool(TilemapData & data, const std::vector<CopyMapTool::CopyValue> & value)
    : BaseMapTool(data)
    , m_value(value)
{
    updateValueSize();
}

void PasteMapTool::onAddTile(const sf::Vector2u & pos)
{
    if(m_blocks.size() > 0)
        return;

    auto size = m_data.tiles.getSize();

    for(const auto & t : m_value)
    {
        sf::Vector2u tilePos(pos.x + t.pos.x - m_valueSize.x/2, pos.y + t.pos.y - m_valueSize.y/2);
        if(tilePos.x < size.x && tilePos.y < size.y)
            m_blocks.push_back({tilePos, t.tile});
    }
}

void PasteMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    if(pos.x >= m_data.tiles.getSize().x || pos.y >= m_data.tiles.getSize().y)
        return;

    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = m_data.tileSize;
    auto delta = m_data.tileDelta;

    sf::RectangleShape shape(sf::Vector2f(size * m_valueSize.x, size * m_valueSize.y));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f - m_valueSize.x/2) * size, (pos.y - 0.5f - m_valueSize.y/2) * size));

    target.draw(shape);

    if(!m_texture.isValid())
        return;

    unsigned int tileInWidth((m_texture->getSize().x + delta) / (size + delta));

    sf::Sprite sprite(*m_texture);
    sprite.setColor(sf::Color(255, 255, 255, a));

    for(const auto t : m_value)
    {
        sf::Vector2u tilePos(pos.x + t.pos.x - m_valueSize.x/2, pos.y + t.pos.y - m_valueSize.y/2);

        if(tilePos.x >= m_data.tiles.getSize().x || tilePos.y >= m_data.tiles.getSize().y)
            continue;

        auto id = t.tile.id;
        auto x = id % tileInWidth;
        auto y = id / tileInWidth;
        sprite.setTextureRect(sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
        sprite.setPosition((tilePos.x - 0.5f) * size, (tilePos.y - 0.5f) * size);

        target.draw(sprite);
    }
}

void PasteMapTool::updateValueSize()
{
    sf::Vector2u max(0, 0);

    for(const auto & t : m_value)
    {
        max.x = std::max(max.x, t.pos.x);
        max.y = std::max(max.y, t.pos.y);
    }
    m_valueSize = max + sf::Vector2u(1, 1);
}
