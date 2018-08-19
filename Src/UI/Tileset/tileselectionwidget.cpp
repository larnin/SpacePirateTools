#include "tileselectionwidget.h"
#include "ProjectInfos/projectinfos.h"
#include <QMouseEvent>
#include <QWheelEvent>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <cmath>

const sf::Color selectColor(sf::Color::Green);
const sf::Color fillColor(sf::Color::Transparent);
constexpr unsigned int outline(2);

TileSelectionWidget::TileSelectionWidget(Texture texture, unsigned int delta, unsigned int size, QWidget *parent)
    : ImageWidget(texture, parent)
    , m_delta(delta)
    , m_size(size)
    , m_mousePos(0, 0)
{
    setMouseTracking(true);
}

void TileSelectionWidget::OnUpdate()
{
    ImageWidget::OnUpdate();

    if(!getTexture().isValid())
        return;

    auto id = index();
    if(id < 0)
        return;

    auto textureSize = textureTileSize();
    sf::Vector2u pos(id % textureSize.x, id / textureSize.x);

    sf::RectangleShape shape(sf::Vector2f(m_size, m_size));
    shape.setFillColor(fillColor);
    shape.setOutlineColor(selectColor);
    shape.setOutlineThickness(outline);
    shape.setPosition(sf::Vector2f(pos * (m_size + m_delta)));

    RenderWindow::draw(shape);
}

void TileSelectionWidget::mousePressEvent(QMouseEvent * event)
{
    ImageWidget::mousePressEvent(event);

    if(!getTexture().isValid() || event->button() != Qt::LeftButton)
        return;

    m_mousePos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));

    auto id = index();
    if(id < 0)
        return;

    emit onTileSelect(id);
}

void TileSelectionWidget::mouseMoveEvent(QMouseEvent *event)
{
    ImageWidget::mouseMoveEvent(event);

    m_mousePos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
}

int TileSelectionWidget::index() const
{
    sf::Vector2f relativePos(m_mousePos / float(m_size + m_delta));
    auto textureSize = textureTileSize();
    if(relativePos.x < 0 || relativePos.y < 0 || relativePos.x >= textureSize.x || relativePos.y >= textureSize.y)
        return -1;
    return static_cast<int>(relativePos.x) + static_cast<int>(relativePos.y) * textureSize.x;
}

sf::Vector2u TileSelectionWidget::textureTileSize() const
{
    auto texture = getTexture();
    if(!texture.isValid())
        return {0, 0};

    return sf::Vector2u((texture->getSize().x + m_delta) / (m_size + m_delta), (texture->getSize().y + m_delta) / (m_size + m_delta));
}
