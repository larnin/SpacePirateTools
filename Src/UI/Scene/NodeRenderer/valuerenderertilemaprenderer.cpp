#include "valuerenderertilemaprenderer.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/Tilemap/tilemaprenderer.h"

ValueRendererTilemapRenderer::ValueRendererTilemapRenderer(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase(node, value)
    , m_data(dynamic_cast<ObjectValueTilemapRenderer*>(value))
    , m_array(sf::Quads)
{

}

void ValueRendererTilemapRenderer::draw(sf::RenderTarget & target) const
{
    if(!m_tilemap || !m_texture.isValid())
        return;

    sf::RenderStates states;
    states.texture = m_texture();
    states.transform = getTransform();
    target.draw(m_array, states);
}

void ValueRendererTilemapRenderer::drawGizmos(sf::RenderTarget &) const
{

}

void ValueRendererTilemapRenderer::update()
{
    if(*m_data != m_currentData)
        loadTilemap();
}

void ValueRendererTilemapRenderer::loadTilemap()
{
    if(m_data->tilemapName != m_currentData.tilemapName)
    {
        if(!m_data->tilemapName.isEmpty())
             m_tilemap = std::make_unique<TilemapData>(ProjectInfos::instance().fullFileName(m_data->tilemapName, AssetType::Tilemap));
        else m_tilemap = {};
    }

    if(m_data->textureName != m_currentData.textureName)
    {
        if(!m_data->textureName.isEmpty())
            m_texture.load(ProjectInfos::instance().fullFileName(m_data->textureName, AssetType::Image).toStdString());
        else m_texture.clear();
    }

    m_currentData = *m_data;
    m_array.clear();

    if(!m_tilemap || !m_texture.isValid())
        return;

    unsigned int tiles(0);
    for(const auto & t : m_tilemap->tiles)
        if(t.id != 0)
            tiles++;

    m_array.resize(tiles * 4);

    auto tileByRow = (m_texture->getSize().x + m_data->tileDelta) / (m_data->tileSize + m_data->tileDelta);

    unsigned int index(0);
    for(unsigned int i(0) ; i < m_tilemap->tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_tilemap->tiles.getSize().y ; j++)
        {
            const auto & tile = m_tilemap->tiles(sf::Vector2u(i, j));
            if(tile.id == 0)
                continue;

            sf::Vector2f pos(m_tilemap->tiles.getSize().x, m_tilemap->tiles.getSize().y);
            pos *= m_data->tileSize / -2.0f;
            pos += sf::Vector2f(i, j) * static_cast<float>(m_data->tileSize);
            pos += m_data->offset;
            pos -= sf::Vector2f(m_data->tileSize, m_data->tileSize) / 2.0f;

            unsigned int x(tile.id % tileByRow);
            unsigned int y(tile.id / tileByRow);

            TilemapRenderer::drawQuad(&m_array[index * 4], sf::FloatRect(pos.x, pos.y, m_data->tileSize, m_data->tileSize),
                    sf::FloatRect(x * (m_data->tileSize + m_data->tileDelta), y * (m_data->tileSize + m_data->tileDelta), m_data->tileSize, m_data->tileSize));

            index++;
        }
}
