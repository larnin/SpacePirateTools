#ifndef SCENETOOLBASE_H
#define SCENETOOLBASE_H

#include "Scene/scenenode.h"
#include <SFML/Graphics/Drawable.hpp>
#include <QMouseEvent>

class SceneToolBase : public sf::Drawable
{
public:
    SceneToolBase(SceneNode * node);

    virtual bool mouseMoveEvent(QMouseEvent * event) = 0;
    virtual bool mousePressEvent(QMouseEvent * event) = 0;
    virtual bool mouseReleaseEvent(QMouseEvent * event) = 0;

protected:
    SceneNode * m_node;
};

#endif // SCENETOOLBASE_H
