#ifndef VERTICALBRUSHMAPTOOL_H
#define VERTICALBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushvertical.h"

class VerticalBrushMapTool : public BaseMapTool
{
public:
    VerticalBrushMapTool(TilemapData & data, const BrushVertical & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushVertical & m_brush;
};

#endif // VERTICALBRUSHMAPTOOL_H
