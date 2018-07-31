#ifndef SCENETOOLSBASE_H
#define SCENETOOLSBASE_H

#include "Scene/scenenode.h"
#include <SFML/Graphics/Drawable.hpp>
#include <QMouseEvent>

class SceneToolsBase : public sf::Drawable
{
public:
    SceneToolsBase(SceneNode * node);

    virtual bool mouseMoveEvent(QMouseEvent * event) = 0;
    virtual bool mousePressEvent(QMouseEvent * event) = 0;
    virtual bool mouseReleaseEvent(QMouseEvent * event) = 0;

private:
    SceneNode * m_node;
};

#endif // SCENETOOLSBASE_H
