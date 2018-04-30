#ifndef BASETILESETSCENETOOL_H
#define BASETILESETSCENETOOL_H

#include "basescenetool.h"
#include "Scene/Layers/tilesetlayer.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <vector>

class BaseTilesetSceneTool : public BaseSceneTool
{
    struct BlockChangeInfos
    {
        sf::Vector2u pos;
        TileInfos tile;
    };

public:
    BaseTilesetSceneTool(TilesetLayer & layer);

    void mouseMoveEvent(QMouseEvent * event) override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void keyPressEvent(QKeyEvent *) override;
    void keyReleaseEvent(QKeyEvent *) override;

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;
    sf::Rect<unsigned int> selectionBounds() const;
    virtual void onAddTile(const sf::Vector2u & pos) = 0;
    virtual void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const = 0;

    TilesetLayer & m_layer;

    bool m_altButtonPressed;
    bool m_onSelection;
    std::vector<BlockChangeInfos> m_blocks;
    std::vector<sf::Vector2u> m_selection;

private:
    void addTile(const sf::Vector2u & pos);
    void onSelectionEnd();
    void drawTiles(sf::RenderTarget &target) const;
    void drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const;

    sf::Vector2u m_mousePos;
};

#endif // BASETILESETSCENETOOL_H
