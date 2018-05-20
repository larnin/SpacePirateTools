#ifndef BRUSHVERTICAL_H
#define BRUSHVERTICAL_H

#include "brushtiled.h"

class BrushVertical : public BrushTiled
{
public:
    BrushVertical(const QJsonObject & obj, const QString & _name);
    BrushVertical(const QString & _name);

    std::unique_ptr<BaseMapTool> getMapTool(TilemapData & data) const override;
};

#endif // BRUSHVERTICAL_H
