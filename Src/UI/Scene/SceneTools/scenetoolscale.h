#ifndef SCENETOOLSCALE_H
#define SCENETOOLSCALE_H

#include "scenetoolbase.h"

class SceneToolScale : public SceneToolBase
{
    enum class DirectionState
    {
        Full,
        Horizontal,
        Vertical
    };

public:
    SceneToolScale(SceneNode * node);

    bool mouseMoveEvent(QMouseEvent * event) override;
    bool mousePressEvent(QMouseEvent * event) override;
    bool mouseReleaseEvent(QMouseEvent * event) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;

private:
    bool m_pressed;
    DirectionState m_directionState;
    sf::Vector2f m_mouseStartPos;
    sf::Vector2f m_mouseOffset;
    sf::Transform m_baseTransform;
    sf::Vector2f m_baseScale;
};

#endif // SCENETOOLSCALE_H
