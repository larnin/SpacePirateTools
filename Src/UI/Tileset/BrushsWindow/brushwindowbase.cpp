#include "brushwindowbase.h"

BrushWindowBase::BrushWindowBase(QWidget *parent)
    : QWidget(parent)
{

}

void BrushWindowBase::setTexture(const Texture & t)
{
    m_texture = t;
    onTextureUpdate();
}
