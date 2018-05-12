#ifndef RIGIDBODYVALUEWIDGET_H
#define RIGIDBODYVALUEWIDGET_H

#include "Object/Value/objectvaluerigidbody.h"
#include <QWidget>
#include <QDoubleSpinBox>

class RigidbodyValueWidget : public QWidget
{
    Q_OBJECT
public:
    RigidbodyValueWidget(ObjectValueRigidbody & rigidbody, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueRigidbody & m_rigidbody;

    QDoubleSpinBox * m_mass;
};

#endif // RIGIDBODYVALUEWIDGET_H
