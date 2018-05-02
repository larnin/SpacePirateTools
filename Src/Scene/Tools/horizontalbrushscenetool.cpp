#include "horizontalbrushscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

HorizontalBrushSceneTool::HorizontalBrushSceneTool(TilesetLayer &layer, const BrushHorizontal &brush)
    : BaseTilesetSceneTool(layer)
    , m_brush(brush)
{

}

void HorizontalBrushSceneTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    updateTile(pos, true);
}

void HorizontalBrushSceneTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    bool haveItemLeft = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x - 1, pos.y)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool haveItemRight = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x + 1, pos.y)](const auto & b){return b.pos == pos;}) != m_blocks.end();

    if(haveItemLeft && haveItemRight)
        it->tile = m_brush.tile(TileShape::Horizontal).toTileInfos();
    else if(haveItemLeft)
        it->tile = m_brush.tile(TileShape::Right3).toTileInfos();
    else if(haveItemRight)
        it->tile = m_brush.tile(TileShape::Left3).toTileInfos();

    if(updateNext)
    {
        updateTile(sf::Vector2u(pos.x - 1, pos.y), false);
        updateTile(sf::Vector2u(pos.x + 1, pos.y), false);
    }
}

void HorizontalBrushSceneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
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
