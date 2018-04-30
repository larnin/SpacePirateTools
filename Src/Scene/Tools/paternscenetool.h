#ifndef PATERNSCENETOOL_H
#define PATERNSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushpatern.h"

class PaternSceneTool : public BaseTilesetSceneTool
{
public:
    PaternSceneTool(TilesetLayer & layer, const BrushPatern & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushPatern & m_brush;
};

#endif // PATERNSCENETOOL_H
