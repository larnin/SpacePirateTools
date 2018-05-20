#ifndef CENTRALTILEMAPWIDGET_H
#define CENTRALTILEMAPWIDGET_H

#include "tilemapinfos.h"
#include "UI/qsfmlcanvas.h"
#include "tilemaprenderer.h"
#include "MapTool/basemaptool.h"
#include <memory>

class CentralTilemapWidget : public QSFMLCanvas
{
    Q_OBJECT
public:
    CentralTilemapWidget(TilemapInfos * tilemap, QWidget * parent = nullptr);

    inline void setTool(std::unique_ptr<BaseMapTool> && tool) { m_tool = std::move(tool); }

protected:
    void OnUpdate() override;

    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;
    void keyReleaseEvent(QKeyEvent * event) override;

public slots:
    void onRightClick(QPoint point);

private:
    static const std::vector<float> & zoomLevels();
    float zoom();
    void rebuildView();
    void drawGrid();

    TilemapInfos * m_infos;
    TilemapRenderer m_renderer;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;
    sf::Vector2i m_mouseOldPos;
    bool m_draging;
    bool m_showGrid;
    bool m_drawColliders;
    std::unique_ptr<BaseMapTool> m_tool;
};

#endif // CENTRALTILEMAPWIDGET_H
