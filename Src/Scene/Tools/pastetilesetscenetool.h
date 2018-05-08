#ifndef PASTETILESETSCENETOOL_H
#define PASTETILESETSCENETOOL_H

#include "basetilesetscenetool.h"
#include "copytilesetscenetool.h"

class PasteTilesetSceneTool : public BaseTilesetSceneTool
{
public:
    PasteTilesetSceneTool(TilesetLayer & layer, const std::vector<CopyTilesetSceneTool::CopyValue> & data);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateDataSize();

    std::vector<CopyTilesetSceneTool::CopyValue> m_data;
    sf::Vector2u m_dataSize;
};

#endif // PASTETILESETSCENETOOL_H
