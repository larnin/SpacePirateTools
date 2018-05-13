#include "colorvaluewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QColorDialog>

ColorValueWidget::ColorValueWidget(ObjectValueColor &color, QWidget *parent)
    : QWidget(parent)
    , m_color(color)
{
    m_r = new QSpinBox();
    m_r->setRange(0, 255);
    m_r->setValue(m_color.color.r);
    m_g = new QSpinBox();
    m_g->setRange(0, 255);
    m_g->setValue(m_color.color.g);
    m_b = new QSpinBox();
    m_b->setRange(0, 255);
    m_b->setValue(m_color.color.b);
    m_a = new QSpinBox();
    m_a->setRange(0, 255);
    m_a->setValue(m_color.color.a);

    m_colorButton = new QPushButton("");
    m_colorButton->setFixedWidth(30);
    updateColorButton();

    QHBoxLayout * colorLayout = new QHBoxLayout();
    colorLayout->addWidget(new QLabel("Couleur : "));
    colorLayout->addWidget(new QLabel("R"));
    colorLayout->addWidget(m_r, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(new QLabel("G"));
    colorLayout->addWidget(m_g, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(new QLabel("B"));
    colorLayout->addWidget(m_b, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(new QLabel("A"));
    colorLayout->addWidget(m_a, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(m_colorButton);

    setLayout(colorLayout);

    connect(m_r, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_g, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_b, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_a, SIGNAL(editingFinished()), this, SLOT(onValueChange()));
    connect(m_colorButton, SIGNAL(clicked(bool)), this, SLOT(onClickColor()));
}

void ColorValueWidget::onClickColor()
{
    auto oldColor = m_color.color;
    auto color = QColorDialog::getColor(QColor(oldColor.r, oldColor.g, oldColor.b, oldColor.a), this, "Choisissez une couleur", QColorDialog::ShowAlphaChannel);
    if(!color.isValid())
        return;

    m_color.color = sf::Color(color.red(), color.green(), color.blue(), color.alpha());
    updateColorButton();

    m_r->blockSignals(true);
    m_g->blockSignals(true);
    m_b->blockSignals(true);
    m_a->blockSignals(true);

    m_r->setValue(m_color.color.r);
    m_g->setValue(m_color.color.g);
    m_b->setValue(m_color.color.b);
    m_a->setValue(m_color.color.a);

    m_r->blockSignals(true);
    m_g->blockSignals(true);
    m_b->blockSignals(true);
    m_a->blockSignals(true);
}

void ColorValueWidget::onValueChange()
{
    m_color.color.r = m_r->value();
    m_color.color.g = m_g->value();
    m_color.color.b = m_b->value();
    m_color.color.a = m_a->value();

    updateColorButton();
}

void ColorValueWidget::updateColorButton()
{
    constexpr int size(30);
    QPixmap map(size, size);
    auto color = m_color.color;
    map.fill(QColor(color.r, color.g, color.b));
    m_colorButton->setIcon(QIcon(map));
}
