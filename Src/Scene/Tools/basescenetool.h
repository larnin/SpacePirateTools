#ifndef BASESCENETOOL_H
#define BASESCENETOOL_H

#include <sfml/Graphics/Drawable.hpp>
#include <QMouseEvent>
#include <QKeyEvent>

class BaseSceneTool : public sf::Drawable
{
public:
    virtual ~BaseSceneTool() = default;

    virtual void mouseMoveEvent(QMouseEvent * event) = 0;
    virtual void mousePressEvent(QMouseEvent * event) = 0;
    virtual void mouseReleaseEvent(QMouseEvent *) = 0;
    virtual void keyPressEvent(QKeyEvent * event) = 0;
    virtual void keyReleaseEvent(QKeyEvent * event) = 0;
};

#endif // BASESCENETOOL_H
