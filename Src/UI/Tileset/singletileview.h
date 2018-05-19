#ifndef SINGLETILEVIEW_H
#define SINGLETILEVIEW_H

#include "UI/qsfmlcanvas.h"
#include "ressource.h"
#include "Tileset/tileshape.h"

class SingleTileView : public QSFMLCanvas
{
    Q_OBJECT
public:
    SingleTileView(TileShape shape, QWidget *parent = nullptr);
    inline void setTexture(const Texture & texture) {m_texture = texture;}
    inline void setTileID(unsigned int id) {m_id = id;}
    inline void setDeltaTile(unsigned int delta) {m_deltaTile = delta;}
    inline void setTileSize(unsigned int size) {m_tileSize = size;}
    inline void setTileColliderValue(unsigned int value) {m_colliderValue = value;}

signals:
    void onRightClick();
    void onLeftClick();

protected:
    void OnUpdate() override;
    void resizeEvent(QResizeEvent *) override;
    void mousePressEvent(QMouseEvent *e) override;

private:
    void updateView();
    void drawSprite(const Texture & texture, unsigned int id, unsigned int tileSize, unsigned int delta, const sf::FloatRect & rect);
    void drawCollider();

    Texture m_shapeTexture;
    Texture m_texture;
    TileShape m_shape;
    unsigned int m_id;
    unsigned int m_deltaTile;
    unsigned int m_tileSize;
    unsigned int m_colliderValue;
};

#endif // SINGLETILEVIEW_H
