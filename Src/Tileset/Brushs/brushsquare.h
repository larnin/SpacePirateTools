#ifndef BRUSHSQUARE_H
#define BRUSHSQUARE_H

#include "brushtiled.h"

class BrushSquare : public BrushTiled
{
public:
    BrushSquare(const QJsonObject & obj, const QString & _name);
    BrushSquare(const QString & _name);
};

#endif // BRUSHSQUARE_H
