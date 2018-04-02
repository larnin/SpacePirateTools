#ifndef BRUSHWINDOWBASE_H
#define BRUSHWINDOWBASE_H

#include "ressource.h"
#include <QWidget>

class BrushWindowBase : public QWidget
{
public:
    virtual ~BrushWindowBase() = default;

    void setTexture(const Texture & t);

protected:
    BrushWindowBase(QWidget * parent = nullptr);
    virtual void onTextureUpdate() = 0;

    Texture m_texture;
};

#endif // BRUSHWINDOWBASE_H
