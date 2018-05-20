#ifndef FULLBRUSHMAPTOOL_H
#define FULLBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushfull.h"

class FullBrushMapTool : public BaseMapTool
{
public:
    FullBrushMapTool(TilemapData & data, const BrushFull & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushFull & m_brush;
};

#endif // FULLBRUSHMAPTOOL_H
