#ifndef FLOATVALUEWIDGET_H
#define FLOATVALUEWIDGET_H

#include "Object/Value/objectvaluefloat.h"
#include <QWidget>
#include <QDoubleSpinBox>

class FloatValueWidget : public QWidget
{
    Q_OBJECT
public:
    FloatValueWidget(ObjectValueFloat & value, QWidget * parent = nullptr);

public slots:
    void onValueChange();

private:
    ObjectValueFloat & m_value;

    QDoubleSpinBox * m_float;
};

#endif // FLOATVALUEWIDGET_H
