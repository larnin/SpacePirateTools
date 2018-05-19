#include "brushsquare.h"
//#include "Scene/Tools/squarebrushscenetool.h"

BrushSquare::BrushSquare(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Square)
{

}

BrushSquare::BrushSquare(const QString & _name)
    : BrushTiled(_name, BrushType::Square)
{

}

/*std::unique_ptr<BaseSceneTool> BrushSquare::getSceneTool(TilesetLayer & layer) const
{
    return std::make_unique<SquareBrushSceneTool>(layer, *this);
}*/
