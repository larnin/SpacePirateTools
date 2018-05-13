#include "vector2ivaluewidget.h"
#include <QLabel>
#include <QHBoxLayout>

Vector2iValueWidget::Vector2iValueWidget(ObjectValueVector2i &value, QWidget *parent)
    : QWidget(parent)
    , m_value(value)
{
    m_x = new QSpinBox();
    m_x->setRange(-1000000, 1000000);
    m_x->setValue(m_value.value.x);
    m_y = new QSpinBox();
    m_y->setRange(-1000000, 1000000);
    m_y->setValue(m_value.value.y);

    QHBoxLayout * valueLayout = new QHBoxLayout();
    valueLayout->addWidget(new QLabel("Valeur : "));
    valueLayout->addWidget(new QLabel("X"));
    valueLayout->addWidget(m_x, 1);
    valueLayout->addSpacing(10);
    valueLayout->addWidget(new QLabel("Y"));
    valueLayout->addWidget(m_y, 1);

    setLayout(valueLayout);

    connect(m_x, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_y, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void Vector2iValueWidget::onValueChanged()
{
    m_value.value.x = m_x->value();
    m_value.value.y = m_y->value();
}

