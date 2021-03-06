#ifndef BRUSHWINDOWBASE_H
#define BRUSHWINDOWBASE_H

#include "ressource.h"
#include <QWidget>

class BrushWindowBase : public QWidget
{
public:
    virtual ~BrushWindowBase() = default;

    void setTexture(const Texture & t);
    void setDeltaTile(unsigned int delta);
    void setTileSize(unsigned int size);

protected:
    BrushWindowBase(QWidget * parent = nullptr);
    virtual void onValueUpdate() = 0;

    Texture m_texture;
    unsigned int m_delta;
    unsigned int m_size;
};

#endif // BRUSHWINDOWBASE_H
