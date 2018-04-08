#ifndef TILESELECTIONWIDGET_H
#define TILESELECTIONWIDGET_H

#include "UI/imagewidget.h"
#include "ressource.h"

class TileSelectionWidget : public ImageWidget
{
    Q_OBJECT
public:
    TileSelectionWidget(Texture texture, unsigned int delta, QWidget * parent = nullptr);

signals:
    void onTileSelect(unsigned int id);

protected:
    void OnUpdate() override;
    void mousePressEvent(QMouseEvent * event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    
private:
    int index() const;
    sf::Vector2u textureTileSize() const;
    unsigned int m_delta;

    sf::Vector2f m_mousePos;
};

#endif // TILESELECTIONWIDGET_H
