#ifndef BASEMAPTOOL_H
#define BASEMAPTOOL_H

#include "Tilemap/tilemapdata.h"
#include "ressource.h"
#include <sfml/Graphics/Drawable.hpp>
#include <QMouseEvent>
#include <QKeyEvent>

class BaseMapTool : public sf::Drawable
{
    struct BlockChangeInfos
    {
        sf::Vector2u pos;
        TileInfos tile;
    };

public:
    BaseMapTool(TilemapData & data, bool selectionTool = false);
    virtual ~BaseMapTool() = default;

    inline void setTexture(const Texture & t){m_texture = t;}
    inline bool isSelectionTool() const { return m_selectionTool; }

    void mouseMoveEvent(QMouseEvent * event);
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent * event);
    void keyPressEvent(QKeyEvent * event);
    void keyReleaseEvent(QKeyEvent * event);

protected:
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;
    sf::Rect<unsigned int> selectionBounds() const;
    virtual void onAddTile(const sf::Vector2u & pos) = 0;
    virtual void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const = 0;
    virtual void beforeSelectionEnd() {}

    TilemapData & m_data;

    Texture m_texture;

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
    bool m_selectionTool;
};

#endif // BASEMAPTOOL_H
