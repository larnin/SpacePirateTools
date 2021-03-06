#ifndef BRUSHFULL_H
#define BRUSHFULL_H

#include "brushtiled.h"

class BrushFull : public BrushTiled
{
public:
    BrushFull(const QJsonObject & obj, const QString & _name);
    BrushFull(const QString & _name);

    std::unique_ptr<BaseMapTool> getMapTool(TilemapData & data) const override;
};

#endif // BRUSHFULL_H
