#ifndef SINGLETILEVIEW_H
#define SINGLETILEVIEW_H

#include "UI/qsfmlcanvas.h"
#include "ressource.h"

enum class TileShape
{
    Empty,
    Full,
    Left3,
    Right3,
    Top3,
    Down3,
    Horizontal,
    Vertical,
    TopLeft,
    TopRight,
    DownLeft,
    DownRight,
    Left,
    Right,
    Top,
    Down,
    QuadCorners,
    TopLeftCorners3,
    TopRightCorners3,
    DownLeftCorners3,
    DownRightCorners3,
    DiagonalTopLeft,
    DiagonalTopRight,
    LeftCorners,
    RightCorners,
    TopCorners,
    DownCorners,
    TopLeftCorner,
    TopRightCorner,
    DownLeftCorner,
    DownRightCorner,
    TopLeftWithCorner,
    TopRightWithCorner,
    DownLeftWithCorner,
    DownRightWithCorner,
    LeftCorners2,
    RightCorners2,
    TopCorners2,
    DownCorners2,
    LeftCornerTop,
    RightCornerTop,
    TopCornerTop,
    DownCornerTop,
    LeftCornerDown,
    RightCornerDown,
    TopCornerDown,
    DownCornerDown,
    Max = DownCornerDown
};

class SingleTileView : public QSFMLCanvas
{
public:
    SingleTileView(TileShape shape, QWidget *parent = nullptr);
    inline void setTexture(const Texture & texture) {m_texture = texture;}
    inline void setTileID(unsigned int id) {m_id = id;}
    inline void setDeltaTile(unsigned int delta) {m_deltaTile = delta;}

protected:
    void OnUpdate() override;
    void resizeEvent(QResizeEvent *) override;

private:
    void updateView();
    void drawSprite(const Texture & texture, unsigned int id, unsigned int tileSize, unsigned int delta, const sf::FloatRect & rect);

    Texture m_shapeTexture;
    Texture m_texture;
    TileShape m_shape;
    unsigned int m_id;
    unsigned int m_deltaTile;
};

#endif // SINGLETILEVIEW_H
