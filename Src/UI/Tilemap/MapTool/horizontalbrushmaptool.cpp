#include "horizontalbrushmaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

HorizontalBrushMapTool::HorizontalBrushMapTool(TilemapData & data, const BrushHorizontal &brush)
    : BaseMapTool(data)
    , m_brush(brush)
{

}

void HorizontalBrushMapTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(BlockConnexions(pos));

    if(m_altButtonPressed)
    {
        checkTileOnMap(sf::Vector2u(pos.x - 1, pos.y));
        checkTileOnMap(sf::Vector2u(pos.x + 1, pos.y));
    }

    updateTile(pos, true);
}

void HorizontalBrushMapTool::addTileConnexions(const BlockConnexions & block)
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
       if(block.left)
           itCurrent->left = true;
       if(block.right)
           itCurrent->right = true;
    }

    auto itLeft = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x - 1, pos.y)](const auto & b){return b.pos == pos;});
    auto itRight = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x + 1, pos.y)](const auto & b){return b.pos == pos;});

    if(itLeft != m_connexions.end())
    {
        itCurrent->left = true;
        itLeft->right = true;
    }
    if(itRight != m_connexions.end())
    {
        itCurrent->right = true;
        itRight->left = true;
    }
}

void HorizontalBrushMapTool::checkTileOnMap(const sf::Vector2u & pos)
{
    if(pos.x >= m_data.tiles.getSize().x)
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
    case TileShape::Horizontal:
        b.left = true;
        b.right = true;
        break;
    case TileShape::Left3:
        b.right = true;
        break;
    case TileShape::Right3:
        b.left = true;
        break;
    default:
        break;
    }

    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(b);
}

void HorizontalBrushMapTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    auto shape = std::find_if(m_connexions.begin(), m_connexions.end(), [pos](const auto & b){return b.pos == pos;});
    assert(shape != m_connexions.end());
    bool haveItemLeft = shape->left;
    bool haveItemRight = shape->right;

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

void HorizontalBrushMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
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

void HorizontalBrushMapTool::beforeSelectionEnd()
{
    m_connexions.clear();
}
