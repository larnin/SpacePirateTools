#ifndef INTVALUEWIDGET_H
#define INTVALUEWIDGET_H

#include "Object/Value/objectvalueint.h"
#include <QWidget>
#include <QSpinBox>

class IntValueWidget : public QWidget
{
    Q_OBJECT
public:
    IntValueWidget(ObjectValueInt & value, QWidget * parent = nullptr);

public slots:
    void onValueChange();

private:
    ObjectValueInt & m_value;

    QSpinBox * m_int;
};

#endif // INTVALUEWIDGET_H
