#include "brushhorizontal.h"
#include "Scene/Tools/horizontalbrushscenetool.h"

BrushHorizontal::BrushHorizontal(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Horizontal)
{

}

BrushHorizontal::BrushHorizontal(const QString & _name)
    : BrushTiled(_name, BrushType::Horizontal)
{

}

std::unique_ptr<BaseSceneTool> BrushHorizontal::getSceneTool(TilesetLayer & layer) const
{
    return std::make_unique<HorizontalBrushSceneTool>(layer, *this);
}
