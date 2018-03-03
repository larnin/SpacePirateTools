#ifndef ANIMATIONPREVIEW_H
#define ANIMATIONPREVIEW_H

#include "UI/qsfmlcanvas.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Graphics/Rect.hpp>

class AnimationsInfos;

class AnimationPreview : public QSFMLCanvas
{
public:
    AnimationPreview(AnimationsInfos* infos, QWidget * parent = nullptr);

    void updateTexture(const QString & name);
protected:
    void OnUpdate() override;

    void mouseReleaseEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent * event) override;

private:
    void updateAnimationTime();
    sf::IntRect globalRect(int border = 0);

    AnimationsInfos* m_animationInfos;

    sf::Texture m_texture;
    bool m_textureEnabled;

    unsigned int m_currentFrame;
    float m_frameTime;
    bool m_animationPaused;
    sf::Clock m_clock;
};

#endif // ANIMATIONPREVIEW_H
