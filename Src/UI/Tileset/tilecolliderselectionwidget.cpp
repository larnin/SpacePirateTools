#include "tilecolliderselectionwidget.h"
#include "enumiterators.h"
#include <SFML/Graphics/RectangleShape.hpp>
#include <QMouseEvent>
#include <QResizeEvent>

constexpr unsigned int colliderSize(32);
constexpr unsigned int colliderDelta(16);
const sf::Color shapesColor(sf::Color::White);
const sf::Color backgroundColor(sf::Color::Black);
const sf::Color selectedColor(sf::Color::Yellow);
const sf::Color hoverColor(sf::Color::Green);
constexpr unsigned int outline(2);

TileColliderSelectionWidget::TileColliderSelectionWidget(QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_xFlipped(false)
    , m_yFlipped(false)
    , m_rotation(TileColliderRotation::R_0)
    , m_selectedCollider(-1)
    , m_mousePos(-10, -10)
{
    setMouseTracking(true);
}

void TileColliderSelectionWidget::OnUpdate()
{
    RenderWindow::clear(backgroundColor);

    drawAllShapes();

    sf::RectangleShape shape(sf::Vector2f(colliderSize, colliderSize));
    shape.setOutlineThickness(outline);
    shape.setFillColor(sf::Color::Transparent);

    auto drawFunct = [this](sf::RectangleShape shape, const sf::Color & c, unsigned int id)
    {
        shape.setOutlineColor(c);
        auto w = nbCollidersWidth();
        sf::Vector2u posCollider(id % w, id / w);
        shape.setPosition(sf::Vector2f(posCollider * (colliderSize + colliderDelta)));
        RenderWindow::draw(shape);
    };

    if(m_selectedCollider >= 0)
        drawFunct(shape, selectedColor, m_selectedCollider);

    auto idCurrent = posToIndex(m_mousePos);
    if(idCurrent >= 0)
        drawFunct(shape, hoverColor, idCurrent);
}
void TileColliderSelectionWidget::mousePressEvent(QMouseEvent * event)
{
    m_mousePos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));

    if(event->button() != Qt::LeftButton)
        return;

    auto id = posToIndex(m_mousePos);
    if(id < 0)
        return;

    TileCollider c;
    c.rotation = m_rotation;
    c.xFlipped = m_xFlipped;
    c.yFlipped = m_yFlipped;
    c.type = static_cast<TileColliderType>(id);

    m_selectedCollider = id;

    emit onTileColliderSelect(c);
}
void TileColliderSelectionWidget::mouseMoveEvent(QMouseEvent *event)
{
    m_mousePos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
}

void TileColliderSelectionWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent(event);

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width(), QWidget::size().height());
    v.setCenter(QWidget::size().width() / 2, QWidget::size().height() / 2);
    v.setCenter(v.getCenter() - sf::Vector2f(colliderDelta, colliderDelta) / 2.0f);
    RenderWindow::setView(v);
}

void TileColliderSelectionWidget::drawAllShapes()
{
    TileCollider c;
    c.rotation = m_rotation;
    c.xFlipped = m_xFlipped;
    c.yFlipped = m_yFlipped;

    auto nbWidth = nbCollidersWidth();

    for(auto v : TileColliderType::Max)
    {
        auto i = static_cast<unsigned int>(v);
        sf::Vector2u pos(i % nbWidth, i / nbWidth);
        c.type = v;
        RenderWindow::draw(c.drawShape(shapesColor, sf::Vector2f(pos * (colliderSize + colliderDelta)) + sf::Vector2f(colliderSize, colliderSize) / 2.0f, colliderSize));
    }
}

unsigned int TileColliderSelectionWidget::nbCollidersWidth() const
{
    return (getSize().x) / (colliderSize + colliderDelta);
}

int TileColliderSelectionWidget::posToIndex(const sf::Vector2f & pos) const
{
    auto nbWidth = nbCollidersWidth();

    for(auto v : TileColliderType::Max)
    {
        auto i = static_cast<unsigned int>(v);
        sf::Vector2u posCollider(i % nbWidth, i / nbWidth);

        if(sf::FloatRect(sf::Vector2f(posCollider * (colliderSize + colliderDelta)), sf::Vector2f(colliderSize, colliderSize)).contains(pos))
            return i;
    }
    return -1;
}
