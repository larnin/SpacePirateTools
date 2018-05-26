#include "verticalbrushmaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

VerticalBrushMapTool::VerticalBrushMapTool(TilemapData & data, const BrushVertical &brush)
    : BaseMapTool(data)
    , m_brush(brush)
{

}

void VerticalBrushMapTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(BlockConnexions(pos));

    if(m_altButtonPressed)
    {
        checkTileOnMap(sf::Vector2u(pos.x, pos.y - 1));
        checkTileOnMap(sf::Vector2u(pos.x, pos.y + 1));
    }

    updateTile(pos, true);
}

void VerticalBrushMapTool::addTileConnexions(const BlockConnexions & block)
{
    auto pos = block.pos;

    auto itCurrent = std::find_if(m_connexions.begin(), m_connexions.end(), [pos](const auto & b){return b.pos == pos;});
    if(itCurrent == m_connexions.end())
    {
        m_connexions.emplace_back(block);
        itCurrent = m_connexions.end() - 1;
    }
    else
    {
       if(block.top)
           itCurrent->top = true;
       if(block.bottom)
           itCurrent->bottom = true;
    }

    auto itTop = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x, pos.y-1)](const auto & b){return b.pos == pos;});
    auto itBottom = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x, pos.y+1)](const auto & b){return b.pos == pos;});

    if(itTop != m_connexions.end())
    {
        itCurrent->top = true;
        itTop->bottom = true;
    }
    if(itBottom != m_connexions.end())
    {
        itCurrent->bottom = true;
        itBottom->top = true;
    }
}

void VerticalBrushMapTool::checkTileOnMap(const sf::Vector2u & pos)
{
    if(pos.y >= m_data.tiles.getSize().y)
        return;

    auto tile = m_data.tiles(pos);
    bool ok = false;
    TileShape shape;
    for(const auto & s : m_brush.validShapes())
    {
        if(tile.id == m_brush.tile(s).id)
        {
            shape = s;
            ok = true;
        }
    }
    if(!ok)
        return;

    BlockConnexions b(pos);
    switch (shape)
    {
    case TileShape::Vertical:
        b.top = true;
        b.bottom = true;
        break;
    case TileShape::Top3:
        b.bottom = true;
        break;
    case TileShape::Down3:
        b.top = true;
        break;
    default:
        break;
    }

    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(b);
}

void VerticalBrushMapTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    auto shape = std::find_if(m_connexions.begin(), m_connexions.end(), [pos](const auto & b){return b.pos == pos;});
    assert(shape != m_connexions.end());
    bool haveItemTop = shape->top;
    bool haveItemBottom = shape->bottom;

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

void VerticalBrushMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = m_data.tileSize;
    auto delta = m_data.tileDelta;

    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f) * size, (pos.y - 0.5f) * size));

    target.draw(shape);

    if(!m_texture.isValid())
        return;

    unsigned int tileInWidth((m_texture->getSize().x + delta) / (size + delta));

    auto id = m_brush.tile(TileShape::Full).id;
    auto x = id % tileInWidth;
    auto y = id / tileInWidth;

    sf::Sprite sprite(*m_texture, sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
    sprite.setPosition((pos.x - 0.5f) * size, (pos.y - 0.5f) * size);
    sprite.setColor(sf::Color(255, 255, 255, a));

    target.draw(sprite);
}


void VerticalBrushMapTool::beforeSelectionEnd()
{
    m_connexions.clear();
}
