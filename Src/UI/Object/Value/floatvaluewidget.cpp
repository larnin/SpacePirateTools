#include "floatvaluewidget.h"
#include <QHBoxLayout>
#include <QLabel>

FloatValueWidget::FloatValueWidget(ObjectValueFloat &value, QWidget *parent)
    : QWidget(parent)
    , m_value(value)
{
    m_float = new QDoubleSpinBox();
    m_float->setRange(-1000000, 1000000);
    m_float->setValue(m_value.value);

    QHBoxLayout * valueLayout = new QHBoxLayout();
    valueLayout->addWidget(new QLabel("Valeur : "));
    valueLayout->addWidget(m_float, 1);

    setLayout(valueLayout);

    connect(m_float, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
}

void FloatValueWidget::onValueChange()
{
    m_value.value = m_float->value();
}
