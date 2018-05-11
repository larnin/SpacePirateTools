#ifndef BOX2DCOLLIDERVALUEWIDGET_H
#define BOX2DCOLLIDERVALUEWIDGET_H

#include "Object/Value/objectvaluebox2dcollider.h"
#include <QWidget>
#include <QDoubleSpinBox>

class Box2DColliderValueWidget : public QWidget
{
    Q_OBJECT
public:
    Box2DColliderValueWidget(ObjectValueBox2DCollider & collider, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueBox2DCollider & m_collider;

    QDoubleSpinBox * m_centerX;
    QDoubleSpinBox * m_centerY;
    QDoubleSpinBox * m_sizeX;
    QDoubleSpinBox * m_sizeY;
};

#endif // BOX2DCOLLIDERVALUEWIDGET_H
