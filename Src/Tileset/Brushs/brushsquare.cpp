#include "brushsquare.h"

BrushSquare::BrushSquare(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Square)
{

}

BrushSquare::BrushSquare(const QString & _name)
    : BrushTiled(_name, BrushType::Square)
{

}

std::unique_ptr<BaseMapTool> BrushSquare::getMapTool(TilemapData & data) const
{
    return {};
}
