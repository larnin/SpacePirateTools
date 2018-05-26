#include "fullbrushmaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

FullBrushMapTool::FullBrushMapTool(TilemapData & data, const BrushFull &brush)
    : BaseMapTool(data)
    , m_brush(brush)
{

}

void FullBrushMapTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(BlockConnexions(pos));

    if(m_altButtonPressed)
    {
        checkTileOnMap(sf::Vector2u(pos.x - 1, pos.y));
        checkTileOnMap(sf::Vector2u(pos.x + 1, pos.y));
        checkTileOnMap(sf::Vector2u(pos.x, pos.y - 1));
        checkTileOnMap(sf::Vector2u(pos.x, pos.y + 1));
        checkTileOnMap(sf::Vector2u(pos.x - 1, pos.y - 1));
        checkTileOnMap(sf::Vector2u(pos.x + 1, pos.y - 1));
        checkTileOnMap(sf::Vector2u(pos.x - 1, pos.y + 1));
        checkTileOnMap(sf::Vector2u(pos.x + 1, pos.y + 1));
    }

    updateTile(pos, true);
}

void FullBrushMapTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    auto shape = std::find_if(m_connexions.begin(), m_connexions.end(), [pos](const auto & b){return b.pos == pos;});
    assert(shape != m_connexions.end());

    bool l = shape->left;
    bool r = shape->right;
    bool t = shape->top;
    bool d = shape->bottom;
    bool tl = shape->topLeft;
    bool tr = shape->topRight;
    bool dl = shape->bottomLeft;
    bool dr = shape->bottomRight;

    //full
    if(!l && !r && !t && !d)
        it->tile = m_brush.tile(TileShape::Full).toTileInfos();
    //3 sides
    else if(!l && !r && !t)
        it->tile = m_brush.tile(TileShape::Top3).toTileInfos();
    else if(!l && !r && !d)
        it->tile = m_brush.tile(TileShape::Down3).toTileInfos();
    else if(!l && !t && !d)
        it->tile = m_brush.tile(TileShape::Left3).toTileInfos();
    else if(!r && !t && !d)
        it->tile = m_brush.tile(TileShape::Right3).toTileInfos();
    //horizontal vertical
    else if(!l && !r)
        it->tile = m_brush.tile(TileShape::Vertical).toTileInfos();
    else if(!t && !d)
        it->tile = m_brush.tile(TileShape::Horizontal).toTileInfos();
    //corner with corner
    else if(!l && !t && !dr)
        it->tile = m_brush.tile(TileShape::TopLeftWithCorner).toTileInfos();
    else if(!l && !d && !tr)
        it->tile = m_brush.tile(TileShape::DownLeftWithCorner).toTileInfos();
    else if(!r && !t && !dl)
        it->tile = m_brush.tile(TileShape::TopRightWithCorner).toTileInfos();
    else if(!r && !d && !tl)
        it->tile = m_brush.tile(TileShape::DownRightWithCorner).toTileInfos();
    //corner without corner
    else if(!l && !t)
        it->tile = m_brush.tile(TileShape::TopLeft).toTileInfos();
    else if(!l && !d)
        it->tile = m_brush.tile(TileShape::DownLeft).toTileInfos();
    else if(!r && !t)
        it->tile = m_brush.tile(TileShape::TopRight).toTileInfos();
    else if(!r && !d)
        it->tile = m_brush.tile(TileShape::DownRight).toTileInfos();
    //one border with 2 corners
    else if(!l && !dr && !tr)
        it->tile = m_brush.tile(TileShape::LeftCorners2).toTileInfos();
    else if(!r && !dl && !tl)
        it->tile = m_brush.tile(TileShape::RightCorners2).toTileInfos();
    else if(!t && !dl && !dr)
        it->tile = m_brush.tile(TileShape::TopCorners2).toTileInfos();
    else if(!d && !tl && !tr)
        it->tile = m_brush.tile(TileShape::DownCorners2).toTileInfos();
    //one border with one corner
    else if(!l && !dr)
        it->tile = m_brush.tile(TileShape::LeftCornerDown).toTileInfos();
    else if(!l&& !tr)
        it->tile = m_brush.tile(TileShape::LeftCornerTop).toTileInfos();
    else if(!r && !dl)
        it->tile = m_brush.tile(TileShape::RightCornerTop).toTileInfos();
    else if(!r && !tl)
        it->tile = m_brush.tile(TileShape::RightCornerDown).toTileInfos();
    else if(!t && !dl)
        it->tile = m_brush.tile(TileShape::TopCornerDown).toTileInfos();
    else if(!t &&!dr)
        it->tile = m_brush.tile(TileShape::TopCornerTop).toTileInfos();
    else if(!d && !tl)
        it->tile = m_brush.tile(TileShape::DownCornerTop).toTileInfos();
    else if(!d && !tr)
        it->tile = m_brush.tile(TileShape::DownCornerDown).toTileInfos();
    //one border without corners
    else if(!l)
        it->tile = m_brush.tile(TileShape::Left).toTileInfos();
    else if(!r)
        it->tile = m_brush.tile(TileShape::Right).toTileInfos();
    else if(!t)
        it->tile = m_brush.tile(TileShape::Top).toTileInfos();
    else if(!d)
        it->tile = m_brush.tile(TileShape::Down).toTileInfos();
    //4 corners
    else if(!tl && !tr && !dl && !dr)
        it->tile = m_brush.tile(TileShape::QuadCorners).toTileInfos();
    //3 corners
    else if(!tl && !tr && !dl)
        it->tile = m_brush.tile(TileShape::TopLeftCorners3).toTileInfos();
    else if(!tl && !tr && !dr)
        it->tile = m_brush.tile(TileShape::TopRightCorners3).toTileInfos();
    else if(!tl && !dl && !dr)
        it->tile = m_brush.tile(TileShape::DownLeftCorners3).toTileInfos();
    else if(!tr && !dl && !dr)
        it->tile = m_brush.tile(TileShape::DownRightCorners3).toTileInfos();
    //2 corners diagonal
    else if(!tr && !dl)
        it->tile = m_brush.tile(TileShape::DiagonalTopRight).toTileInfos();
    else if(!tl && !dr)
        it->tile = m_brush.tile(TileShape::DiagonalTopLeft).toTileInfos();
    //2 corners side
    else if(!tr && !dr)
        it->tile = m_brush.tile(TileShape::RightCorners).toTileInfos();
    else if(!tl && !dl)
        it->tile = m_brush.tile(TileShape::LeftCorners).toTileInfos();
    else if(!tr && !tl)
        it->tile = m_brush.tile(TileShape::TopCorners).toTileInfos();
    else if(!dr && !dl)
        it->tile = m_brush.tile(TileShape::DownCorners).toTileInfos();
    //1 corner
    else if(!tr)
        it->tile = m_brush.tile(TileShape::TopRightCorner).toTileInfos();
    else if(!tl)
        it->tile = m_brush.tile(TileShape::TopLeftCorner).toTileInfos();
    else if(!dr)
        it->tile = m_brush.tile(TileShape::DownRightCorner).toTileInfos();
    else if(!dl)
        it->tile = m_brush.tile(TileShape::DownLeftCorner).toTileInfos();
    //empty
    else it->tile = m_brush.tile(TileShape::Empty).toTileInfos();

    if(updateNext)
    {
        updateTile(sf::Vector2u(pos.x - 1, pos.y), false);
        updateTile(sf::Vector2u(pos.x + 1, pos.y), false);
        updateTile(sf::Vector2u(pos.x, pos.y - 1), false);
        updateTile(sf::Vector2u(pos.x, pos.y + 1), false);
        updateTile(sf::Vector2u(pos.x - 1, pos.y - 1), false);
        updateTile(sf::Vector2u(pos.x + 1, pos.y - 1), false);
        updateTile(sf::Vector2u(pos.x - 1, pos.y + 1), false);
        updateTile(sf::Vector2u(pos.x + 1, pos.y + 1), false);
    }
}

