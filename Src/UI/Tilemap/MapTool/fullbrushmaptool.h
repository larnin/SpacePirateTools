#ifndef FULLBRUSHMAPTOOL_H
#define FULLBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushfull.h"

class FullBrushMapTool : public BaseMapTool
{
    struct BlockConnexions
    {
        BlockConnexions(const sf::Vector2u & _pos) : pos(_pos), left(false), right(false), top(false), bottom(false), topLeft(false), topRight(false), bottomLeft(false), bottomRight(false) {}
        sf::Vector2u pos;
        bool left;
        bool right;
        bool top;
        bool bottom;
        bool topLeft;
        bool topRight;
        bool bottomLeft;
        bool bottomRight;
    };

public:
    FullBrushMapTool(TilemapData & data, const BrushFull & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;
    void beforeSelectionEnd() override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    void addTileConnexions(const BlockConnexions & block);
    void checkTileOnMap(const sf::Vector2u & pos);

    const BrushFull & m_brush;

    std::vector<BlockConnexions> m_connexions;
};

#endif // FULLBRUSHMAPTOOL_H
