#include "squarebrushscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

SquareBrushSceneTool::SquareBrushSceneTool(TilesetLayer &layer, const BrushSquare &brush)
    : BaseTilesetSceneTool(layer)
    , m_brush(brush)
{

}

void SquareBrushSceneTool::onAddTile(const sf::Vector2u & pos)
{
    m_blocks.clear();
    auto bounds = selectionBounds();

    if(bounds.width == 1 && bounds.height == 1)
        m_blocks.push_back({pos, m_brush.tile(TileShape::Full).toTileInfos()});
    else if(bounds.width == 1)
    {
        for(unsigned int i(0) ; i < bounds.height ; i++)
        {
            TileInfos t;
            if(i == 0)
                t = m_brush.tile(TileShape::Top3).toTileInfos();
            else if(i == bounds.height - 1)
                t = m_brush.tile(TileShape::Down3).toTileInfos();
            else t = m_brush.tile(TileShape::Vertical).toTileInfos();

            m_blocks.push_back({sf::Vector2u(bounds.left, i + bounds.top), t});
        }
    }
    else if(bounds.height == 1)
    {
        for(unsigned int i(0) ; i < bounds.width ; i++)
        {
            TileInfos t;
            if(i == 0)
                t = m_brush.tile(TileShape::Left3).toTileInfos();
            else if(i == bounds.width - 1)
                t = m_brush.tile(TileShape::Right3).toTileInfos();
            else t = m_brush.tile(TileShape::Horizontal).toTileInfos();

            m_blocks.push_back({sf::Vector2u(i + bounds.left, bounds.top), t});
        }
    }
    else
    {
        for(unsigned int i(0) ; i < bounds.width ; i++)
            for(unsigned int j(0) ; j < bounds.height ; j++)
            {
                TileInfos t;
                if(i == 0 && j == 0)
                    t = m_brush.tile(TileShape::TopLeft).toTileInfos();
                else if(i == bounds.width - 1 && j == 0)
                    t = m_brush.tile(TileShape::TopRight).toTileInfos();
                else if(i == bounds.width - 1 && j == bounds.height - 1)
                    t = m_brush.tile(TileShape::DownRight).toTileInfos();
                else if(i == 0 && j == bounds.height - 1)
                    t = m_brush.tile(TileShape::DownLeft).toTileInfos();
                else if(i == 0)
                    t = m_brush.tile(TileShape::Left).toTileInfos();
                else if(j == 0)
                    t = m_brush.tile(TileShape::Top).toTileInfos();
                else if(i == bounds.width - 1)
                    t = m_brush.tile(TileShape::Right).toTileInfos();
                else if(j == bounds.height - 1)
                    t = m_brush.tile(TileShape::Down).toTileInfos();
                else t = m_brush.tile(TileShape::Empty).toTileInfos();

                m_blocks.push_back({sf::Vector2u(i + bounds.left, j + bounds.top), t});
            }
    }
}

void SquareBrushSceneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
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
