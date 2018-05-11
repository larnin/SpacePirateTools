#include "box2dcollidervaluewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

Box2DColliderValueWidget::Box2DColliderValueWidget(ObjectValueBox2DCollider &collider, QWidget *parent)
    : QWidget(parent)
    , m_collider(collider)
{
    m_centerX = new QDoubleSpinBox();
    m_centerX->setRange(-1000000, 1000000);
    m_centerX->setValue(m_collider.center.x);
    m_centerY = new QDoubleSpinBox();
    m_centerY->setRange(-1000000, 1000000);
    m_centerY->setValue(m_collider.center.y);

    QHBoxLayout * centerLayout = new QHBoxLayout();
    centerLayout->addWidget(new QLabel("Centre : "));
    centerLayout->addWidget(new QLabel("X"));
    centerLayout->addWidget(m_centerX, 1);
    centerLayout->addSpacing(10);
    centerLayout->addWidget(new QLabel("Y"));
    centerLayout->addWidget(m_centerY, 1);

    m_sizeX = new QDoubleSpinBox();
    m_sizeX->setRange(-1000000, 1000000);
    m_sizeX->setValue(m_collider.size.x);
    m_sizeY = new QDoubleSpinBox();
    m_sizeY->setRange(-1000000, 1000000);
    m_sizeY->setValue(m_collider.size.y);

    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Taille : "));
    sizeLayout->addWidget(new QLabel("X"));
    sizeLayout->addWidget(m_sizeX, 1);
    sizeLayout->addSpacing(10);
    sizeLayout->addWidget(new QLabel("Y"));
    sizeLayout->addWidget(m_sizeY, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(centerLayout);
    layout->addLayout(sizeLayout);

    setLayout(layout);

    connect(m_centerX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_centerY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_sizeX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_sizeY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void Box2DColliderValueWidget::onValueChanged()
{
    m_collider.center.x = m_centerX->value();
    m_collider.center.y = m_centerY->value();
    m_collider.size.x = m_sizeX->value();
    m_collider.size.y = m_sizeY->value();
}
