#ifndef VERTICALBRUSHSCENETOOL_H
#define VERTICALBRUSHSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushvertical.h"

class VerticalBrushSceneTool : public BaseTilesetSceneTool
{
public:
    VerticalBrushSceneTool(TilesetLayer & layer, const BrushVertical & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushVertical & m_brush;
};

#endif // VERTICALBRUSHSCENETOOL_H
