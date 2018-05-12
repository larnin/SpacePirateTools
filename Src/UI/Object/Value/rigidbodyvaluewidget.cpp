#include "rigidbodyvaluewidget.h"
#include <QLabel>
#include <QHBoxLayout>

RigidbodyValueWidget::RigidbodyValueWidget(ObjectValueRigidbody &rigidbody, QWidget *parent)
    : QWidget(parent)
    , m_rigidbody(rigidbody)
{
    m_mass = new QDoubleSpinBox();
    m_mass->setRange(0.1, 1000000);
    m_mass->setValue(rigidbody.mass);

    QHBoxLayout * massLayout = new QHBoxLayout();
    massLayout->addWidget(new QLabel("Masse : "));
    massLayout->addWidget(m_mass, 1);

    setLayout(massLayout);

    connect(m_mass, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void RigidbodyValueWidget::onValueChanged()
{
    m_rigidbody.mass = m_mass->value();
}
