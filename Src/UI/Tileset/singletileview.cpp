#include "singletileview.h"
#include "ProjectInfos/projectinfos.h"
#include "Tileset/tilecollider.h"
#include <SFML/Graphics/Sprite.hpp>
#include <QMouseEvent>

constexpr unsigned int shapeSize(38);
constexpr unsigned int shapeTextureSize(4);
constexpr unsigned int shapeDeltaSize(1);
constexpr unsigned int tileSize(32);
constexpr unsigned int totalSize(44);

SingleTileView::SingleTileView(TileShape shape, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_shapeTexture("Img/TileShapes.png")
    , m_shape(shape)
    , m_id(0)
    , m_deltaTile(0)
    , m_colliderValue(0)
{
    updateView();
}

void SingleTileView::OnUpdate()
{
    RenderWindow::clear(sf::Color::White);

    if(m_shapeTexture.isValid())
        drawSprite(m_shapeTexture, static_cast<unsigned int>(m_shape), shapeTextureSize, shapeDeltaSize
                   , sf::FloatRect((totalSize - shapeSize) / 2.0f, (totalSize - shapeSize) / 2.0f, shapeSize, shapeSize));

    if(m_texture.isValid())
        drawSprite(m_texture, m_id, ProjectInfos::instance().options().tileSize, m_deltaTile
                   , sf::FloatRect((totalSize - tileSize) / 2.0f, (totalSize - tileSize ) / 2.0f, tileSize, tileSize));

    drawCollider();
}

void SingleTileView::resizeEvent(QResizeEvent *)
{
    updateView();
}

void SingleTileView::updateView()
{
    float w(totalSize), h(totalSize);
    if(QWidget::width() > QWidget::height())
        w *= QWidget::width() / QWidget::height();
    else h *= QWidget::height() / QWidget::width();

    sf::View v(sf::FloatRect(0, 0, w, h));
    RenderWindow::setView(v);
}

void SingleTileView::drawSprite(const Texture & texture, unsigned int id, unsigned int tileSize, unsigned int delta, const sf::FloatRect & rect)
{
    if(!texture.isValid())
        return;

    unsigned int tileByRow = (texture->getSize().x + delta) / (tileSize + delta);
    unsigned int x(id % tileByRow);
    unsigned int y(id / tileByRow);

    sf::Sprite s(*texture, sf::IntRect(x * (tileSize + delta), y * (tileSize + delta), tileSize, tileSize));
    s.setPosition(rect.left, rect.top);
    s.setScale(rect.width / tileSize, rect.height / tileSize);

    RenderWindow::draw(s);
}

void SingleTileView::drawCollider()
{
    auto pos = totalSize / 2.0f;
    RenderWindow::draw(TileCollider(m_colliderValue).drawShape(sf::Color::Green, sf::Vector2f(pos, pos), tileSize));
}

void SingleTileView::mousePressEvent(QMouseEvent * e)
{
    if(e->button() == Qt::LeftButton)
        emit onLeftClick();
    if(e->button() == Qt::RightButton)
        emit onRightClick();
}
