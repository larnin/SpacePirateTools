#ifndef BASESCENETOOL_H
#define BASESCENETOOL_H

#include "Scene/Layers/layerbase.h"
#include <sfml/Graphics/Drawable.hpp>
#include <QMouseEvent>
#include <QKeyEvent>

class BaseSceneTool : public sf::Drawable
{
public:
    inline BaseSceneTool(const LayerBase & layer) : m_layer(layer) {}

    virtual ~BaseSceneTool() = default;

    virtual void mouseMoveEvent(QMouseEvent * event) = 0;
    virtual void mousePressEvent(QMouseEvent * event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
    virtual void keyPressEvent(QKeyEvent * event) = 0;
    virtual void keyReleaseEvent(QKeyEvent * event) = 0;

    inline const LayerBase & layer() const { return m_layer;}

private:
    const LayerBase & m_layer;
};

#endif // BASESCENETOOL_H
