#ifndef BRUSHVERTICAL_H
#define BRUSHVERTICAL_H

#include "brushtiled.h"

class BrushVertical : public BrushTiled
{
public:
    BrushVertical(const QJsonObject & obj, const QString & _name);
    BrushVertical(const QString & _name);
};

#endif // BRUSHVERTICAL_H
