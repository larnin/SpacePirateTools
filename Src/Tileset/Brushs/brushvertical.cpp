#include "brushvertical.h"
#include "Scene/Tools/verticalbrushscenetool.h"

BrushVertical::BrushVertical(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Vertical)
{

}

BrushVertical::BrushVertical(const QString & _name)
    : BrushTiled(_name, BrushType::Vertical)
{

}

std::unique_ptr<BaseSceneTool> BrushVertical::getSceneTool(TilesetLayer & layer) const
{
    return std::make_unique<VerticalBrushSceneTool>(layer, *this);
}
