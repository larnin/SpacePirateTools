#include "circlecollidervaluewidget.h"
#include "fillcolliderlayercombobox.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

CircleColliderValueWidget::CircleColliderValueWidget(ObjectValueCircleCollider &collider, QWidget *parent)
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

    m_size = new QDoubleSpinBox();
    m_size->setRange(-1000000, 1000000);
    m_size->setValue(m_collider.size);

    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Taille : "));
    sizeLayout->addWidget(m_size, 1);

    m_collisionLayer = new QComboBox();
    fillColliderLayerComboBox(m_collisionLayer);
    m_collisionLayer->setCurrentIndex(m_collider.collisionLayer);

    QHBoxLayout * layerLayout = new QHBoxLayout();
    layerLayout->addWidget(new QLabel("Collision layer:"));
    layerLayout->addWidget(m_collisionLayer, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(centerLayout);
    layout->addLayout(sizeLayout);
    layout->addLayout(layerLayout);

    setLayout(layout);

    connect(m_centerX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_centerY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_size, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_collisionLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
}

void CircleColliderValueWidget::onValueChanged()
{
    m_collider.center.x = m_centerX->value();
    m_collider.center.y = m_centerY->value();
    m_collider.size = m_size->value();
    m_collider.collisionLayer = m_collisionLayer->currentIndex();
}
