#include "centraltilemapwidget.h"

CentralTilemapWidget::CentralTilemapWidget(TilemapInfos *tilemap, QWidget *parent)
    : QSFMLCanvas(20)
    , m_infos(tilemap)
{
    tilemap->setCentralWidget(this);
}

void CentralTilemapWidget::OnUpdate()
{
    RenderWindow::clear(sf::Color::Black);
}
