#include "randomscenetool.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

RandomSceneTool::RandomSceneTool(TilesetLayer &layer, const BrushRandom &brush)
    : BaseTilesetSceneTool(layer)
    , m_brush(brush)
{
    assert(!m_brush.empty());

    std::vector<float> weights;
    for(const auto & b : m_brush)
        weights.push_back(b.probability);
    m_distrib = {weights.begin(), weights.end()};
}

void RandomSceneTool::onAddTile(const sf::Vector2u & pos)
{
    auto id = m_brush[m_distrib(m_rand)].id;
    TileInfos tile{id, m_brush.collider};

    auto it = std::find_if(m_blocks.begin(), m_blocks.end(), [pos](const auto & b){return b.pos == pos;});
    if(it == m_blocks.end())
        m_blocks.push_back({pos, tile});
    else it->tile = tile;
}

void RandomSceneTool::drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const
{
    auto t = std::chrono::system_clock::now().time_since_epoch();
    auto s = std::chrono::duration_cast<std::chrono::milliseconds>(t).count();
    float a = std::sin(s / 500.0) * 30 + 150;
    auto size = ProjectInfos::instance().options().tileSize;
    auto delta = ProjectInfos::instance().options().delta;
    auto id(m_brush[0].id);

    sf::RectangleShape shape(sf::Vector2f(size, size));
    shape.setFillColor(sf::Color(255, 255, 255, a));

    shape.setPosition(sf::Vector2f((pos.x - 0.5f) * size, (pos.y - 0.5f) * size));

    target.draw(shape);

    if(!m_layer.texture().isValid())
        return;

    unsigned int tileInWidth((m_layer.texture()->getSize().x + delta) / (size + delta));

    auto x = id % tileInWidth;
    auto y = id / tileInWidth;

    sf::Sprite sprite(*m_layer.texture(), sf::IntRect(x * (delta + size), y * (delta+ size), size, size));
    sprite.setPosition((pos.x - 0.5f) * size, (pos.y - 0.5f) * size);
    sprite.setColor(sf::Color(255, 255, 255, a));

    target.draw(sprite);
}
