#include "tilesetlayer.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/Scene/LayerToolWindow/tilesetlayertoolwindow.h"
#include "UI/Scene/centralscenewindow.h"
#include "Scene/Tools/copytilesetscenetool.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <QJsonArray>

const sf::Color gizmosColor(sf::Color::Green);

TilesetLayer::TilesetLayer(const QString &name, const QJsonObject &obj)
    : LayerBase(LayerType::Tilemap, name)
    , m_tiles(sf::Vector2u(obj["sx"].toInt(), obj["sy"].toInt()))
{
    auto itArray = obj.find("tiles");
    if(itArray != obj.end() && itArray->isArray())
    {
        QJsonArray array = itArray->toArray();
        if(array.size() == int(m_tiles.getSize().x * m_tiles.getSize().y))
        {
            unsigned int index(0);
            for(TileInfos & v : m_tiles)
            {
                auto item = array[index].toArray();
                v.id = item[0].toInt();
                v.collider.fromInt(item[1].toInt());
                index++;
            }
        }
    }

    setTextureName(obj["texture"].toString());
    brushName = obj["brush"].toString();

    updateRender();
}

TilesetLayer::TilesetLayer(const QString & name, const sf::Vector2u &size)
    : LayerBase(LayerType::Tilemap, name)
    , m_tiles(size)
{

}

void TilesetLayer::onSave(QJsonObject & obj) const
{
    obj.insert("sx", int(m_tiles.getSize().x));
    obj.insert("sy", int(m_tiles.getSize().y));

    QJsonArray array;
    for(const auto & v : m_tiles)
    {
        QJsonArray tile;
        tile.append(int(v.id));
        tile.append(int(v.collider.toInt()));
        array.append(tile);
    }
    obj.insert("tiles", array);

    obj.insert("texture", m_textureName);
    obj.insert("brush", brushName);
}


void TilesetLayer::setTile(const sf::Vector2u & pos, const TileInfos & tile)
{
    m_tiles(pos) = tile;
    updateRender();
}

void TilesetLayer::setTiles(const std::vector<sf::Vector2u> & pos, const std::vector<TileInfos> & tile)
{
    assert(pos.size() == tile.size());

    for(unsigned int i(0) ; i < pos.size() ; i++)
        m_tiles(pos[i]) = tile[i];

    updateRender();
}

void TilesetLayer::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    if(!hidden && m_texture.isValid())
        target.draw(m_tileArray, sf::RenderStates(m_texture()));

    if(showGizmos)
        target.draw(m_gizmoArray);
}

void TilesetLayer::setSize(const sf::Vector2u & size)
{
    m_tiles.resize(size);

    updateRender();
}

QWidget * TilesetLayer::getToolWindow(CentralSceneWindow * window)
{
    return new TilesetLayerToolWindow(window, *this);
}

std::unique_ptr<BaseSceneTool> TilesetLayer::getSelectionTool()
{
    return std::make_unique<CopyTilesetSceneTool>(*this);
}

void TilesetLayer::setTextureName(const QString & name)
{
    if(name.isEmpty())
        m_texture = Texture();
    else
    {
        AssetType img = AssetType::Image;
        QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(img) + "/" + name/* + "." + assetTypeExtension(img)*/;

        m_texture = Texture(fullName.toStdString());
    }

    m_textureName = name;

    updateRender();
}

void TilesetLayer::updateRender()
{
    updateTileRender();
    updateGizmoRender();
}

void TilesetLayer::updateTileRender()
{
    m_tileArray.clear();
    m_tileArray.setPrimitiveType(sf::Quads);

    if(!m_texture.isValid())
        return;

    unsigned int count = renderableTileCount();
    m_tileArray.resize(count * 4);

    unsigned int index(0);
    unsigned int tileSize = ProjectInfos::instance().options().tileSize;
    unsigned int delta = ProjectInfos::instance().options().delta;

    unsigned int tileByRow = (m_texture->getSize().x + delta) / (tileSize + delta);

    for(unsigned int i(0) ; i < m_tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_tiles.getSize().y ; j++)
        {
            unsigned int id(m_tiles({i, j}).id);
            if(id == 0)
                continue;
            unsigned int x(id % tileByRow);
            unsigned int y(id / tileByRow);

            drawQuad(&m_tileArray[index * 4], sf::FloatRect(i * tileSize - tileSize / 2.0f, j * tileSize - tileSize / 2.0f, tileSize, tileSize)
                    , sf::FloatRect(x * (tileSize + delta), y * (tileSize + delta), tileSize, tileSize));

            index++;
        }
}

void TilesetLayer::updateGizmoRender()
{
    auto size = ProjectInfos::instance().options().tileSize;

    m_gizmoArray.clear();
    m_gizmoArray.setPrimitiveType(sf::Lines);

    for(unsigned int i(0) ; i < m_tiles.getSize().x ; i++)
        for(unsigned int j(0) ; j < m_tiles.getSize().y ; j++)
            m_tiles({i, j}).collider.drawShape(gizmosColor, sf::Vector2f(i * size, j * size), size, m_gizmoArray);
}

unsigned int TilesetLayer::renderableTileCount() const
{
    unsigned int count(0);

    for(auto tile : m_tiles)
        if(tile.id > 0)
            count ++;
    return count;
}

void TilesetLayer::drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const
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
