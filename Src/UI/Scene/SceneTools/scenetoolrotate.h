#ifndef SCENETOOLROTATE_H
#define SCENETOOLROTATE_H

#include "scenetoolbase.h"

class SceneToolRotate : public SceneToolBase
{
public:
    SceneToolRotate(SceneNode * node);

    bool mouseMoveEvent(QMouseEvent * event) override;
    bool mousePressEvent(QMouseEvent * event) override;
    bool mouseReleaseEvent(QMouseEvent * event) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;

private:
    bool m_pressed;
    sf::Vector2f m_mouseStartPos;
    sf::Vector2f m_mouseOffset;
    sf::Transform m_baseTransform;
    float m_baseAngle;
    float m_baseMouseAngle;
};

#endif // SCENETOOLROTATE_H
