#include "spriterenderervaluewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
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

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(posLayout);
    layout->addLayout(sizeLayout);

    setLayout(layout);

    connect(m_top, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_left, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_width, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_height, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}


void SpriteRendererValueWidget::onValueChanged()
{
    m_spriteRenderer.textureRect.top = m_top->value();
    m_spriteRenderer.textureRect.left = m_left->value();
    m_spriteRenderer.textureRect.width = m_width->value();
    m_spriteRenderer.textureRect.height = m_height->value();
}
