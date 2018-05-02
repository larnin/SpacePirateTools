#include "brushfull.h"
#include "Scene/Tools/fullbrushscrenetool.h"

BrushFull::BrushFull(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Full)
{

}

BrushFull::BrushFull(const QString & _name)
    : BrushTiled(_name, BrushType::Full)
{

}

std::unique_ptr<BaseSceneTool> BrushFull::getSceneTool(TilesetLayer & layer) const
{
    return std::make_unique<FullBrushScreneTool>(layer, *this);
}
