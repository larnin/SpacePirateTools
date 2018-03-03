#include "centralanimationwidget.h"
#include "ProjectInfos/assettype.h"
#include "ProjectInfos/projectinfos.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <vector>

constexpr unsigned int defaultZoomLevel(2);
const sf::Color borderColor(sf::Color::Cyan);
const sf::Color selectedColor(sf::Color::Green);
const sf::Color offsetColor(sf::Color::Yellow);
const sf::Color vertexColor(sf::Color::Blue);

CentralAnimationWidget::CentralAnimationWidget(AnimationsInfos *infos, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_animationInfos(infos)
    , m_textureEnabled(false)
    , m_zoomLevel(defaultZoomLevel)
    , m_center(0, 0)
    , m_drag(DragType::None)
{
    m_animationInfos->setCentralAnimationWidget(this);
    updateTexture(infos->getAnimationData().imageName);
    initializeFramesTextures();
}

void CentralAnimationWidget::OnUpdate()
{
    RenderWindow::clear();

    if(m_textureEnabled)
    {
        sf::Sprite sImage(m_texture);
        RenderWindow::draw(sImage);
    }

    drawFrames();
}

void CentralAnimationWidget::drawFrames()
{
    const auto & data = m_animationInfos->getAnimationData();
    int currentIndex = m_animationInfos->getCurrentFrameIndex();
    sf::VertexArray vertexs(sf::Lines, data.size() * 8);
    for(unsigned int i(0) ; i < data.size() * 8 ; i++)
        vertexs[i].color = vertexColor;

    for(unsigned int i(0) ; i < data.size() ; i++)
    {
        const Frame & f(data[i]);

        vertexs[i*8].position = sf::Vector2f(f.rect.left, f.rect.top);
        vertexs[i*8+1].position = sf::Vector2f(f.rect.left + f.rect.width, f.rect.top);
        vertexs[i*8+2].position = sf::Vector2f(f.rect.left + f.rect.width, f.rect.top);
        vertexs[i*8+3].position = sf::Vector2f(f.rect.left + f.rect.width, f.rect.top + f.rect.height);
        vertexs[i*8+4].position = sf::Vector2f(f.rect.left + f.rect.width, f.rect.top + f.rect.height);
        vertexs[i*8+5].position = sf::Vector2f(f.rect.left, f.rect.top + f.rect.height);
        vertexs[i*8+6].position = sf::Vector2f(f.rect.left, f.rect.top + f.rect.height);
        vertexs[i*8+7].position = sf::Vector2f(f.rect.left, f.rect.top);

        sf::Color currentColor(int(i) == currentIndex ? selectedColor : borderColor);

        auto drawFunc([this](const sf::Vector2f & pos, const sf::Texture & texture, const sf::Color & color)
        {
            sf::Sprite s(texture);
            s.setPosition(pos);
            s.setColor(color);
            RenderWindow::draw(s);
        });

        drawFunc(sf::Vector2f(f.rect.left, f.rect.top), m_framesTextures[TopLeft], currentColor);
        drawFunc(sf::Vector2f(f.rect.left + f.rect.width - m_framesTextures[TopRight].getSize().x, f.rect.top), m_framesTextures[TopRight], currentColor);
        drawFunc(sf::Vector2f(f.rect.left, f.rect.top + f.rect.height - m_framesTextures[DownLeft].getSize().y), m_framesTextures[DownLeft], currentColor);
        drawFunc(sf::Vector2f(f.rect.left + f.rect.width - m_framesTextures[DownRight].getSize().x, f.rect.top + f.rect.height - m_framesTextures[DownRight].getSize().y), m_framesTextures[DownRight], currentColor);

        drawFunc(sf::Vector2f(f.rect.left, f.rect.top + (f.rect.height - m_framesTextures[Left].getSize().y) / 2.0f), m_framesTextures[Left], currentColor);
        drawFunc(sf::Vector2f(f.rect.left + (f.rect.width - m_framesTextures[Top].getSize().x) / 2.0f, f.rect.top), m_framesTextures[Top], currentColor);
        drawFunc(sf::Vector2f(f.rect.left + f.rect.width - m_framesTextures[Right].getSize().x, f.rect.top + (f.rect.height - m_framesTextures[Right].getSize().y) / 2.0f), m_framesTextures[Right], currentColor);
        drawFunc(sf::Vector2f(f.rect.left + (f.rect.width - m_framesTextures[Down].getSize().x) / 2.0f, f.rect.top + f.rect.height - m_framesTextures[Down].getSize().y), m_framesTextures[Down], currentColor);

        drawFunc(sf::Vector2f(f.rect.left, f.rect.top) + sf::Vector2f(f.offset) - sf::Vector2f(m_framesTextures[Origine].getSize()/2u), m_framesTextures[Origine], offsetColor);
    }

    RenderWindow::draw(vertexs);
}

void CentralAnimationWidget::updateTexture(const QString & name)
{
    m_textureEnabled = false;
    if(name.isEmpty())
        return;

    AssetType img = AssetType::Image;
    QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(img) + "/" + name/* + "." + assetTypeExtension(img)*/;

    m_textureEnabled = m_texture.loadFromFile(fullName.toStdString());

    m_center = sf::Vector2f(m_texture.getSize() / 2u);
    m_zoomLevel = defaultZoomLevel;
    rebuildView();
}

const std::vector<float> & CentralAnimationWidget::zoomLevels()
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

float CentralAnimationWidget::zoom()
{
    if(m_zoomLevel >= zoomLevels().size())
        m_zoomLevel = zoomLevels().size() - 1;
    return zoomLevels()[m_zoomLevel];
}

#include <QDebug>

void CentralAnimationWidget::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0 && m_zoomLevel > 0)
        m_zoomLevel--;
    if(event->angleDelta().y() < 0 && m_zoomLevel < zoomLevels().size() - 1)
        m_zoomLevel++;

    rebuildView();
}

void CentralAnimationWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(m_drag == DragType::None)
        return;

    float z(zoom());
    sf::Vector2i newPos(event->x(), event->y());
    auto delta = newPos - m_mouseOldPos;
    m_mouseOldPos = newPos;

    if(m_drag == DragType::Screen)
    {
        m_center -= sf::Vector2f(delta) / z;
        rebuildView();
        return;
    }

    dragObject(m_drag, newPos);
}
#include <iostream>
void CentralAnimationWidget::dragObject(DragType drag, sf::Vector2i current)
{
    if(m_currentDragFrame >= m_animationInfos->getAnimationData().size())
        return;

    sf::Vector2i oldPos(RenderWindow::mapPixelToCoords(m_mouseStartPos));
    sf::Vector2i newPos(RenderWindow::mapPixelToCoords(current));
    auto move = newPos - oldPos;

    Frame f(m_frameStartDrag);
    std::cout << f.offset.x << " " << f.offset.y << "//" << f.rect.left << " " << f.rect.top << " " << f.rect.width << " " << f.rect.height << std::endl;

    switch(drag)
    {
    case DragType::Origine:
        f.offset += move;
        break;
    case DragType::Left:
        f.rect.left += move.x;
        f.rect.width -= move.x;
        f.offset.x -= move.x;
        break;
    case DragType::Right:
        f.rect.width += move.x;
        if(f.rect.width < 1)
        {
            f.rect.left += f.rect.width - 1;
            f.offset.x -= f.rect.width - 1;
            f.rect.width = 1;
        }
        break;
    case DragType::Top:
        f.rect.top += move.y;
        f.rect.height -= move.y;
        f.offset.y -= move.y;
        break;
    case DragType::Down:
        f.rect.height += move.y;
        if(f.rect.height < 1)
        {
            f.rect.top += f.rect.height - 1;
            f.offset.y -= f.rect.height - 1;
            f.rect.height = 1;
        }
        break;
    case DragType::TopLeft:
        f.rect.left += move.x;
        f.rect.top += move.y;
        f.rect.width -= move.x;
        f.rect.height -= move.y;
        f.offset -= move;
        break;
    case DragType::TopRight:
        f.rect.top += move.y;
        f.rect.height -= move.y;
        f.offset.y -= move.y;
        f.rect.width += move.x;
        if(f.rect.width < 1)
        {
            f.rect.left += f.rect.width - 1;
            f.offset.x -= f.rect.width - 1;
            f.rect.width = 1;
        }
        break;
    case DragType::DownLeft:
        f.rect.height += move.y;
        if(f.rect.height < 1)
        {
            f.rect.top += f.rect.height - 1;
            f.offset.y -= f.rect.height - 1;
            f.rect.height = 1;
        }
        f.rect.left += move.x;
        f.rect.width -= move.x;
        f.offset.x -= move.x;
        break;
    case DragType::DownRight:
        f.rect.height += move.y;
        if(f.rect.height < 1)
        {
            f.rect.top += f.rect.height - 1;
            f.offset.y -= f.rect.height - 1;
            f.rect.height = 1;
        }
        f.rect.width += move.x;
        if(f.rect.width < 1)
        {
            f.rect.left += f.rect.width - 1;
            f.offset.x -= f.rect.width - 1;
            f.rect.width = 1;
        }
        break;
    case DragType::Center:
        f.rect.left += move.x;
        f.rect.top += move.y;
        f.offset -= move;
        break;
    default:
        break;
    }

    if(f.rect.width < 1)
        f.rect.width = 1;
    if(f.rect.height < 1)
        f.rect.height = 1;

    m_animationInfos->setFrame(m_currentDragFrame, f);
}

