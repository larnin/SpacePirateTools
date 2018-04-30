#ifndef RANDOMSCENETOOL_H
#define RANDOMSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Tileset/Brushs/brushrandom.h"
#include <random>

class RandomSceneTool : public BaseTilesetSceneTool
{
public:
    RandomSceneTool(TilesetLayer & layer, const BrushRandom & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    const BrushRandom & m_brush;
    std::discrete_distribution<unsigned int> m_distrib;
    std::mt19937 m_rand;
};

#endif // RANDOMSCENETOOL_H
