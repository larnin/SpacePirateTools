#include "brushwindowrandom.h"
#include "UI/linewidget.h"
#include "UI/Tileset/tileselectiondialog.h"
#include "UI/Tileset/tilecolliderselectiondialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QDoubleSpinBox>
#include <QFrame>
#include <algorithm>
#include <cassert>

#include <iostream>

BrushWindowRandom::BrushWindowRandom(BrushRandom *brush, QWidget *parent)
    : BrushWindowBase(parent)
    , m_brush(brush)
{
    m_collider = new SingleTileView(TileShape::Empty);
    m_collider->setFixedSize(44, 44);
    m_collider->setTileColliderValue(brush->collider.toInt());

    QFrame* frameCollider = new QFrame();
    frameCollider->setFrameShape(QFrame::Box);
    QVBoxLayout *frameLayout = new QVBoxLayout();
    frameLayout->addWidget(m_collider);
    frameCollider->setLayout(frameLayout);
    frameCollider->setFixedSize(frameCollider->sizeHint());

    QHBoxLayout * colliderLayout = new QHBoxLayout();
    colliderLayout->addStretch(1);
    colliderLayout->addWidget(new QLabel("Collider :"));
    colliderLayout->addWidget(frameCollider);
    colliderLayout->addStretch(1);

    QPushButton * addButton = new QPushButton("Ajouter");
    addButton->setFixedWidth(250);

    m_tilesLayout = new FlowLayout();

    for(const auto & value : *brush)
        addWidget(value);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(colliderLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(m_tilesLayout);
    layout->addSpacing(5);
    layout->addWidget(addButton, 0, Qt::AlignHCenter);
    layout->addStretch(1);

    setLayout(layout);

    connect(m_collider, SIGNAL(onRightClick()), this, SLOT(onRightClickCollider()));
    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(onAdd()));
}

void BrushWindowRandom::onLeftClick(QWidget *parent)
{
    bool ok = false;
    unsigned int value = TileSelectionDialog::getTileID(m_texture, m_delta, m_size, this, &ok);
    if(!ok)
        return;

    auto index(indexOf(parent));
    (*m_brush)[index].id = value;
    m_tiles[index]->setTileID(value);
}

void BrushWindowRandom::onRightClickCollider()
{
    bool ok = false;
    auto value = TileColliderSelectionDialog::getTileCollider(this, &ok);
    if(!ok)
        return;
    m_collider->setTileColliderValue(value.toInt());
    m_brush->collider = value;
}

void BrushWindowRandom::onChangeWeight(QWidget *parent, float value)
{
    auto index(indexOf(parent));

    auto & item = (*m_brush)[index];
    item.probability = value;
}

void BrushWindowRandom::onAdd()
{
    m_brush->push_back({0, 0.0f});
    addWidget(m_brush->back());
}

void BrushWindowRandom::onRemove(QWidget *parent)
{
    auto index(indexOf(parent));
    m_brush->erase(m_brush->begin() + index);
    removeWidget(index);
}

void BrushWindowRandom::onValueUpdate()
{
    for(auto t : m_tiles)
    {
        t->setTexture(m_texture);
        t->setDeltaTile(m_delta);
        t->setTileSize(m_size);
    }
}

void BrushWindowRandom::addWidget(TileRandomInfo tileValue)
{
    SingleTileView* tile = new SingleTileView(TileShape::Empty);
    tile->setFixedSize(44, 44);
    tile->setTileID(tileValue.id);
    tile->setTexture(m_texture);
    tile->setDeltaTile(m_delta);
    tile->setTileSize(m_size);

    QDoubleSpinBox * probability = new QDoubleSpinBox();
    probability->setRange(0, 1000);
    probability->setValue(tileValue.probability);

    QPushButton* removeButton = new QPushButton("Supprimer");

    QFrame* frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    QVBoxLayout *frameLayout = new QVBoxLayout();
    frameLayout->addWidget(tile, 0, Qt::AlignHCenter);
    frameLayout->addWidget(new QLabel("Probabilité"), 0, Qt::AlignHCenter);
    frameLayout->addWidget(probability, 0, Qt::AlignHCenter);
    frameLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    frameLayout->addWidget(removeButton, 0, Qt::AlignHCenter);
    frame->setLayout(frameLayout);
    frame->setFixedSize(frame->sizeHint());
    m_tilesLayout->addWidget(frame);

    connect(tile, &SingleTileView::onLeftClick, this, [this, frame](){onLeftClick(frame);});
    connect(probability, qOverload<double>(&QDoubleSpinBox::valueChanged), this, [this, frame](double value){onChangeWeight(frame, value);});
    connect(removeButton, &QPushButton::clicked, this, [this, frame](){onRemove(frame);});

    m_widgets.push_back(frame);
    m_tiles.push_back(tile);
}

void BrushWindowRandom::removeWidget(unsigned int index)
{
    auto widget = m_widgets[index];
    m_widgets.erase(m_widgets.begin() + index);
    m_tiles.erase(m_tiles.begin() + index);
    m_tilesLayout->removeWidget(widget);
    delete widget;
}

unsigned int BrushWindowRandom::indexOf(QWidget * parent)
{
    auto it = std::find(m_widgets.begin(), m_widgets.end(), parent);
    assert(it != m_widgets.end());
    return std::distance(m_widgets.begin(), it);
}