void CentralAnimationWidget::mousePressEvent(QMouseEvent * event)
{
    if(m_drag != DragType::None)
        return;

    m_mouseOldPos = sf::Vector2i(event->x(), event->y());
    m_mouseStartPos = m_mouseOldPos;

    if(event->button() == Qt::RightButton)
        m_drag = DragType::Screen;
    if(event->button() == Qt::LeftButton)
    {
        sf::Vector2i pos(RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y())));
        const auto & data = m_animationInfos->getAnimationData();

        for(unsigned int i(0) ; i < data.size() ; i++)
        {
            const Frame & f(data[i]);

            m_currentDragFrame = i;
            m_frameStartDrag = data[i];

            if(sf::IntRect(sf::Vector2i(f.rect.left, f.rect.top) + f.offset - sf::Vector2i(m_framesTextures[Origine].getSize() / 2u), sf::Vector2i(m_framesTextures[Origine].getSize())).contains(pos))
            {
                m_drag = DragType::Origine;
                break;
            }

            if(!f.rect.contains(pos))
                continue;

            auto inRectPos = pos - sf::Vector2i(f.rect.left, f.rect.top);

            if(sf::IntRect(sf::Vector2i(0, 0), sf::Vector2i(m_framesTextures[TopLeft].getSize())).contains(inRectPos))
                m_drag = DragType::TopLeft;
            else if(sf::IntRect(sf::Vector2i(f.rect.width - m_framesTextures[TopRight].getSize().x, 0), sf::Vector2i(m_framesTextures[TopRight].getSize())).contains(inRectPos))
                m_drag = DragType::TopRight;
            else if(sf::IntRect(sf::Vector2i(0, f.rect.height - m_framesTextures[DownLeft].getSize().x), sf::Vector2i(m_framesTextures[DownLeft].getSize())).contains(inRectPos))
                m_drag = DragType::DownLeft;
            else if(sf::IntRect(sf::Vector2i(f.rect.width - m_framesTextures[DownRight].getSize().x, f.rect.height - m_framesTextures[DownRight].getSize().y), sf::Vector2i(m_framesTextures[DownRight].getSize())).contains(inRectPos))
                m_drag = DragType::DownRight;
            else if(sf::IntRect(0, 0, m_framesTextures[Left].getSize().x, f.rect.height).contains(inRectPos))
                m_drag = DragType::Left;
            else if(sf::IntRect(f.rect.width - m_framesTextures[Right].getSize().x, 0, m_framesTextures[Right].getSize().x, f.rect.height).contains(inRectPos))
                m_drag = DragType::Right;
            else if(sf::IntRect(0, 0, f.rect.width, m_framesTextures[Top].getSize().y).contains(inRectPos))
                m_drag = DragType::Top;
            else if(sf::IntRect(0, f.rect.height - m_framesTextures[Down].getSize().y, f.rect.width, m_framesTextures[Down].getSize().y).contains(inRectPos))
                m_drag = DragType::Down;
            else m_drag = DragType::Center;

            break;
        }
    }
}

void CentralAnimationWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_drag = DragType::None;
}

void CentralAnimationWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

void CentralAnimationWidget::rebuildView()
{
    float z(zoom());

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width() / z, QWidget::size().height() / z);
    v.setCenter(m_center);
    RenderWindow::setView(v);
}

void CentralAnimationWidget::initializeFramesTextures()
{
    m_framesTextures.clear();

    sf::Image img;
    sf::Color c(255, 255, 255);
    //offset
    img.create(5, 5, sf::Color::Transparent);
    img.setPixel(2, 0, c);
    img.setPixel(1, 1, c);
    img.setPixel(2, 1, c);
    img.setPixel(3, 1, c);
    img.setPixel(0, 2, c);
    img.setPixel(1, 2, c);
    img.setPixel(3, 2, c);
    img.setPixel(4, 2, c);
    img.setPixel(1, 3, c);
    img.setPixel(2, 3, c);
    img.setPixel(3, 3, c);
    img.setPixel(2, 4, c);

    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //Left
    img.create(2, 3, sf::Color::Transparent);
    img.setPixel(0, 0, c);
    img.setPixel(0, 1, c);
    img.setPixel(1, 1, c);
    img.setPixel(0, 2, c);


    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //Right
    img.create(2, 3, sf::Color::Transparent);
    img.setPixel(1, 0, c);
    img.setPixel(0, 1, c);
    img.setPixel(1, 1, c);
    img.setPixel(1, 2, c);


    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //Top
    img.create(3, 2, sf::Color::Transparent);
    img.setPixel(0, 0, c);
    img.setPixel(1, 0, c);
    img.setPixel(2, 0, c);
    img.setPixel(1, 1, c);


    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //Down
    img.create(3, 2, sf::Color::Transparent);
    img.setPixel(1, 0, c);
    img.setPixel(0, 1, c);
    img.setPixel(1, 1, c);
    img.setPixel(2, 1, c);


    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //TopLeft
    img.create(3, 3, sf::Color::Transparent);
    img.setPixel(0, 0, c);
    img.setPixel(1, 0, c);
    img.setPixel(2, 0, c);
    img.setPixel(0, 1, c);
    img.setPixel(0, 2, c);

    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //TopRight
    img.create(3, 3, sf::Color::Transparent);
    img.setPixel(0, 0, c);
    img.setPixel(1, 0, c);
    img.setPixel(2, 0, c);
    img.setPixel(2, 1, c);
    img.setPixel(2, 2, c);

    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //DownLeft
    img.create(3, 3, sf::Color::Transparent);
    img.setPixel(0, 0, c);
    img.setPixel(0, 1, c);
    img.setPixel(0, 2, c);
    img.setPixel(1, 2, c);
    img.setPixel(2, 2, c);

    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);

    //DownRight
    img.create(3, 3, sf::Color::Transparent);
    img.setPixel(2, 0, c);
    img.setPixel(2, 1, c);
    img.setPixel(0, 2, c);
    img.setPixel(1, 2, c);
    img.setPixel(2, 2, c);

    m_framesTextures.push_back(sf::Texture());
    m_framesTextures.back().loadFromImage(img);
}
