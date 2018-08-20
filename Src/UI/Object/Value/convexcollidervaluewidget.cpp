#include "convexcollidervaluewidget.h"
#include "UI/linewidget.h"
#include "fillcolliderlayercombobox.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QLabel>
#include <algorithm>
#include <cassert>

ConvexColliderValueWidget::ConvexColliderValueWidget(ObjectValueConvexeCollider &collider, QWidget *parent)
    : QWidget(parent)
    , m_collider(collider)
{
    QPushButton * addButton = new QPushButton("Ajouter un point");

    m_widgetsLayout = new QVBoxLayout();

    m_collisionLayer = new QComboBox();
    fillColliderLayerComboBox(m_collisionLayer);
    m_collisionLayer->setCurrentIndex(m_collider.collisionLayer);

    QHBoxLayout * layerLayout = new QHBoxLayout();
    layerLayout->addWidget(new QLabel("Collision layer:"));
    layerLayout->addWidget(m_collisionLayer, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(m_widgetsLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(addButton);
    layout->addLayout(layerLayout);

    setLayout(layout);

    for(const auto & v : collider.points)
        addWidget(v);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(addWidget()));
    connect(m_collisionLayer, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
}

void ConvexColliderValueWidget::onXValueChange(QWidget * widget, float value)
{
    auto id = indexOf(widget);
    if(id >= m_collider.points.size())
        return;

    m_collider.points[id].x = value;
}

void ConvexColliderValueWidget::onYValueChange(QWidget * widget, float value)
{
    auto id = indexOf(widget);
    if(id >= m_collider.points.size())
        return;

    m_collider.points[id].y = value;
}

void ConvexColliderValueWidget::removeWidget(QWidget * widget)
{
    auto id = indexOf(widget);
    if(id >= m_collider.points.size())
        return;

    m_widgetsLayout->removeWidget(widget);
    m_widgets.erase(m_widgets.begin() + id);
    delete widget;
}

void ConvexColliderValueWidget::addWidget()
{
    m_collider.points.push_back({});
    addWidget({0.0f, 0.0f});
}

void ConvexColliderValueWidget::addWidget(const sf::Vector2f & value)
{
    QWidget * widget = new QWidget();

    QDoubleSpinBox * x = new QDoubleSpinBox();
    x->setRange(-1000000, 1000000);
    x->setValue(value.x);
    QDoubleSpinBox * y = new QDoubleSpinBox();
    y->setRange(-1000000, 1000000);
    y->setValue(value.y);

    QPushButton * removeButton = new QPushButton("X");
    removeButton->setFixedWidth(40);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(new QLabel("Point : "));
    layout->addWidget(new QLabel("X"));
    layout->addWidget(x, 1);
    layout->addSpacing(10);
    layout->addWidget(new QLabel("Y"));
    layout->addWidget(y, 1);
    layout->addSpacing(15);
    layout->addWidget(removeButton);
    layout->setMargin(0);

    widget->setLayout(layout);

    m_widgets.push_back(widget);

    m_widgetsLayout->addWidget(widget);

    connect(x, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this, widget](double value){onXValueChange(widget, value);});
    connect(y, QOverload<double>::of(&QDoubleSpinBox::valueChanged), this, [this, widget](double value){onYValueChange(widget, value);});
    connect(removeButton, &QPushButton::clicked, this, [this, widget](){removeWidget(widget);});
}

unsigned int ConvexColliderValueWidget::indexOf(QWidget * widget)
{
    auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);
    assert(it != m_widgets.end());

    return std::distance(m_widgets.begin(), it);
}

void ConvexColliderValueWidget::onValueChanged()
{
    m_collider.collisionLayer = m_collisionLayer->currentIndex();
}
