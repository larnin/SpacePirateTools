#include "brushwindowtiled.h"
#include "UI/flowlayout.h"
#include "UI/Tileset/tileselectiondialog.h"
#include "UI/Tileset/tilecolliderselectiondialog.h"
#include <QFrame>
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
    bool ok = false;
    unsigned int value = TileSelectionDialog::getTileID(m_texture, m_delta, this, &ok);
    if(!ok)
        return;

    auto & tile = m_brush->tile(m_brush->validShapes()[index]);
    tile.id = value;
    m_tiles[index]->setTileID(value);
}

void BrushWindowTiled::onRightClick(unsigned int index)
{
    bool ok = false;
    auto value = TileColliderSelectionDialog::getTileCollider(this, &ok);
    if(!ok)
        return;
    m_tiles[index]->setTileColliderValue(value.toInt());
    auto & tile = m_brush->tile(m_brush->validShapes()[index]);
    tile.collider = value;
}
