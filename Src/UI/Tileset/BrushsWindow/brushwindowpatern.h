#ifndef BRUSHWINDOWPATERN_H
#define BRUSHWINDOWPATERN_H

#include "brushwindowbase.h"
#include "Tileset/Brushs/brushpatern.h"
#include "UI/Tileset/singletileview.h"
#include <QSpinBox>
#include <QGridLayout>

class BrushWindowPatern : public BrushWindowBase
{
public:
    BrushWindowPatern(BrushPatern * brush, QWidget * parent = nullptr);

public slots:
    void onLeftClick(unsigned int x, unsigned int y);
    void onRightClick(unsigned int x, unsigned int y);
    void onSizeValueChanged();

protected:
    void onValueUpdate() override;

private:
    std::pair<QWidget *, SingleTileView *> addWidget(unsigned int x, unsigned int y, TileFullInfos tileValue);
    void removeWidget(QWidget * widget);

    BrushPatern * m_brush;
    std::vector<SingleTileView*> m_tiles;
    std::vector<QWidget *> m_widgets;
    QGridLayout* m_tilesLayout;
    QSpinBox * m_sizeX;
    QSpinBox * m_sizeY;
};

#endif // BRUSHWINDOWPATERN_H
