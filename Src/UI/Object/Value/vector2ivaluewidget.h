#ifndef VECTOR2IVALUEWIDGET_H
#define VECTOR2IVALUEWIDGET_H

#include "Object/Value/objectvaluevector2i.h"
#include <QWidget>
#include <QSpinBox>

class Vector2iValueWidget : public QWidget
{
    Q_OBJECT
public:
    Vector2iValueWidget(ObjectValueVector2i & value, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueVector2i & m_value;
    QSpinBox * m_x;
    QSpinBox * m_y;
};

#endif // VECTOR2IVALUEWIDGET_H
