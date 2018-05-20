#include "brushrandom.h"
#include "UI/Tileset/BrushsWindow/brushwindowrandom.h"
#include "UI/Tilemap/MapTool/randommaptool.h"
#include <QJsonArray>

BrushRandom::BrushRandom(const QJsonObject & obj, const QString & _name)
    : BrushBase(BrushType::Random, _name)
{
    collider.fromInt(obj["collider"].toInt());

    auto itTiles = obj.find("tiles");
    if(itTiles != obj.end() && itTiles->isArray())
    {
        for(const auto & obj : itTiles->toArray())
        {
            auto tile = obj.toObject();
            push_back({static_cast<unsigned int>(tile["id"].toInt()), static_cast<float>(tile["p"].toDouble())});
        }
    }
}

BrushRandom::BrushRandom(const QString & _name)
    : BrushBase(BrushType::Random, _name)
    , collider(0)
{
    push_back({0, 1});
}

void BrushRandom::onSave(QJsonObject & obj) const
{
    obj.insert("collider", int(collider.toInt()));

    QJsonArray array;
    for(const auto & item : *this)
    {
        QJsonObject tile;
        tile.insert("id", int(item.id));
        tile.insert("p", item.probability);
        array.append(tile);
    }

    obj.insert("tiles", array);
}

BrushWindowBase* BrushRandom::getBrushWindows()
{
    return new BrushWindowRandom(this);
}

std::unique_ptr<BaseMapTool> BrushRandom::getMapTool(TilemapData & data) const
{
    return std::make_unique<RandomMapTool>(data, *this);
}
