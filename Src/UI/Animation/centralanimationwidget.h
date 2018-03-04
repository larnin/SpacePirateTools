#ifndef CENTRALANIMATIONWIDGET_H
#define CENTRALANIMATIONWIDGET_H

#include "UI/qsfmlcanvas.h"
#include "animationsinfos.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Vector2.hpp>
#include <QString>

class CentralAnimationWidget : public QSFMLCanvas
{
    enum class DragType
    {
        Screen,
        Origine,
        Left,
        Right,
        Top,
        Down,
        TopLeft,
        TopRight,
        DownLeft,
        DownRight,
        Center,
        None,
    };

    enum TextureIndex
    {
        Origine,
        Left,
        Right,
        Top,
        Down,
        TopLeft,
        TopRight,
        DownLeft,
        DownRight,
    };

public:
    CentralAnimationWidget(AnimationsInfos* infos, QWidget * parent = nullptr);

    void updateTexture(const QString & name);

protected:
    void OnUpdate() override;

    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent * event) override;

private:
    static const std::vector<float> & zoomLevels();
    float zoom();
    void initializeFramesTextures();
    void drawFrames();

    void rebuildView();

    void dragObject(DragType drag, sf::Vector2i current);

    DragType dragTypeZone(const Frame & f, const sf::Vector2i & pos);

    void showDragCursor(const sf::Vector2i &pos);

    AnimationsInfos * m_animationInfos;
    sf::Texture m_texture;
    bool m_textureEnabled;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;
    DragType m_drag;
    sf::Vector2i m_mouseOldPos;
    sf::Vector2i m_mouseStartPos;
    Frame m_frameStartDrag;
    unsigned int m_currentDragFrame;
    std::vector<sf::Texture> m_framesTextures;
};

#endif // CENTRALANIMATIONWIDGET_H