void FullBrushMapTool::addTileConnexions(const BlockConnexions & block)
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
       if(block.top)
           itCurrent->top = true;
       if(block.bottom)
           itCurrent->bottom = true;
       if(block.topLeft)
           itCurrent->topLeft = true;
       if(block.topRight)
           itCurrent->topRight = true;
       if(block.bottomLeft)
           itCurrent->bottomLeft = true;
       if(block.bottomRight)
           itCurrent->bottomRight = true;
    }

    auto itLeft = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x - 1, pos.y)](const auto & b){return b.pos == pos;});
    auto itRight = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x + 1, pos.y)](const auto & b){return b.pos == pos;});
    auto itTop = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x, pos.y - 1)](const auto & b){return b.pos == pos;});
    auto itBottom = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x, pos.y + 1)](const auto & b){return b.pos == pos;});
    auto itTopLeft = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x - 1, pos.y - 1)](const auto & b){return b.pos == pos;});
    auto itTopRight = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x + 1, pos.y - 1)](const auto & b){return b.pos == pos;});
    auto itBottomLeft = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x - 1, pos.y + 1)](const auto & b){return b.pos == pos;});
    auto itBottomRight = std::find_if(m_connexions.begin(), m_connexions.end(), [pos = sf::Vector2u(pos.x + 1, pos.y + 1)](const auto & b){return b.pos == pos;});

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
    if(itTopLeft != m_connexions.end())
    {
        itCurrent->topLeft = true;
        itTopLeft->bottomRight = true;
    }
    if(itTopRight != m_connexions.end())
    {
        itCurrent->topRight = true;
        itTopRight->bottomLeft = true;
    }
    if(itBottomLeft != m_connexions.end())
    {
        itCurrent->bottomLeft = true;
        itBottomLeft->topRight = true;
    }
    if(itBottomRight != m_connexions.end())
    {
        itCurrent->bottomRight = true;
        itBottomRight->topLeft = true;
    }
}

