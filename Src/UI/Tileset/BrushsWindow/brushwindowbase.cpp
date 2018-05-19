#include "brushwindowbase.h"

BrushWindowBase::BrushWindowBase(QWidget *parent)
    : QWidget(parent)
    , m_delta(0)
    , m_size(0)
{

}

void BrushWindowBase::setTexture(const Texture & t)
{
    m_texture = t;
    onValueUpdate();
}

void BrushWindowBase::setDeltaTile(unsigned int delta)
{
    m_delta = delta;
    onValueUpdate();
}


void BrushWindowBase::setTileSize(unsigned int size)
{
    m_size = size;
    onValueUpdate();
}
