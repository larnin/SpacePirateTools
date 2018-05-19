#include "brushwindowpatern.h"
#include "UI/linewidget.h"
#include "UI/Tileset/tileselectiondialog.h"
#include "UI/Tileset/tilecolliderselectiondialog.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

BrushWindowPatern::BrushWindowPatern(BrushPatern * brush, QWidget * parent)
    : BrushWindowBase(parent)
    , m_brush(brush)
    , m_tiles(brush->getSize().x * brush->getSize().y, nullptr)
    , m_widgets(brush->getSize().x * brush->getSize().y, nullptr)
{
    m_sizeX = new QSpinBox();
    m_sizeX->setRange(1, 100);
    m_sizeX->setValue(brush->getSize().x);
    m_sizeY = new QSpinBox();
    m_sizeY->setRange(1, 100);
    m_sizeY->setValue(brush->getSize().y);
    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("X : "));
    sizeLayout->addWidget(m_sizeX, 1);
    sizeLayout->addSpacing(10);
    sizeLayout->addWidget(new QLabel("Y : "));
    sizeLayout->addWidget(m_sizeY, 1);

    m_tilesLayout = new QGridLayout();

    for(unsigned int j(0) ; j < brush->getSize().y ; j++)
        for(unsigned int i(0) ; i < brush->getSize().x ; i++)
        {
            auto f = addWidget(i, j, (*brush)[sf::Vector2u(i, j)]);
            m_tiles[i + j * brush->getSize().x] = f.second;
            m_widgets[i + j * brush->getSize().x] = f.first;
        }

    QHBoxLayout* tilesHLayout = new QHBoxLayout();
    tilesHLayout->addStretch(1);
    tilesHLayout->addLayout(m_tilesLayout);
    tilesHLayout->addStretch(1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Taille du patern"));
    layout->addLayout(sizeLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(tilesHLayout);
    layout->addStretch(1);

    setLayout(layout);

    connect(m_sizeX, &QSpinBox::editingFinished, this, &onSizeValueChanged);
    connect(m_sizeY, &QSpinBox::editingFinished, this, &onSizeValueChanged);
}

void BrushWindowPatern::onLeftClick(unsigned int x, unsigned int y)
{
    bool ok = false;
    unsigned int value = TileSelectionDialog::getTileID(m_texture, m_delta, m_size, this, &ok);
    if(!ok)
        return;
    unsigned int index(x + y * m_brush->getSize().x);
    m_tiles[index]->setTileID(value);
    (*m_brush)[sf::Vector2u(x, y)].id = value;
}

void BrushWindowPatern::onRightClick(unsigned int x, unsigned int y)
{
    bool ok = false;
    auto value = TileColliderSelectionDialog::getTileCollider(this, &ok);
    if(!ok)
        return;
    unsigned int index(x + y * m_brush->getSize().x);
    m_tiles[index]->setTileColliderValue(value.toInt());
    (*m_brush)[sf::Vector2u(x, y)].collider = value;
}

void BrushWindowPatern::onValueUpdate()
{
    for(auto t : m_tiles)
    {
        t->setTexture(m_texture);
        t->setDeltaTile(m_delta);
        t->setTileSize(m_size);
    }
}

void BrushWindowPatern::onSizeValueChanged()
{
    sf::Vector2u oldSize = m_brush->getSize();
    sf::Vector2u size(m_sizeX->value(), m_sizeY->value());
    m_brush->setSize(size);

    std::vector<SingleTileView*> tiles(size.x * size.y, nullptr);
    std::vector<QWidget *> widgets(size.x * size.y, nullptr);
    for(unsigned int i(0) ; i < std::max(size.x, oldSize.x) ; i++)
        for(unsigned int j(0) ; j < std::max(size.y, oldSize.y) ; j++)
        {
            unsigned int index = i + j * size.x;
            unsigned int oldIndex = i + j * oldSize.x;
            if(i < size.x && j < size.y && i < oldSize.x && j < oldSize.y)
            {
                widgets[index] = m_widgets[oldIndex];
                tiles[index] = m_tiles[oldIndex];
            }
            else if(size.x < oldSize.x || size.y < oldSize.y)
                removeWidget(m_widgets[oldIndex]);
            else //size.x > oldSize.x || size.y > oldSize.y
            {
                auto f = addWidget(i, j, (*m_brush)[sf::Vector2u(i, j)]);
                widgets[index] = f.first;
                tiles[index] = f.second;
            }
        }

    m_tiles = tiles;
    m_widgets = widgets;
}

std::pair<QWidget*, SingleTileView*> BrushWindowPatern::addWidget(unsigned int x, unsigned int y, TileFullInfos tileValue)
{
    SingleTileView* tile = new SingleTileView(TileShape::Empty);
    tile->setFixedSize(44, 44);
    tile->setTileID(tileValue.id);
    tile->setTileColliderValue(tileValue.collider.toInt());
    tile->setTexture(m_texture);
    tile->setDeltaTile(m_delta);
    tile->setTileSize(m_size);

    QFrame* frame = new QFrame();
    frame->setFrameShape(QFrame::Box);
    QVBoxLayout *frameLayout = new QVBoxLayout();
    frameLayout->addWidget(tile);
    frame->setLayout(frameLayout);
    frame->setFixedSize(frame->sizeHint());
    m_tilesLayout->addWidget(frame, y, x);

    connect(tile, &SingleTileView::onLeftClick, this, [this, x, y](){onLeftClick(x, y);});
    connect(tile, &SingleTileView::onRightClick, this, [this, x, y](){onRightClick(x, y);});

    return std::make_pair(frame, tile);
}

void BrushWindowPatern::removeWidget(QWidget *widget)
{
    m_tilesLayout->removeWidget(widget);
    delete widget;
}
