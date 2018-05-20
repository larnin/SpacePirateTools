#ifndef SINGLETILEMAPTOOL_H
#define SINGLETILEMAPTOOL_H

#include "basemaptool.h"

class SingleTileMapTool : public BaseMapTool
{
public:
    SingleTileMapTool(TilemapData & data, const TileInfos &tile);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    TileInfos m_tile;
};

#endif // SINGLETILEMAPTOOL_H
