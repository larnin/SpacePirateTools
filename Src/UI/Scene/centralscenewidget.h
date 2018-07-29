#ifndef CENTRALSCENEWIDGET_H
#define CENTRALSCENEWIDGET_H

#include "Scene/scenedata.h"
#include "UI/qsfmlcanvas.h"
#include "selectionmodewidget.h"

class CentralSceneWidget : public QSFMLCanvas
{
    Q_OBJECT
public:
    CentralSceneWidget(SceneData & data, QWidget * parent = nullptr);

public slots:
    void onChangeSelectionState(SelectionState state);

signals:
    void selectionStateChanged(SelectionState);

protected:
    void OnUpdate() override;

    void wheelEvent(QWheelEvent * event) override;
    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent * event) override;
    void keyPressEvent(QKeyEvent * event) override;

private:
    static const std::vector<float> & zoomLevels();
    float zoom();
    void rebuildView();

    SceneData & m_data;

    SelectionModeWidget * m_selectionWidget;

    bool m_dragScreen;
    sf::Vector2i m_mouseOldPos;
    sf::Vector2i m_mouseStartPos;
    unsigned int m_zoomLevel;
    sf::Vector2f m_center;

    SelectionState m_selectionState;
};

#endif // CENTRALSCENEWIDGET_H
