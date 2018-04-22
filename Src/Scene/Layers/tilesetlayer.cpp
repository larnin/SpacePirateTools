#include "tilesetlayer.h"
#include "ProjectInfos/projectinfos.h"
#include <QJsonArray>

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
            }
        }
    }

    setTextureName(obj["texture"].toString());
    brushName = obj["brush"].toString();
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

void TilesetLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void TilesetLayer::setSize(const sf::Vector2u & size)
{
    m_tiles.resize(size);
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
}
