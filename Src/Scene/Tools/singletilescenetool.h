#ifndef SINGLETILESCENETOOL_H
#define SINGLETILESCENETOOL_H

#include "basetilesetscenetool.h"

class SingleTileSceneTool : public BaseTilesetSceneTool
{
public:
    SingleTileSceneTool(TilesetLayer & layer, const TileInfos &tile);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    TileInfos m_tile;
};

#endif // SINGLETILESCENETOOL_H
