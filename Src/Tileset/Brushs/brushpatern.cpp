#include "brushpatern.h"
#include "UI/Tileset/BrushsWindow/brushwindowpatern.h"
#include "UI/Tilemap/MapTool/paternmaptool.h"
#include <QJsonArray>
#include <cassert>

BrushPatern::BrushPatern(const QJsonObject & obj, const QString & _name)
    : BrushBase(BrushType::Pattern, _name)
{
    m_size = sf::Vector2u(obj["sx"].toInt(), obj["sy"].toInt());

    auto tileIt = obj.find("tiles");
    if(tileIt != obj.end() && tileIt->isArray())
    {
        QJsonArray array = tileIt->toArray();
        if(array.size() == int(m_size.x * m_size.y))
        {
            for(const auto & v : array)
            {
                auto obj = v.toObject();
                m_tiles.emplace_back(TileCollider(obj["c"].toInt()), obj["id"].toInt());
            }
        }
        else m_tiles.resize(m_size.x * m_size.y, {TileCollider(0), 0});
    }
}

BrushPatern::BrushPatern(const QString & _name, const sf::Vector2u &size, TileFullInfos defaultTile)
    : BrushBase(BrushType::Pattern, _name)
    , m_size(0, 0)
{
    setSize(size, defaultTile);
}

void BrushPatern::setSize(const sf::Vector2u & size, TileFullInfos defaultTile)
{
    std::vector<TileFullInfos> newVect(size.x * size.y, defaultTile);

    for(unsigned int i(0) ; i < m_size.x ; i++)
        for(unsigned int j(0) ; j < m_size.y; j++)
        {
            if(i >= size.x || j >= size.y)
                continue;

            newVect[i + j * size.x] = m_tiles[posToIndex({i, j})];
        }

    m_tiles = newVect;
    m_size = size;
}

void BrushPatern::onSave(QJsonObject & obj) const
{
    obj.insert("sx", int(m_size.x));
    obj.insert("sy", int(m_size.y));

    QJsonArray array;
    for(const auto & tile : m_tiles)
    {
        QJsonObject tObj;
        tObj.insert("c", int(tile.collider.toInt()));
        tObj.insert("id", int(tile.id));
        array.append(tObj);
    }

    obj.insert("tiles", array);
}

TileFullInfos & BrushPatern::operator[](const sf::Vector2u & pos)
{
    return m_tiles[posToIndex(pos)];
}

TileFullInfos const & BrushPatern::operator [](const sf::Vector2u & pos) const
{
    return m_tiles[posToIndex(pos)];
}

unsigned int BrushPatern::posToIndex(const sf::Vector2u & pos) const
{
    assert(pos.x < m_size.x && pos.y < m_size.y);

    return pos.x + pos.y * m_size.x;
}

 BrushWindowBase* BrushPatern::getBrushWindows()
 {
     return new BrushWindowPatern(this);
 }

 std::unique_ptr<BaseMapTool> BrushPatern::getMapTool(TilemapData & data) const
 {
     return std::make_unique<PaternMapTool>(data, *this);
 }
