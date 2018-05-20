#include "brushvertical.h"
#include "UI/Tilemap/MapTool/verticalbrushmaptool.h"

BrushVertical::BrushVertical(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Vertical)
{

}

BrushVertical::BrushVertical(const QString & _name)
    : BrushTiled(_name, BrushType::Vertical)
{

}

std::unique_ptr<BaseMapTool> BrushVertical::getMapTool(TilemapData & data) const
{
    return std::make_unique<VerticalBrushMapTool>(data, *this);
}
