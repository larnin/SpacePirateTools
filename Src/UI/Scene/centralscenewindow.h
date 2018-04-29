#ifndef CENTRALSCENEWINDOW_H
#define CENTRALSCENEWINDOW_H

#include "sceneinfos.h"
#include "UI/qsfmlcanvas.h"
#include "Scene/Tools/basescenetool.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <memory>

class CentralSceneWindow : public QSFMLCanvas
{
public:
    CentralSceneWindow(SceneInfos * infos, QWidget * parent = nullptr);

    void setTool(std::unique_ptr<BaseSceneTool> && tool) { m_tool = std::move(tool); }

protected:
    void OnUpdate() override;

    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;

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
    std::unique_ptr<BaseSceneTool> m_tool;
};

#endif // CENTRALSCENEWINDOW_H
