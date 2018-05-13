#include "intvaluewidget.h"
#include <QHBoxLayout>
#include <QLabel>

IntValueWidget::IntValueWidget(ObjectValueInt &value, QWidget *parent)
    : QWidget(parent)
    , m_value(value)
{
    m_int = new QSpinBox();
    m_int->setRange(-1000000, 1000000);
    m_int->setValue(m_value.value);

    QHBoxLayout * valueLayout = new QHBoxLayout();
    valueLayout->addWidget(new QLabel("Valeur : "));
    valueLayout->addWidget(m_int, 1);

    setLayout(valueLayout);

    connect(m_int, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
}

void IntValueWidget::onValueChange()
{
    m_value.value = m_int->value();
}
