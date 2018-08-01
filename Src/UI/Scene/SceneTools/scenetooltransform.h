#ifndef SCENETOOLTRANSFORM_H
#define SCENETOOLTRANSFORM_H

#include "scenetoolbase.h"

class SceneToolTransform : public SceneToolBase
{
public:
    SceneToolTransform(SceneNode * node);

    bool mouseMoveEvent(QMouseEvent * event) override;
    bool mousePressEvent(QMouseEvent * event) override;
    bool mouseReleaseEvent(QMouseEvent * event) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;

private:
    bool m_pressed;
    sf::Vector2f m_mouseStartPos;
    sf::Vector2f m_mouseOffset;
};

#endif // SCENETOOLTRANSFORM_H
