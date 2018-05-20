#include "basemaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>

BaseMapTool::BaseMapTool(TilemapData &data)
    : m_data(data)
    , m_altButtonPressed(false)
    , m_onSelection(false)
    , m_mousePos(-1, -1)
{

}

void BaseMapTool::mouseMoveEvent(QMouseEvent * event)
{
    sf::Vector2i pos((event->x() + m_data.tileSize / 2) / m_data.tileSize, (event->y() + m_data.tileSize / 2) / m_data.tileSize);
    if(pos.x >= int(m_data.tiles.getSize().x))
        pos.x = -1;
    if(pos.y >= int(m_data.tiles.getSize().y))
        pos.y = -1;
    m_mousePos = sf::Vector2u(pos);

    if(m_onSelection)
        addTile(m_mousePos);
}

void BaseMapTool::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    m_onSelection = true;
    m_selection.clear();
    m_blocks.clear();

    mouseMoveEvent(event);
}

void BaseMapTool::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    onSelectionEnd();
}

void BaseMapTool::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Shift)
        m_altButtonPressed = true;
}

void BaseMapTool::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Shift)
        m_altButtonPressed = false;
}

void BaseMapTool::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    drawTiles(target);
    drawCursor(target, m_mousePos);
}

sf::Rect<unsigned int> BaseMapTool::selectionBounds() const
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

void BaseMapTool::addTile(const sf::Vector2u & pos)
{
    if(pos.x > m_data.tiles.getSize().x || pos.y > m_data.tiles.getSize().y)
        return;

    if(std::find(m_selection.begin(), m_selection.end(), pos) == m_selection.end())
        m_selection.push_back(pos);

    onAddTile(pos);
}

void BaseMapTool::onSelectionEnd()
{
    beforeSelectionEnd();

    m_onSelection = false;

    for(const auto b : m_blocks)
        m_data.tiles(b.pos) = b.tile;

    m_blocks.clear();
    m_selection.clear();
}

void BaseMapTool::drawTiles(sf::RenderTarget &target) const
{
    if(!m_texture.isValid())
        return;

    sf::VertexArray array(sf::Quads, m_blocks.size() * 4);
    sf::VertexArray backArray(sf::Quads, m_blocks.size() * 4);

    auto size = m_data.tileSize;
    auto delta = m_data.tileDelta;

    unsigned int tileInWidth((m_texture()->getSize().x + delta) / (size + delta));

    for(unsigned int i(0) ; i < m_blocks.size() ; i++)
    {
        const auto & b = m_blocks[i];
        auto x = b.tile.id % tileInWidth;
        auto y = b.tile.id / tileInWidth;

        drawQuad(&array[i * 4], sf::FloatRect((b.pos.x - 0.5f) * size, (b.pos.y - 0.5f) * size, size, size)
                , sf::FloatRect(x * (delta + size), y * (delta+ size), size, size));
        drawQuad(&backArray[i * 4], sf::FloatRect((b.pos.x - 0.5f) * size, (b.pos.y - 0.5f) * size, size, size)
                , sf::FloatRect(x * (delta + size), y * (delta+ size), size, size));
    }

    for(unsigned int i(0) ; i < backArray.getVertexCount() ; i++)
        backArray[i].color = sf::Color(255, 255, 255, 80);

    target.draw(backArray);
    target.draw(array, m_texture());
}

void BaseMapTool::drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const
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
