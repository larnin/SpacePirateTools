#ifndef PATERNMAPTOOL_H
#define PATERNMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushpatern.h"

class PaternMapTool : public BaseMapTool
{
public:
    PaternMapTool(TilemapData & data, const BrushPatern & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushPatern & m_brush;
};

#endif // PATERNMAPTOOL_H
