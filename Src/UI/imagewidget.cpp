#include "imagewidget.h"
#include "ProjectInfos/configs.h"
#include <QWheelEvent>
#include <QMouseEvent>

constexpr unsigned int defaultZoomLevel(2);

ImageWidget::ImageWidget(const QString &assetName, QWidget * parent)
    : QSFMLCanvas(20, parent)
    , m_zoomLevel(2)
{
    m_texture.loadFromFile(assetName.toStdString());

    m_center = sf::Vector2f(m_texture.getSize() / 2u);
    rebuildView();
}

void ImageWidget::OnUpdate()
{
    RenderWindow::clear(Configs::instance().animationBackgroundColor);

    sf::Sprite s(m_texture);
    RenderWindow::draw(s);
}

void ImageWidget::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0 && m_zoomLevel > 0)
        m_zoomLevel--;
    if(event->angleDelta().y() < 0 && m_zoomLevel < zoomLevels().size() - 1)
        m_zoomLevel++;

    rebuildView();
}

void ImageWidget::mouseMoveEvent(QMouseEvent * event)
{
    float z(zoom());
    sf::Vector2i newPos(event->x(), event->y());
    auto delta = newPos - m_mouseOldPos;
    m_mouseOldPos = newPos;

    if(m_drag)
    {
        m_center -= sf::Vector2f(delta) / z;
        rebuildView();
        return;
    }
}

void ImageWidget::mousePressEvent(QMouseEvent * event)
{
    m_mouseOldPos = sf::Vector2i(event->x(), event->y());

    if(event->button() == Qt::MiddleButton)
        m_drag = true;
}

void ImageWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_drag = false;
}

void ImageWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

const std::vector<float> & ImageWidget::zoomLevels()
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

float ImageWidget::zoom()
{
    if(m_zoomLevel >= zoomLevels().size())
        m_zoomLevel = zoomLevels().size() - 1;
    return zoomLevels()[m_zoomLevel];
}

void ImageWidget::rebuildView()
{
    float z(zoom());

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width() / z, QWidget::size().height() / z);
    v.setCenter(m_center);
    RenderWindow::setView(v);
}