void FullBrushMapTool::checkTileOnMap(const sf::Vector2u & pos)
{
    if(pos.x >= m_data.tiles.getSize().x || pos.y >= m_data.tiles.getSize().y)
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
    case TileShape::Empty:
        b.bottom = true;
        b.bottomLeft = true;
        b.bottomRight = true;
        b.left = true;
        b.right = true;
        b.top = true;
        b.topLeft = true;
        b.topRight = true;
        break;
    case TileShape::Left3:
        b.right = true;
        break;
    case TileShape::Right3:
        b.left = true;
        break;
    case TileShape::Top3:
        b.bottom = true;
        break;
    case TileShape::Down3:
        b.top = true;
        break;
    case TileShape::Horizontal:
        b.left = true;
        b.right = true;
        break;
    case TileShape::Vertical:
        b.top = true;
        b.bottom = true;
        break;
    case TileShape::TopLeft:
        b.bottom = true;
        b.bottomRight = true;
        b.right = true;
        break;
    case TileShape::TopRight:
        b.bottom = true;
        b.left = true;
        b.bottomLeft = true;
        break;
    case TileShape::DownLeft:
        b.right = true;
        b.top = true;
        b.topRight = true;
        break;
    case TileShape::DownRight:
        b.left = true;
        b.top = true;
        b.topLeft = true;
        break;
    case TileShape::Left:
        b.bottom = true;
        b.bottomRight = true;
        b.right = true;
        b.top = true;
        b.topRight = true;
        break;
    case TileShape::Right:
        b.bottom = true;
        b.bottomLeft = true;
        b.left = true;
        b.top = true;
        b.topLeft = true;
        break;
    case TileShape::Top:
        b.bottom = true;
        b.bottomLeft = true;
        b.bottomRight = true;
        b.left = true;
        b.right = true;
        break;
    case TileShape::Down:
        b.left = true;
        b.right = true;
        b.top = true;
        b.topLeft = true;
        b.topRight = true;
        break;
    case TileShape::QuadCorners:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        break;
    case TileShape::TopLeftCorners3:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomRight = true;
        break;
    case TileShape::TopRightCorners3:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        break;
    case TileShape::DownLeftCorners3:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.topRight = true;
        break;
    case TileShape::DownRightCorners3:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.topLeft = true;
        break;
    case TileShape::DiagonalTopLeft:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.topRight = true;
        break;
    case TileShape::DiagonalTopRight:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.topLeft = true;
        b.bottomRight = true;
        break;
    case TileShape::LeftCorners:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomRight = true;
        b.topRight = true;
        break;
    case TileShape::RightCorners:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.topLeft = true;
        break;
    case TileShape::TopCorners:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.bottomRight = true;
        break;
    case TileShape::DownCorners:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.topLeft = true;
        b.topRight = true;
        break;
    case TileShape::TopLeftCorner:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.bottomRight = true;
        b.topRight = true;
        break;
    case TileShape::TopRightCorner:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.bottomRight = true;
        b.topLeft = true;
        break;
    case TileShape::DownLeftCorner:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomRight = true;
        b.topLeft = true;
        b.topRight = true;
        break;
    case TileShape::DownRightCorner:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        b.topLeft = true;
        b.topRight = true;
        break;
    case TileShape::TopLeftWithCorner:
        b.bottom = true;
        b.right = true;
        break;
    case TileShape::TopRightWithCorner:
        b.bottom = true;
        b.left = true;
        break;
    case TileShape::DownLeftWithCorner:
        b.top = true;
        b.right = true;
        break;
    case TileShape::DownRightWithCorner:
        b.top = true;
        b.left = true;
        break;
    case TileShape::LeftCorners2:
        b.bottom = true;
        b.top = true;
        b.right = true;
        break;
    case TileShape::RightCorners2:
        b.bottom = true;
        b.top = true;
        b.left = true;
        break;
    case TileShape::TopCorners2:
        b.bottom = true;
        b.left = true;
        b.right = true;
        break;
    case TileShape::DownCorners2:
        b.top = true;
        b.left = true;
        b.right = true;
        break;
    case TileShape::LeftCornerTop:
        b.bottom = true;
        b.top = true;
        b.right = true;
        b.bottomRight = true;
        break;
    case TileShape::RightCornerTop:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.topLeft = true;
        break;
    case TileShape::TopCornerTop:
        b.bottom = true;
        b.left = true;
        b.right = true;
        b.bottomLeft = true;
        break;
    case TileShape::DownCornerTop:
        b.top = true;
        b.left = true;
        b.right = true;
        b.topRight = true;
        break;
    case TileShape::LeftCornerDown:
        b.bottom = true;
        b.top = true;
        b.right = true;
        b.topRight = true;
        break;
    case TileShape::RightCornerDown:
        b.bottom = true;
        b.top = true;
        b.left = true;
        b.bottomLeft = true;
        break;
    case TileShape::TopCornerDown:
        b.bottom = true;
        b.left = true;
        b.right = true;
        b.bottomRight = true;
        break;
    case TileShape::DownCornerDown:
        b.top = true;
        b.left = true;
        b.right = true;
        b.topLeft = true;
        break;
    default:
        break;
    }

    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    addTileConnexions(b);
}

void FullBrushMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
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

void FullBrushMapTool::beforeSelectionEnd()
{
    m_connexions.clear();
}

