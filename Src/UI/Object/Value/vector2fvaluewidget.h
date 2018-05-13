#ifndef VECTOR2FVALUEWIDGET_H
#define VECTOR2FVALUEWIDGET_H

#include "Object/Value/objectvaluevector2f.h"
#include <QWidget>
#include <QDoubleSpinBox>

class Vector2fValueWidget : public QWidget
{
    Q_OBJECT
public:
    Vector2fValueWidget(ObjectValueVector2f & value, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueVector2f & m_value;
    QDoubleSpinBox * m_x;
    QDoubleSpinBox * m_y;
};

#endif // VECTOR2FVALUEWIDGET_H
