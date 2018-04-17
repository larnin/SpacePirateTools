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

TileSelectionWidget::TileSelectionWidget(Texture texture, unsigned int delta, QWidget *parent)
    : ImageWidget(texture, parent)
    , m_delta(delta)
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
    auto tileSize = ProjectInfos::instance().options().tileSize;

    sf::RectangleShape shape(sf::Vector2f(tileSize, tileSize));
    shape.setFillColor(fillColor);
    shape.setOutlineColor(selectColor);
    shape.setOutlineThickness(outline);
    shape.setPosition(sf::Vector2f(pos * (tileSize + m_delta)));

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
    auto tileSize = ProjectInfos::instance().options().tileSize;

    sf::Vector2f relativePos(m_mousePos / float(tileSize + m_delta));
    auto textureSize = textureTileSize();
    if(relativePos.x < 0 || relativePos.y < 0 || relativePos.x >= textureSize.x || relativePos.y >= textureSize.y)
        return -1;
    return (int)relativePos.x + (int)relativePos.y * textureSize.x;
}

sf::Vector2u TileSelectionWidget::textureTileSize() const
{
    auto texture = getTexture();
    if(!texture.isValid())
        return {0, 0};

    auto tileSize = ProjectInfos::instance().options().tileSize;

    return sf::Vector2u((texture->getSize().x + m_delta) / (tileSize + m_delta), (texture->getSize().y + m_delta) / (tileSize + m_delta));
}