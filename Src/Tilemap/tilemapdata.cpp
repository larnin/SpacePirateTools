#include "tilemapdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

TilemapData::TilemapData(const sf::Vector2u & size, const TileInfos & defaultTile)
    : tiles(size, defaultTile)
    , tileSize(16)
    , tileDelta(0)
{

}

TilemapData::TilemapData(const QString & fileName)
    : tiles(sf::Vector2u(1, 1))
{
    load(fileName);
}

void TilemapData::save(const QString & fileName) const
{
    QJsonObject obj;

    QJsonArray tilesArray;
    for(const auto & t : tiles)
    {
        QJsonObject tileObj;
        tileObj.insert("id", int(t.id));
        tileObj.insert("c", int(t.collider.toInt()));
        tilesArray.append(tileObj);
    }
    obj.insert("tiles", tilesArray);
    obj.insert("texture", textureName);
    obj.insert("brush", brushName);
    obj.insert("sizeX", int(tiles.getSize().x));
    obj.insert("sizeY", int(tiles.getSize().y));
    obj.insert("tile", int(tileSize));
    obj.insert("delta", int(tileDelta));

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void TilemapData::load(const QString & fileName)
{
    QFile file(fileName);
    if(!file.exists())
        return;
    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &error));
    file.close();
    if(error.error != QJsonParseError::NoError)
        return;
    if(!doc.isObject())
        return;

    QJsonObject obj(doc.object());

    textureName = obj["texture"].toString();
    brushName = obj["brush"].toString();
    tileSize = obj["tile"].toInt();
    tileDelta = obj["delta"].toInt();

    sf::Vector2u size(obj["sizeX"].toInt(), obj["sizeY"].toInt());

    auto array = obj["tiles"].toArray();
    if(array.size() != int(size.x * size.y))
        return;

    tiles.resize(size);

    for(unsigned int i(0) ; i < size.x ; i++)
        for(unsigned int j(0) ; j < size.y ; j++)
        {
            QJsonObject o = array[i + j * size.x].toObject();
            TileInfos t;
            t.id = o["id"].toInt();
            t.collider.fromInt(o["c"].toInt());
            tiles(sf::Vector2u(i, j)) = t;
        }
}
