#ifndef TILECOLLIDERSELECTIONWIDGET_H
#define TILECOLLIDERSELECTIONWIDGET_H

#include "UI/qsfmlcanvas.h"
#include "Tileset/tilecollider.h"
#include <SFML/Graphics/VertexArray.hpp>

class TileColliderSelectionWidget : public QSFMLCanvas
{
    Q_OBJECT
public:
    TileColliderSelectionWidget(QWidget* parent = nullptr);

    inline void setXFlipped(bool xFlipped) {m_xFlipped = xFlipped;}
    inline void setYFlipped(bool yFlipped) {m_yFlipped = yFlipped;}
    inline void setColliderRotation(TileColliderRotation rot) {m_rotation = rot;}
    inline void setColliderLayer(unsigned int value) {m_colliderLayer = value;}
    TileCollider get() const;

signals:
    void onTileColliderSelect(const TileCollider & collider);

protected:
    void OnUpdate() override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent * event) override;

private:
    void drawAllShapes();
    unsigned int nbCollidersWidth() const;
    int posToIndex(const sf::Vector2f & pos) const;

    bool m_xFlipped;
    bool m_yFlipped;
    TileColliderRotation m_rotation;
    unsigned int m_colliderLayer;

    int m_selectedCollider;

    sf::Vector2f m_mousePos;
};

#endif // TILECOLLIDERSELECTIONWIDGET_H
