#include "spriterenderervaluewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>

SpriteRendererValueWidget::SpriteRendererValueWidget(ObjectValueSpriteRenderer &spriteRenderer, QWidget *parent)
    : QWidget(parent)
    , m_spriteRenderer(spriteRenderer)
{
    m_top = new QSpinBox();
    m_top->setRange(-1000000, 1000000);
    m_top->setValue(m_spriteRenderer.textureRect.top);
    m_left = new QSpinBox();
    m_left->setRange(-1000000, 1000000);
    m_left->setValue(m_spriteRenderer.textureRect.left);

    m_width = new QSpinBox();
    m_width->setRange(1, 1000000);
    m_width->setValue(m_spriteRenderer.textureRect.width);
    m_height = new QSpinBox();
    m_height->setRange(1, 1000000);
    m_height->setValue(m_spriteRenderer.textureRect.height);

    m_offsetX = new QDoubleSpinBox();
    m_offsetX->setRange(-100000, 100000);
    m_offsetX->setDecimals(2);
    m_offsetX->setSingleStep(1);
    m_offsetX->setValue(m_spriteRenderer.offset.x);

    m_offsetY = new QDoubleSpinBox();
    m_offsetY->setRange(-100000, 100000);
    m_offsetY->setDecimals(2);
    m_offsetY->setSingleStep(1);
    m_offsetY->setValue(m_spriteRenderer.offset.y);

    QHBoxLayout * posLayout = new QHBoxLayout();
    posLayout->addWidget(new QLabel("Position : "));
    posLayout->addWidget(new QLabel("X"));
    posLayout->addWidget(m_left, 1);
    posLayout->addSpacing(10);
    posLayout->addWidget(new QLabel("Y"));
    posLayout->addWidget(m_top, 1);

    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Taille : "));
    sizeLayout->addWidget(new QLabel("X"));
    sizeLayout->addWidget(m_width, 1);
    sizeLayout->addSpacing(10);
    sizeLayout->addWidget(new QLabel("Y"));
    sizeLayout->addWidget(m_height, 1);

    QGroupBox * rectBox = new QGroupBox("Texture rect");
    QVBoxLayout * rectLayout = new QVBoxLayout();
    rectLayout->addLayout(posLayout);
    rectLayout->addLayout(sizeLayout);
    rectBox->setLayout(rectLayout);

    QHBoxLayout * offsetLayout = new QHBoxLayout();
    offsetLayout->addWidget(new QLabel("Offset : "));
    offsetLayout->addWidget(new QLabel("X"));
    offsetLayout->addWidget(m_offsetX, 1);
    offsetLayout->addWidget(new QLabel("Y"));
    offsetLayout->addWidget(m_offsetY, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(rectBox);
    layout->addLayout(offsetLayout);

    setLayout(layout);

    connect(m_top, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_left, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_width, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_height, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}


void SpriteRendererValueWidget::onValueChanged()
{
    m_spriteRenderer.textureRect.top = m_top->value();
    m_spriteRenderer.textureRect.left = m_left->value();
    m_spriteRenderer.textureRect.width = m_width->value();
    m_spriteRenderer.textureRect.height = m_height->value();
    m_spriteRenderer.offset.x = m_offsetX->value();
    m_spriteRenderer.offset.y = m_offsetY->value();
}
