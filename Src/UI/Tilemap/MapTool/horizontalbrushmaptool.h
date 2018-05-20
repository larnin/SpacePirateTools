#ifndef HORIZONTALBRUSHMAPTOOL_H
#define HORIZONTALBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushhorizontal.h"

class HorizontalBrushMapTool : public BaseMapTool
{
public:
    HorizontalBrushMapTool(TilemapData & data, const BrushHorizontal & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushHorizontal & m_brush;
};

#endif // HORIZONTALBRUSHMAPTOOL_H
