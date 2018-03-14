#ifndef CENTRALANIMATORWIDGET_H
#define CENTRALANIMATORWIDGET_H

#include "UI/qsfmlcanvas.h"
#include "animatorinfos.h"
#include <SFML/Graphics/VertexArray.hpp>

class CentralAnimatorWidget : public QSFMLCanvas
{
    enum class DragType
    {
        Screen,
        State,
        Transition,
        None
    };

    Q_OBJECT
public:
    CentralAnimatorWidget(AnimatorInfos * infos, QWidget * parent = nullptr);

protected:
    void OnUpdate() override;

    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent *) override;
    void resizeEvent(QResizeEvent * event) override;

public slots:
    void onRightClick(QPoint point);

private:
    void rebuildView();
    sf::VertexArray drawGrid() const;

    AnimatorInfos *m_infos;

    DragType m_drag;
    sf::Vector2i m_mouseOldPos;
    sf::Vector2f m_center;
};

#endif // CENTRALANIMATORWIDGET_H
