#ifndef HORIZONTALBRUSHSCENETOOL_H
#define HORIZONTALBRUSHSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushhorizontal.h"

class HorizontalBrushSceneTool : public BaseTilesetSceneTool
{
public:
    HorizontalBrushSceneTool(TilesetLayer & layer, const BrushHorizontal & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushHorizontal & m_brush;
};

#endif // HORIZONTALBRUSHSCENETOOL_H
