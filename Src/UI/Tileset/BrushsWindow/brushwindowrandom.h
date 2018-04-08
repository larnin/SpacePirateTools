#ifndef BRUSHWINDOWRANDOM_H
#define BRUSHWINDOWRANDOM_H

#include "Tileset/Brushs/brushrandom.h"
#include "brushwindowbase.h"
#include "UI/Tileset/singletileview.h"
#include "UI/flowlayout.h"
#include <vector>

class BrushWindowRandom : public BrushWindowBase
{
    Q_OBJECT
public:
    BrushWindowRandom(BrushRandom * brush, QWidget * parent = nullptr);

public slots:
    void onLeftClick(QWidget * parent);
    void onRightClickCollider();
    void onChangeWeight(QWidget * parent, float value);
    void onAdd();
    void onRemove(QWidget * parent);

protected:
    void onValueUpdate() override;

private:
    void addWidget(TileRandomInfo tileValue);
    void removeWidget(unsigned int index);
    unsigned int indexOf(QWidget * parent);

    BrushRandom * m_brush;
    std::vector<SingleTileView*> m_tiles;
    std::vector<QWidget *> m_widgets;
    SingleTileView* m_collider;
    FlowLayout * m_tilesLayout;
};

#endif // BRUSHWINDOWRANDOM_H
