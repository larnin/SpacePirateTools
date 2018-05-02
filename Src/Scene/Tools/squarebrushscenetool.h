#ifndef SQUAREBRUSHSCENETOOL_H
#define SQUAREBRUSHSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushsquare.h"

class SquareBrushSceneTool : public BaseTilesetSceneTool
{
public:
    SquareBrushSceneTool(TilesetLayer & layer, const BrushSquare & brush);

protected:
    void onAddTile(const sf::Vector2u &pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushSquare & m_brush;
};

#endif // SQUAREBRUSHSCENETOOL_H
