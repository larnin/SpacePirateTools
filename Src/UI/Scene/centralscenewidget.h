#ifndef CENTRALSCENEWIDGET_H
#define CENTRALSCENEWIDGET_H

#include "Scene/scenedata.h"
#include "UI/qsfmlcanvas.h"
#include "selectionmodewidget.h"
#include "SceneTools/scenetoolbase.h"
#include "NodeRenderer/rendersystem.h"
#include <memory>

class CentralSceneWidget : public QSFMLCanvas
{
    Q_OBJECT
public:
    CentralSceneWidget(SceneData & data, QWidget * parent = nullptr);

public slots:
    void onChangeSelectionState(SelectionState state);
    void onChangeLayer(int layerIndex);
    void onChangeNode(int nodeIndex);

signals:
    void selectionStateChanged(SelectionState);
    void currentNodeChanged(int);
    void currentNodeMoved();

protected:
    void OnUpdate() override;

    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;

private:
    static const std::vector<float> & zoomLevels();
    float zoom();
    void rebuildView();

    void drawCurrentLayerPositions();
    void drawVisiblelayers();
    void drawCurrentLayerGizmos();

    int getNextSelectableNode();
    void setToolCurrentNode();

    SceneData & m_data;

    SelectionModeWidget * m_selectionWidget;

    bool m_dragScreen;
    sf::Vector2i m_mouseOldPos;
    sf::Vector2i m_mouseStartPos;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;

    SelectionState m_selectionState;

    int m_currentLayerIndex;
    int m_currentNodeIndex;
    bool m_mouseMoved;

    std::unique_ptr<SceneToolBase> m_sceneTool;

    RenderSystem m_render;
};

#endif // CENTRALSCENEWIDGET_H
