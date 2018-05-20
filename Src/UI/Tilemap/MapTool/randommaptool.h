#ifndef RANDOMMAPTOOL_H
#define RANDOMMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushrandom.h"

class RandomMapTool : public BaseMapTool
{
public:
    RandomMapTool(TilemapData & data, const BrushRandom & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushRandom & m_brush;
    std::discrete_distribution<unsigned int> m_distrib;
    std::mt19937 m_rand;
};

#endif // RANDOMMAPTOOL_H
