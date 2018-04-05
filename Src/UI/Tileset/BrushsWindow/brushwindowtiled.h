#ifndef BRUSHWINDOWTILED_H
#define BRUSHWINDOWTILED_H

#include "brushwindowbase.h"
#include "Tileset/Brushs/brushtiled.h"
#include "UI/Tileset/singletileview.h"
#include <vector>

class BrushWindowTiled : public BrushWindowBase
{
    Q_OBJECT
public:
    BrushWindowTiled(BrushTiled * brush, QWidget * parent = nullptr);

public slots:
    void onLeftClick(unsigned int index);
    void onRightClick(unsigned int index);
protected:
    void onValueUpdate() override;

private:
    BrushTiled * m_brush;
    std::vector<SingleTileView*> m_tiles;
};

#endif // BRUSHWINDOWTILED_H
