#include "verticalbrushscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

VerticalBrushSceneTool::VerticalBrushSceneTool(TilesetLayer &layer, const BrushVertical &brush)
    : BaseTilesetSceneTool(layer)
    , m_brush(brush)
{

}

void VerticalBrushSceneTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    updateTile(pos, true);
}

void VerticalBrushSceneTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    bool haveItemTop = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x, pos.y - 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool haveItemBottom = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x, pos.y + 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();

    if(haveItemTop && haveItemBottom)
        it->tile = m_brush.tile(TileShape::Vertical).toTileInfos();
    else if(haveItemTop)
        it->tile = m_brush.tile(TileShape::Down3).toTileInfos();
    else if(haveItemBottom)
        it->tile = m_brush.tile(TileShape::Top3).toTileInfos();

    if(updateNext)
    {
        updateTile(sf::Vector2u(pos.x, pos.y - 1), false);
        updateTile(sf::Vector2u(pos.x, pos.y + 1), false);
    }
}

void VerticalBrushSceneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = ProjectInfos::instance().options().tileSize;
    auto delta = ProjectInfos::instance().options().delta;

    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f) * size, (pos.y - 0.5f) * size));

    target.draw(shape);

    if(!m_layer.texture().isValid())
        return;

    unsigned int tileInWidth((m_layer.texture()->getSize().x + delta) / (size + delta));

    auto id = m_brush.tile(TileShape::Full).id;
    auto x = id % tileInWidth;
    auto y = id / tileInWidth;

    sf::Sprite sprite(*m_layer.texture(), sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
    sprite.setPosition((pos.x - 0.5f) * size, (pos.y - 0.5f) * size);
    sprite.setColor(sf::Color(255, 255, 255, a));

    target.draw(sprite);
}
