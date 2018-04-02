#include "brushhorizontal.h"

BrushHorizontal::BrushHorizontal(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Horizontal)
{

}

BrushHorizontal::BrushHorizontal(const QString & _name)
    : BrushTiled(_name, BrushType::Horizontal)
{

}
