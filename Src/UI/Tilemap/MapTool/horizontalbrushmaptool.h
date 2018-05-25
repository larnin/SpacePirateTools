#ifndef HORIZONTALBRUSHMAPTOOL_H
#define HORIZONTALBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushhorizontal.h"

class HorizontalBrushMapTool : public BaseMapTool
{
    struct BlockConnexions
    {
        BlockConnexions(const sf::Vector2u & _pos) : pos(_pos), left(false), right(false) {}
        sf::Vector2u pos;
        bool left;
        bool right;
    };

public:
    HorizontalBrushMapTool(TilemapData & data, const BrushHorizontal & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;
    void beforeSelectionEnd() override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    const BrushHorizontal & m_brush;
    void addTileConnexions(const BlockConnexions & block);
    void checkTileOnMap(const sf::Vector2u & pos);

    std::vector<BlockConnexions> m_connexions;
};

#endif // HORIZONTALBRUSHMAPTOOL_H
