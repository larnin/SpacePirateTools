#ifndef FULLBRUSHSCRENETOOL_H
#define FULLBRUSHSCRENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushfull.h"

class FullBrushScreneTool : public BaseTilesetSceneTool
{
public:
    FullBrushScreneTool(TilesetLayer & layer, const BrushFull & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushFull & m_brush;
};

#endif // FULLBRUSHSCRENETOOL_H
