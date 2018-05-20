#include "tilemaprenderer.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>

TilemapRenderer::TilemapRenderer()
    : m_data(nullptr)
{

}

TilemapRenderer::TilemapRenderer(TilemapData &data)
    : m_data(&data)
{

}

void TilemapRenderer::drawTiles(sf::RenderTarget & target)const
{
    if(!m_texture.isValid() || m_data == nullptr || m_data->tileSize == 0)
        return;

    unsigned int tiles(0);
    for(const auto & t : m_data->tiles)
        if(t.id != 0)
            tiles++;

    sf::VertexArray array(sf::Quads, tiles * 4);

    auto tileByRow = (m_texture->getSize().x + m_data->tileDelta) / (m_data->tileSize + m_data->tileDelta);

    unsigned int index(0);

    for(unsigned int i(0) ; i < m_data->tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_data->tiles.getSize().y ; j++)
        {
            unsigned int id(m_data->tiles({i, j}).id);
            if(id == 0)
                continue;
            unsigned int x(id % tileByRow);
            unsigned int y(id / tileByRow);

            drawQuad(&array[index * 4], sf::FloatRect(i * m_data->tileSize - m_data->tileSize / 2.0f, j * m_data->tileSize - m_data->tileSize / 2.0f, m_data->tileSize, m_data->tileSize)
                                , sf::FloatRect(x * (m_data->tileSize + m_data->tileDelta), y * (m_data->tileSize + m_data->tileDelta), m_data->tileSize, m_data->tileSize));

            index++;
        }

    target.draw(array, sf::RenderStates(m_texture()));
}

void TilemapRenderer::drawColliders(sf::RenderTarget & target) const
{
    if(m_data == nullptr)
        return;

    sf::VertexArray array(sf::Lines);

    auto list = ProjectInfos::instance().options().colliderLayers;

    for(unsigned int i(0) ; i < m_data->tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_data->tiles.getSize().y ; j++)
        {
            const auto & collider(m_data->tiles({i, j}).collider);
            sf::Color color = collider.collisionLayer < list.size() ? list[collider.collisionLayer].color : list[0].color;

            collider.drawShape(color, sf::Vector2f(i * m_data->tileSize, j * m_data->tileSize), m_data->tileSize, array);
        }

    target.draw(array);
}

void TilemapRenderer::drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect)
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
