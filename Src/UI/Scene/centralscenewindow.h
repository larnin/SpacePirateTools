#ifndef CENTRALSCENEWINDOW_H
#define CENTRALSCENEWINDOW_H

#include "sceneinfos.h"
#include "UI/qsfmlcanvas.h"
#include <SFML/Graphics/VertexArray.hpp>

class CentralSceneWindow : public QSFMLCanvas
{
public:
    CentralSceneWindow(SceneInfos * infos, QWidget * parent = nullptr);

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
    void drawGrid();

    SceneInfos * m_infos;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;
    sf::Vector2i m_mouseOldPos;
    bool m_draging;
};

#endif // CENTRALSCENEWINDOW_H
