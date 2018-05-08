#include "pastetilesetscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <chrono>

PasteTilesetSceneTool::PasteTilesetSceneTool(TilesetLayer &layer, const std::vector<CopyTilesetSceneTool::CopyValue> &data)
    : BaseTilesetSceneTool(layer)
    , m_data(data)
{
    updateDataSize();
}

void PasteTilesetSceneTool::onAddTile(const sf::Vector2u & pos)
{
    if(m_blocks.size() > 0)
        return;

    auto layerSize(m_layer.size());

    for(const auto & t : m_data)
    {
        sf::Vector2u tilePos(pos.x + t.pos.x - m_dataSize.x/2, pos.y + t.pos.y - m_dataSize.y/2);
        if(tilePos.x < layerSize.x && tilePos.y < layerSize.y)
            m_blocks.push_back({tilePos, t.tile});
    }
}

void PasteTilesetSceneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    if(pos.x >= m_layer.size().x || pos.y >= m_layer.size().y)
        return;

    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = ProjectInfos::instance().options().tileSize;
    auto delta = ProjectInfos::instance().options().delta;

    sf::RectangleShape shape(sf::Vector2f(size * m_dataSize.x, size * m_dataSize.y));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f - m_dataSize.x/2) * size, (pos.y - 0.5f - m_dataSize.y/2) * size));

    target.draw(shape);

    if(!m_layer.texture().isValid())
        return;

    unsigned int tileInWidth((m_layer.texture()->getSize().x + delta) / (size + delta));

    sf::Sprite sprite(*m_layer.texture());
    sprite.setColor(sf::Color(255, 255, 255, a));

    for(const auto t : m_data)
    {
        sf::Vector2u tilePos(pos.x + t.pos.x - m_dataSize.x/2, pos.y + t.pos.y - m_dataSize.y/2);

        if(tilePos.x >= m_layer.size().x || tilePos.y >= m_layer.size().y)
            continue;

        auto id = t.tile.id;
        auto x = id % tileInWidth;
        auto y = id / tileInWidth;
        sprite.setTextureRect(sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
        sprite.setPosition((tilePos.x - 0.5f) * size, (tilePos.y - 0.5f) * size);

        target.draw(sprite);
    }
}

void PasteTilesetSceneTool::updateDataSize()
{
    sf::Vector2u max(0, 0);

    for(const auto & t : m_data)
    {
        max.x = std::max(max.x, t.pos.x);
        max.y = std::max(max.y, t.pos.y);
    }
    m_dataSize = max + sf::Vector2u(1, 1);
}
