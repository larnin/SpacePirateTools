#include "copymaptool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <chrono>

std::vector<CopyMapTool::CopyValue> CopyMapTool::m_copyBuffer;

CopyMapTool::CopyMapTool(TilemapData & data)
    : BaseMapTool(data, true)
    , m_copyHolder(Event<CopyEvent>::connect([this](const auto & e){onCopy(e);}))
    , m_cutHolder(Event<CutEvent>::connect([this](const auto & e){onCut(e);}))
    , m_haveSelected(false)
    , m_onSelection(false)
{

}

void CopyMapTool::onAddTile(const sf::Vector2u & pos)
{
    if(!m_onSelection)
    {
        m_onSelection = true;
        m_startPos = pos;
    }
    m_endPos = pos;
}

void CopyMapTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = m_data.tileSize;

    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color(255, 255, 150, a));

    if(m_haveSelected || m_onSelection)
    {
        sf::Vector2u pos(std::min(m_startPos.x, m_endPos.x), std::min(m_startPos.y, m_endPos.y));
        sf::Vector2u s(std::abs(int(m_endPos.x) - int(m_startPos.x)) + 1, std::abs(int(m_endPos.y) - int(m_startPos.y)) + 1);
        shape.setSize(sf::Vector2f(s.x * size, s.y * size));
        shape.setPosition(sf::Vector2f((pos.x - 0.5f) * size, (pos.y - 0.5f) * size));
    }
    else shape.setPosition(sf::Vector2f((pos.x - 0.5f) * size, (pos.y - 0.5f) * size));

    target.draw(shape);
}

void CopyMapTool::beforeSelectionEnd()
{
    m_onSelection = false;
    m_haveSelected = true;
}

void CopyMapTool::onCopy(const CopyEvent &)
{
    if(m_onSelection || !m_haveSelected)
        return;

    m_copyBuffer.clear();

    for(unsigned int i(0) ; int(i) <= std::abs(int(m_endPos.x) - int(m_startPos.x)) ; i++)
        for(unsigned int j(0) ; int(j) <= std::abs(int(m_endPos.y) - int(m_startPos.y)) ; j++)
        {
            sf::Vector2u pos(i + std::min(m_startPos.x, m_endPos.x), j + std::min(m_startPos.y, m_endPos.y));
            m_copyBuffer.push_back({sf::Vector2u(i, j), m_data.tiles(pos)});
        }
}

void CopyMapTool::onCut(const CutEvent &)
{
    if(m_onSelection || !m_haveSelected)
        return;

    m_copyBuffer.clear();

    for(unsigned int i(0) ; int(i) <= std::abs(int(m_endPos.x) - int(m_startPos.x)) ; i++)
        for(unsigned int j(0) ; int(j) <= std::abs(int(m_endPos.y) - int(m_startPos.y)) ; j++)
        {
            sf::Vector2u pos(i + std::min(m_startPos.x, m_endPos.x), j + std::min(m_startPos.y, m_endPos.y));
            m_copyBuffer.push_back({sf::Vector2u(i, j), m_data.tiles(pos)});
            m_data.tiles(pos) = {};
        }
}
