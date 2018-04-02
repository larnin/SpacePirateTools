#include "brushvertical.h"

BrushVertical::BrushVertical(const QJsonObject & obj, const QString & _name)
    : BrushTiled(obj, _name, BrushType::Vertical)
{

}

BrushVertical::BrushVertical(const QString & _name)
    : BrushTiled(_name, BrushType::Vertical)
{

}
