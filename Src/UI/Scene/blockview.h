#ifndef BLOCKVIEW_H
#define BLOCKVIEW_H

#include "UI/qsfmlcanvas.h"
#include "ressource.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class BlockView : public QSFMLCanvas
{
    Q_OBJECT

public:
    BlockView(QWidget * parent = nullptr);

     void setTexture(Texture texture);

signals:
    void selectBlock(unsigned int id);

public slots:
    void setBlock(unsigned int id);

protected:
    void showEvent(QShowEvent* event) override;
    void OnUpdate() override;
    void mouseReleaseEvent(QMouseEvent * event) override;
    void wheelEvent(QWheelEvent * event) override;
    void resizeEvent(QResizeEvent * event) override;

private:
    void drawTiles();
    void updateRect();
    sf::RectangleShape generactSelector() const;
    void checkSelected();

    void drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const;
    unsigned int textureTileCount() const;

    Texture m_texture;
    sf::VertexArray m_array;
    bool m_selected;
    unsigned int m_selectedId;

    float m_botomTiles;
};

#endif // BLOCKVIEW_H
