#include "centralscenewindow.h"
#include "ProjectInfos/projectinfos.h"
#include <QWheelEvent>
#include <QMouseEvent>

constexpr unsigned int defaultZoomLevel(2);
const sf::Color gridColor(128, 128, 128, 128);

CentralSceneWindow::CentralSceneWindow(SceneInfos * infos, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_infos(infos)
    , m_zoomLevel(defaultZoomLevel)
    , m_center(100, 100)
    , m_draging(false)
{
    infos->setCentralSceneWindow(this);
}


void CentralSceneWindow::OnUpdate()
{
    RenderWindow::clear(m_infos->getDatas().color);

    for(unsigned int i(0) ; i < m_infos->getDatas().layerCount() ; i++)
        RenderWindow::draw(m_infos->getDatas().layer(i));

    if(m_infos->showGrid())
    drawGrid();
}

void CentralSceneWindow::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0 && m_zoomLevel > 0)
        m_zoomLevel--;
    if(event->angleDelta().y() < 0 && m_zoomLevel < zoomLevels().size() - 1)
        m_zoomLevel++;

    rebuildView();
}

void CentralSceneWindow::mouseMoveEvent(QMouseEvent * event)
{
    float z(zoom());
    sf::Vector2i newPos(event->x(), event->y());
    auto delta = newPos - m_mouseOldPos;
    m_mouseOldPos = newPos;

    if(m_draging)
    {
        m_center -= sf::Vector2f(delta) / z;
        rebuildView();
        return;
    }
}

void CentralSceneWindow::mousePressEvent(QMouseEvent * event)
{
    if(m_draging)
        return;

    m_mouseOldPos = sf::Vector2i(event->x(), event->y());

    if(event->button() == Qt::MiddleButton)
        m_draging = true;
}

void CentralSceneWindow::mouseReleaseEvent(QMouseEvent *)
{
    m_draging = false;
}

void CentralSceneWindow::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

const std::vector<float> & CentralSceneWindow::zoomLevels()
{
    static std::vector<float> levels
    {
        0.5f,
        0.707f,
        1,
        1.414f,
        2,
        2.828f,
        4,
        5.656f,
        8,
        11.314f,
        16
    };
    return levels;
}

float CentralSceneWindow::zoom()
{
    if(m_zoomLevel >= zoomLevels().size())
        m_zoomLevel = zoomLevels().size() - 1;
    return zoomLevels()[m_zoomLevel];
}

void CentralSceneWindow::rebuildView()
{
    float z(zoom());

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width() / z, QWidget::size().height() / z);
    v.setCenter(m_center);
    RenderWindow::setView(v);
}

#include <iostream>
void CentralSceneWindow::drawGrid()
{
    unsigned int tileSize = ProjectInfos::instance().options().tileSize;
    auto size = m_infos->getDatas().getSize();

    float left = -(tileSize / 2.0f);
    float right = tileSize * size.x + left;
    float top = -(tileSize / 2.0f);
    float bottom = tileSize * size.y + top;

    sf::VertexArray array(sf::Lines, (size.x + size.y + 2) * 2);

    for(unsigned int i(0) ; i <= size.x ; i++)
    {
        array[2*i].position = sf::Vector2f(left + tileSize * i, top);
        array[2*i+1].position = sf::Vector2f(left + tileSize * i, bottom);
    }
    for(unsigned int j(0) ; j <= size.y ; j++)
    {
        array[2*size.x + 2*j + 2].position = sf::Vector2f(left, top + tileSize * j);
        array[2*size.x + 2*j + 3].position = sf::Vector2f(right, top + tileSize * j);
    }

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = gridColor;

    RenderWindow::draw(array);
}
