#include "basetilesetscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <algorithm>

constexpr Qt::Modifier altKey(Qt::SHIFT);

BaseTilesetSceneTool::BaseTilesetSceneTool(TilesetLayer &layer)
    : m_layer(layer)
    , m_altButtonPressed(false)
    , m_onSelection(false)
    , m_mousePos(-1, -1)
{

}

void BaseTilesetSceneTool::mouseMoveEvent(QMouseEvent * event)
{
    auto size = ProjectInfos::instance().options().tileSize;
    sf::Vector2i pos((event->x() + size / 2) / size, (event->y() + size / 2) / size);
    if(pos.x >= int(m_layer.size().x))
        pos.x = -1;
    if(pos.y >= int(m_layer.size().y))
        pos.y = -1;
    m_mousePos = sf::Vector2u(pos);

    if(m_onSelection)
        addTile(m_mousePos);
}

void BaseTilesetSceneTool::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    m_onSelection = true;
    m_selection.clear();
    m_blocks.clear();

    mouseMoveEvent(event);
}

void BaseTilesetSceneTool::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    onSelectionEnd();
}

void BaseTilesetSceneTool::keyPressEvent(QKeyEvent *)
{

}

void BaseTilesetSceneTool::keyReleaseEvent(QKeyEvent *)
{

}

void BaseTilesetSceneTool::addTile(const sf::Vector2u & pos)
{
    if(pos.x > m_layer.size().x || pos.y > m_layer.size().y)
        return;

    if(std::find(m_selection.begin(), m_selection.end(), pos) == m_selection.end())
        m_selection.push_back(pos);

    onAddTile(pos);
}

void BaseTilesetSceneTool::onSelectionEnd()
{
    m_onSelection = false;

    std::vector<sf::Vector2u> pos;
    std::vector<TileInfos> tiles;
    for(const auto b : m_blocks)
    {
        pos.push_back(b.pos);
        tiles.push_back(b.tile);
    }

    m_layer.setTiles(pos, tiles);

    m_blocks.clear();
    m_selection.clear();
}

void BaseTilesetSceneTool::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    drawTiles(target);
    drawCursor(target, m_mousePos);
}

sf::Rect<unsigned int> BaseTilesetSceneTool::selectionBounds() const
{
    if(m_selection.empty())
        return sf::Rect<unsigned int>(0, 0, 0, 0);

    auto minPos = m_selection[0];
    auto maxPos = m_selection[0];

    for(const auto & p : m_selection)
    {
        minPos = sf::Vector2u(std::min(p.x, minPos.x), std::min(p.y, minPos.y));
        maxPos = sf::Vector2u(std::max(p.x, maxPos.x), std::max(p.y, maxPos.y));
    }

    return sf::Rect<unsigned int>(minPos, maxPos - minPos + sf::Vector2u(1, 1));
}

void BaseTilesetSceneTool::drawTiles(sf::RenderTarget &target) const
{
    if(!m_layer.texture().isValid())
        return;

    sf::VertexArray array(sf::Quads, m_blocks.size() * 4);

    auto size = ProjectInfos::instance().options().tileSize;
    auto delta = ProjectInfos::instance().options().delta;

    unsigned int tileInWidth((m_layer.texture()->getSize().x + delta) / (size + delta));

    for(unsigned int i(0) ; i < m_blocks.size() ; i++)
    {
        const auto & b = m_blocks[i];
        auto x = b.tile.id % tileInWidth;
        auto y = b.tile.id / tileInWidth;

        drawQuad(&array[i * 4], sf::FloatRect((b.pos.x - 0.5f) * size, (b.pos.y - 0.5f) * size, size, size)
                , sf::FloatRect(x * (delta + size), y * (delta+ size), size, size));
    }

    target.draw(array, m_layer.texture()());
}

void BaseTilesetSceneTool::drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const
{
    quad[0].position = sf::Vector2f(rect.left, rect.top);
    quad[0].texCoords = sf::Vector2f(texRect.left, texRect.top);

    quad[1].position = sf::Vector2f(rect.left + rect.width, rect.top);
    quad[1].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top);

    quad[2].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    quad[2].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top + texRect.height);

    quad[3].position = sf::Vector2f(rect.left, rect.top + rect.height);
    quad[3].texCoords = sf::Vector2f(texRect.left, texRect.top + texRect.height);
}
