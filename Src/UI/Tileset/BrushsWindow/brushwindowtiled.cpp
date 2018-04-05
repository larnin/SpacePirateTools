#include "brushwindowtiled.h"
#include "UI/flowlayout.h"
#include "QFrame"
#include <QVBoxLayout>

BrushWindowTiled::BrushWindowTiled(BrushTiled *brush, QWidget *parent)
    : BrushWindowBase(parent)
    , m_brush(brush)
{
    FlowLayout * tilesLayout = new FlowLayout();

    for(auto shape : brush->validShapes())
    {
        SingleTileView* tile = new SingleTileView(shape);
        tile->setFixedSize(44, 44);
        auto tileValue = brush->tile(shape);
        tile->setTileID(tileValue.id);
        tile->setTileColliderValue(tileValue.collider.toInt());

        QFrame* frame = new QFrame();
        frame->setFrameShape(QFrame::Box);
        QVBoxLayout *frameLayout = new QVBoxLayout();
        frameLayout->addWidget(tile);
        frame->setLayout(frameLayout);
        tilesLayout->addWidget(frame);

        connect(tile, &SingleTileView::onLeftClick, this, [this, i = m_tiles.size()](){onLeftClick(i);});
        connect(tile, &SingleTileView::onRightClick, this, [this, i = m_tiles.size()](){onRightClick(i);});
        m_tiles.push_back(tile);
    }

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(tilesLayout);

    setLayout(layout);
}

void BrushWindowTiled::onValueUpdate()
{
    for(auto t : m_tiles)
    {
        t->setTexture(m_texture);
        t->setDeltaTile(m_delta);
    }
}

void BrushWindowTiled::onLeftClick(unsigned int index)
{
    //todo
}

void BrushWindowTiled::onRightClick(unsigned int index)
{
    //todo
}
