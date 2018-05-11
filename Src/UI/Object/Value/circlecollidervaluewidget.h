#ifndef CIRCLECOLLIDERVALUEWIDGET_H
#define CIRCLECOLLIDERVALUEWIDGET_H

#include "Object/Value/objectvaluecirclecollider.h"
#include <QWidget>
#include <QDoubleSpinBox>

class CircleColliderValueWidget : public QWidget
{
    Q_OBJECT
public:
    CircleColliderValueWidget(ObjectValueCircleCollider & collider, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueCircleCollider & m_collider;

    QDoubleSpinBox * m_centerX;
    QDoubleSpinBox * m_centerY;
    QDoubleSpinBox * m_size;
};

#endif // CIRCLECOLLIDERVALUEWIDGET_H
