#include "brushfull.h"
#include "UI/Tilemap/MapTool/fullbrushmaptool.h"

BrushFull::BrushFull(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Full)
{

}

BrushFull::BrushFull(const QString & _name)
    : BrushTiled(_name, BrushType::Full)
{

}

std::unique_ptr<BaseMapTool> BrushFull::getMapTool(TilemapData & data) const
{
    return std::make_unique<FullBrushMapTool>(data, *this);
}
