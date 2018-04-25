#include "blockview.h"
#include "ProjectInfos/projectinfos.h"
#include <QWheelEvent>
#include <QMouseEvent>

BlockView::BlockView(QWidget * parent)
    : QSFMLCanvas(20, parent)
    , m_array(sf::Quads)
    , m_selected(false)
    , m_selectedId(0)
{
    setMouseTracking(true);

    drawTiles();
}

void BlockView::setTexture(Texture texture)
{
    m_texture = texture;
    drawTiles();
}

void BlockView::OnUpdate()
{
    RenderWindow::clear(sf::Color::White);
    if(!m_texture.isValid())
        return;
    RenderWindow::draw(m_array, sf::RenderStates(m_texture()));
    checkSelected();
    if(m_selected)
        RenderWindow::draw(generactSelector());
}

void BlockView::showEvent(QShowEvent* event)
{
    QSFMLCanvas::showEvent(event);

    sf::View v(RenderWindow::getView());
    v.setSize(sf::Vector2f(width()/2.0f, height()/2.0f));
    v.setCenter(v.getSize()/2.0f);
    RenderWindow::setView(v);
}

void BlockView::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    auto tileSize = ProjectInfos::instance().options().tileSize;

    sf::Vector2i realPos(sf::Vector2i(RenderWindow::mapPixelToCoords(sf::Vector2i(event->localPos().x(), event->localPos().y())))/int(tileSize+2));
    int index(realPos.x + realPos.y*(width()/2/(tileSize+2)));
    if(index >= int(textureTileCount()) || index < 0)
        return;
    emit selectBlock(index);
    m_selectedId = index;
    m_selected = true;
}

void BlockView::wheelEvent(QWheelEvent * event)
{
    sf::View v(RenderWindow::getView());
    if(v.getSize().y >= m_botomTiles)
        return;

    int move = event->angleDelta().y();
    if(move < 0)
        move = -20;
    if(move > 0)
        move = 20;
    move = -move;

    if (v.getCenter().y + move - v.getSize().y/2 < 0)
        v.setCenter(v.getSize()/2.0f);
    else if(v.getCenter().y + move + v.getSize().y/2>m_botomTiles)
        v.setCenter(v.getSize().x/2, m_botomTiles-v.getSize().y/2);
    else v.setCenter(v.getCenter().x, v.getCenter().y+move);
    RenderWindow::setView(v);
}

void BlockView::resizeEvent(QResizeEvent * event)
{
    QSFMLCanvas::resizeEvent(event);
    drawTiles();
    sf::View v(RenderWindow::getView());
    v.setSize(sf::Vector2f(width()/2.0f, height()/2.0f));
    v.setCenter(v.getSize()/2.0f);
    RenderWindow::setView(v);
}

void BlockView::drawTiles()
{
    m_array.clear();
    if(!m_texture.isValid())
        return;

    auto tileCount = textureTileCount();
    auto delta = ProjectInfos::instance().options().delta;
    auto size = ProjectInfos::instance().options().tileSize;
    auto tileCountInWidth = (m_texture->getSize().x + delta) / (size + delta);
    m_array.resize(tileCount*4);

    const unsigned int caseWidth(size+2);
    unsigned int nbWidth(width() / 2 / caseWidth);
    if(nbWidth == 0)
        return;

    for(unsigned int i(0) ; i < tileCount ; i++)
    {
        auto x(i % tileCountInWidth);
        auto y(i / tileCountInWidth);

        sf::Vector2f pos(i%nbWidth*caseWidth+1, i/nbWidth*caseWidth+1);
        sf::FloatRect tex(x * (size + delta), y * (size + delta), size, size);
        drawQuad(&(m_array[i*4]), sf::FloatRect(pos, sf::Vector2f(size, size)), tex);
    }

    m_botomTiles = tileCount/nbWidth*caseWidth+1+caseWidth;
}

void BlockView::setBlock(unsigned int id)
{
    m_selectedId = id;
    m_selected = true;
}

sf::RectangleShape BlockView::generactSelector() const
{
    auto tileSize = ProjectInfos::instance().options().tileSize;
    sf::RectangleShape sharp;
    sharp.setSize(sf::Vector2f(tileSize, tileSize));
    sharp.setOutlineColor(sf::Color::Red);
    sharp.setFillColor(sf::Color::Transparent);
    sharp.setOutlineThickness(2);

    auto tileCount = textureTileCount();
    if(m_selectedId >= tileCount)
    {
        sharp.setPosition(sf::Vector2f(-2*tileSize, -2*tileSize));
        return sharp;
    }

    const unsigned int caseWidth(tileSize+2);
    unsigned int nbWidth(width() / 2 / caseWidth);
    sharp.setPosition(m_selectedId % nbWidth * caseWidth + 1, m_selectedId / nbWidth * caseWidth + 1);

    return sharp;
}

void BlockView::checkSelected()
{
    if( m_selectedId >= textureTileCount())
    {
        m_selected = false;
        return;
    }
}

void BlockView::drawQuad(sf::Vertex* quad, const sf::FloatRect & rect, const sf::FloatRect & texRect) const
{
    quad[0].position = sf::Vector2f(rect.left, rect.top);
    quad[0].texCoords = sf::Vector2f(texRect.left, texRect.top);

    quad[1].position = sf::Vector2f(rect.left + rect.width, rect.top);
    quad[1].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top);

    quad[2].position = sf::Vector2f(rect.left + rect.width, rect.top + rect.height);
    quad[2].texCoords = sf::Vector2f(texRect.left + texRect.width, texRect.top + texRect.height);

    quad[3].position = sf::Vector2f(rect.left, rect.top + rect.height);
    quad[3].texCoords = sf::Vector2f(texRect.left, texRect.top + texRect.height);
}


unsigned int BlockView::textureTileCount() const
{
    if(!m_texture.isValid())
        return 0;

    auto size = ProjectInfos::instance().options().tileSize;
    auto delta = ProjectInfos::instance().options().delta;

    return (m_texture->getSize().x + delta) / (size + delta) * (m_texture->getSize().y + delta) / (size + delta);
}
