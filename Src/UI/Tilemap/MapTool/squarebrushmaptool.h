#ifndef SQUAREBRUSHMAPTOOL_H
#define SQUAREBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushsquare.h"

class SquareBrushMapTool : public BaseMapTool
{
public:
    SquareBrushMapTool(TilemapData & data, const BrushSquare & brush);

protected:
    void onAddTile(const sf::Vector2u &pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushSquare & m_brush;
};

#endif // SQUAREBRUSHMAPTOOL_H
