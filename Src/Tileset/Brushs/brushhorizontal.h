#ifndef BRUSHHORIZONTAL_H
#define BRUSHHORIZONTAL_H

#include "brushtiled.h"

class BrushHorizontal : public BrushTiled
{
public:
    BrushHorizontal(const QJsonObject & obj, const QString & _name);
    BrushHorizontal(const QString & _name);
};

#endif // BRUSHHORIZONTAL_H
