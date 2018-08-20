#ifndef CONVEXCOLLIDERVALUEWIDGET_H
#define CONVEXCOLLIDERVALUEWIDGET_H

#include "Object/Value/objectvalueconvexecollider.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QComboBox>
#include <vector>

class ConvexColliderValueWidget : public QWidget
{
    Q_OBJECT
public:
    ConvexColliderValueWidget(ObjectValueConvexeCollider & collider, QWidget * parent = nullptr);

public slots:
    void onXValueChange(QWidget * widget, float value);
    void onYValueChange(QWidget * widget, float value);
    void removeWidget(QWidget * widget);
    void addWidget();
    void onValueChanged();

private:
    void addWidget(const sf::Vector2f & value);
    unsigned int indexOf(QWidget * widget);

    ObjectValueConvexeCollider & m_collider;

    std::vector<QWidget*> m_widgets;
    QVBoxLayout * m_widgetsLayout;

    QComboBox * m_collisionLayer;
};

#endif // CONVEXCOLLIDERVALUEWIDGET_H
