#ifndef CIRCLECOLLIDERVALUEWIDGET_H
#define CIRCLECOLLIDERVALUEWIDGET_H

#include "Object/Value/objectvaluecirclecollider.h"
#include <QWidget>
#include <QDoubleSpinBox>
#include <QComboBox>

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
    QComboBox * m_collisionLayer;
};

#endif // CIRCLECOLLIDERVALUEWIDGET_H
