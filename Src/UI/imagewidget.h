#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "qsfmlcanvas.h"
#include <SFML/Graphics/Texture.hpp>

class ImageWidget : public QSFMLCanvas
{
public:
    ImageWidget(const QString &assetName, QWidget * parent = nullptr);

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
    void rebuildView();

    sf::Texture m_texture;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;
    bool m_drag;
    sf::Vector2i m_mouseOldPos;
};

#endif // IMAGEWIDGET_H
