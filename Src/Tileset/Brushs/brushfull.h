#ifndef BRUSHFULL_H
#define BRUSHFULL_H

#include "brushtiled.h"

class BrushFull : public BrushTiled
{
public:
    BrushFull(const QJsonObject & obj, const QString & _name);
    BrushFull(const QString & _name);
};

#endif // BRUSHFULL_H