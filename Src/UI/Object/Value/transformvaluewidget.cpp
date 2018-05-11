#include "transformvaluewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

TransformValueWidget::TransformValueWidget(ObjectValueTransform &transform, QWidget *parent)
    : QWidget(parent)
    , m_transform(transform)
{
    m_posX = new QDoubleSpinBox();
    m_posX->setRange(-1000000, 1000000);
    m_posX->setValue(m_transform.position.x);
    m_posY = new QDoubleSpinBox();
    m_posY->setRange(-1000000, 1000000);
    m_posY->setValue(m_transform.position.y);

    QHBoxLayout * posLayout = new QHBoxLayout();
    posLayout->addWidget(new QLabel("Position : "));
    posLayout->addWidget(new QLabel("X "));
    posLayout->addWidget(m_posX, 1);
    posLayout->addSpacing(10);
    posLayout->addWidget(new QLabel("Y "));
    posLayout->addWidget(m_posY, 1);

    m_scaleX = new QDoubleSpinBox();
    m_scaleX->setRange(-1000000, 1000000);
    m_scaleX->setValue(m_transform.scale.x);
    m_scaleY = new QDoubleSpinBox();
    m_scaleY->setRange(-1000000, 1000000);
    m_scaleY->setValue(m_transform.scale.y);

    QHBoxLayout * scaleLayout = new QHBoxLayout();
    scaleLayout->addWidget(new QLabel("Scale : "));
    scaleLayout->addWidget(new QLabel("X "));
    scaleLayout->addWidget(m_scaleX, 1);
    scaleLayout->addSpacing(10);
    scaleLayout->addWidget(new QLabel("Y "));
    scaleLayout->addWidget(m_scaleY, 1);

    m_rotation = new QDoubleSpinBox();
    m_rotation->setRange(-1000000, 1000000);
    m_rotation->setValue(m_transform.rotation);

    QHBoxLayout * rotationLayout = new QHBoxLayout();
    rotationLayout->addWidget(new QLabel("Rotation : "));
    rotationLayout->addWidget(m_rotation, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(posLayout);
    layout->addLayout(scaleLayout);
    layout->addLayout(rotationLayout);

    setLayout(layout);

    connect(m_posX, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_posY, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_scaleX, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_scaleY, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_rotation, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
}

void TransformValueWidget::onValueChange()
{
    m_transform.position.x = m_posX->value();
    m_transform.position.y = m_posY->value();
    m_transform.scale.x = m_scaleX->value();
    m_transform.scale.y = m_scaleY->value();
    m_transform.rotation = m_rotation->value();
}
