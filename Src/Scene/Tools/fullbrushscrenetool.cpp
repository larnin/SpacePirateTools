#include "fullbrushscrenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

FullBrushScreneTool::FullBrushScreneTool(TilesetLayer &layer, const BrushFull &brush)
    : BaseTilesetSceneTool(layer)
    , m_brush(brush)
{

}

void FullBrushScreneTool::onAddTile(const sf::Vector2u & pos)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});

    updateTile(pos, true);
}

void FullBrushScreneTool::updateTile(const sf::Vector2u & pos, bool updateNext)
{
    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        return;
    bool l = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x - 1, pos.y)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool r = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x + 1, pos.y)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool t = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x, pos.y - 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool d = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x, pos.y + 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool tl = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x - 1, pos.y - 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool tr = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x + 1, pos.y - 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool dl = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x - 1, pos.y + 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();
    bool dr = std::find_if(m_blocks.begin(), m_blocks.end(), [pos = sf::Vector2u(pos.x + 1, pos.y + 1)](const auto & b){return b.pos == pos;}) != m_blocks.end();

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

void FullBrushScreneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
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
