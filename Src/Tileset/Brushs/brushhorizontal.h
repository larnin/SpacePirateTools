#ifndef BRUSHHORIZONTAL_H
#define BRUSHHORIZONTAL_H

#include "brushtiled.h"

class BrushHorizontal : public BrushTiled
{
public:
    BrushHorizontal(const QJsonObject & obj, const QString & _name);
    BrushHorizontal(const QString & _name);

    std::unique_ptr<BaseMapTool> getMapTool(TilemapData & data) const override;
};

#endif // BRUSHHORIZONTAL_H
