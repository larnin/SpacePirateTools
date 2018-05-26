#ifndef VERTICALBRUSHMAPTOOL_H
#define VERTICALBRUSHMAPTOOL_H

#include "basemaptool.h"
#include "Tileset/Brushs/brushvertical.h"

class VerticalBrushMapTool : public BaseMapTool
{
    struct BlockConnexions
    {
        BlockConnexions(const sf::Vector2u & _pos) : pos(_pos), top(false), bottom(false) {}
        sf::Vector2u pos;
        bool top;
        bool bottom;
    };

public:
    VerticalBrushMapTool(TilemapData & data, const BrushVertical & brush);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;
    void beforeSelectionEnd() override;

private:
    void updateTile(const sf::Vector2u & pos, bool updateNext);
    void addTileConnexions(const BlockConnexions & block);
    void checkTileOnMap(const sf::Vector2u & pos);

    const BrushVertical & m_brush;

    std::vector<BlockConnexions> m_connexions;
};

#endif // VERTICALBRUSHMAPTOOL_H
