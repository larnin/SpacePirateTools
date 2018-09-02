#include "valuerenderertilemapcollider.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/VertexArray.hpp>

ValueRendererTilemapCollider::ValueRendererTilemapCollider(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase (node, value)
    , m_collider(dynamic_cast<ObjectValueTilemapCollider*>(value))
    , m_array(sf::Lines)
{
    loadTilemap();
}

void ValueRendererTilemapCollider::draw(sf::RenderTarget &) const
{

}

void ValueRendererTilemapCollider::drawGizmos(sf::RenderTarget & target) const
{
    if(!m_tilemap)
        return;

    target.draw(m_array, getTransform());
}

void ValueRendererTilemapCollider::update()
{
    if(*m_collider != m_currentCollider)
        loadTilemap();
}

void ValueRendererTilemapCollider::loadTilemap()
{
    if(m_collider->tilemapName != m_currentCollider.tilemapName)
    {
        if(!m_collider->tilemapName.isEmpty())
            m_tilemap = std::make_unique<TilemapData>(ProjectInfos::instance().fullFileName(m_collider->tilemapName, AssetType::Tilemap));
        else m_tilemap = {};
    }

    m_currentCollider = *m_collider;
    m_array.clear();

    if(!m_tilemap)
        return;

    sf::Vector2f topLeft(m_tilemap->tiles.getSize());
    topLeft *= m_collider->tileSize / -2.0f;
    topLeft += m_collider->offset;

    m_array.clear();

    for(unsigned int i(0) ; i < m_tilemap->tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_tilemap->tiles.getSize().y ; j++)
        {
            const auto tile = m_tilemap->tiles(sf::Vector2u(i, j));

            auto lineColor = sf::Color::White;
            if(ProjectInfos::instance().options().colliderLayers.size() > tile.collider.collisionLayer)
                lineColor = ProjectInfos::instance().options().colliderLayers[tile.collider.collisionLayer].color;
            tile.collider.drawShape(lineColor, topLeft + sf::Vector2f(i * m_collider->tileSize, j * m_collider->tileSize), m_collider->tileSize, m_array);
        }
}
