#ifndef TRANSFORMVALUEWIDGET_H
#define TRANSFORMVALUEWIDGET_H

#include "Object/Value/objectvaluetransform.h"
#include <QWidget>
#include "QDoubleSpinBox"

class TransformValueWidget : public QWidget
{
    Q_OBJECT
public:
    TransformValueWidget(ObjectValueTransform & transform, QWidget * parent = nullptr);

public slots:
    void onValueChange();

private:
    ObjectValueTransform & m_transform;

    QDoubleSpinBox * m_posX;
    QDoubleSpinBox * m_posY;
    QDoubleSpinBox * m_scaleX;
    QDoubleSpinBox * m_scaleY;
    QDoubleSpinBox * m_rotation;
};

#endif // TRANSFORMVALUEWIDGET_H
