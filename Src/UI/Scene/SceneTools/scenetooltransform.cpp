#include "scenetooltransform.h"
#include "vect2convert.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

const sf::Color horizontalColor(sf::Color::Red);
const sf::Color verticalColor(sf::Color::Green);
const sf::Color surfaceBorderColor(sf::Color::Yellow);
const sf::Color surfaceFillColor(255, 255, 0, 100);
constexpr float arrowSize = 20;
constexpr float arrowSize2 = 4;
constexpr float squareSize = 5;

SceneToolTransform::SceneToolTransform(SceneNode *node)
    : SceneToolBase(node)
    , m_pressed(false)
{

}

bool SceneToolTransform::mouseMoveEvent(QMouseEvent * event)
{
    if(!m_pressed)
        return false;

    m_mouseOffset = sf::Vector2f(event->x(), event->y()) - m_mouseStartPos;
    auto offset = m_baseTransform.transformPoint(m_mouseOffset) - m_baseTransform.transformPoint({0, 0});
    if(m_directionState == DirectionState::Horizontal)
        offset.y = 0;
    if(m_directionState == DirectionState::Vertical)
        offset.x = 0;
    m_node->getLocalTransform().position = m_basePos + offset;

    return false;
}

bool SceneToolTransform::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return false;

    m_mouseStartPos = sf::Vector2f(event->x(), event->y());
    m_baseTransform = m_node->getSFMLParentTransform().getInverse();

    m_basePos = m_node->getLocalTransform().position;

    auto pos = m_node->getSFMLParentTransform().translate(m_basePos).transformPoint({0,0});
    auto rot = -angle(m_baseTransform.transformPoint({1, 0}) - m_baseTransform.transformPoint({0, 0}));
    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));

    auto localMousePos = t.getInverse().transformPoint(m_mouseStartPos);
    if(sf::FloatRect(0, 0, squareSize, squareSize).contains(localMousePos))
        m_directionState = DirectionState::Full;
    else if(sf::FloatRect(0, -arrowSize2, arrowSize, 2*arrowSize2).contains(localMousePos))
        m_directionState = DirectionState::Horizontal;
    else if(sf::FloatRect(-arrowSize2, 0, 2*arrowSize2, arrowSize).contains(localMousePos))
        m_directionState = DirectionState::Vertical;
    else return false;

    m_pressed = true;

    return false;
}

bool SceneToolTransform::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return false;
    m_pressed = false;
    return false;
}

void SceneToolTransform::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    if(m_node == nullptr)
        return;

    sf::VertexArray line(sf::Lines, 20);
    sf::VertexArray square(sf::Quads, 4);

    //horizontal arrow
    line[0].position = sf::Vector2f(0, 0);
    line[1].position = sf::Vector2f(arrowSize, 0);

    line[2].position = sf::Vector2f(arrowSize - arrowSize2, -arrowSize2);
    line[3].position = sf::Vector2f(arrowSize - arrowSize2, arrowSize2);

    line[4].position = sf::Vector2f(arrowSize, 0);
    line[5].position = sf::Vector2f(arrowSize - arrowSize2, -arrowSize2);

    line[6].position = sf::Vector2f(arrowSize, 0);
    line[7].position = sf::Vector2f(arrowSize - arrowSize2, arrowSize2);

    for(int i(0) ; i < 8 ; i++)
        line[i].color = horizontalColor;

    //vertical arrow
    line[8].position = sf::Vector2f(0, 0);
    line[9].position = sf::Vector2f(0, arrowSize);

    line[10].position = sf::Vector2f(-arrowSize2, arrowSize - arrowSize2);
    line[11].position = sf::Vector2f(arrowSize2, arrowSize - arrowSize2);

    line[12].position = sf::Vector2f(0, arrowSize);
    line[13].position = sf::Vector2f(-arrowSize2, arrowSize - arrowSize2);

    line[14].position = sf::Vector2f(0, arrowSize);
    line[15].position = sf::Vector2f(arrowSize2, arrowSize - arrowSize2);

    for(int i(8); i < 16 ; i++)
        line[i].color = verticalColor;

    //center square
    square[0].position = sf::Vector2f(0, squareSize);
    square[1].position = sf::Vector2f(squareSize, squareSize);
    square[2].position = sf::Vector2f(squareSize, 0);
    square[3].position = sf::Vector2f(0, 0);

    for(int i(0) ; i < 4 ; i++)
        square[i].color = surfaceFillColor;

    line[16].position = sf::Vector2f(0, squareSize);
    line[17].position = sf::Vector2f(squareSize, squareSize);

    line[18].position = sf::Vector2f(squareSize, 0);
    line[19].position = sf::Vector2f(squareSize, squareSize);

    for(int i(16) ; i < 20 ; i++)
        line[i].color = surfaceBorderColor;

    auto transform = m_node->getSFMLParentTransform().translate(m_node->getLocalTransform().position);

    auto pos = transform.transformPoint({0,0});
    auto rot = angle(transform.transformPoint({1, 0}) - pos);

    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));
    sf::RenderStates states;
    states.transform = t;

    target.draw(line, states);
    target.draw(square, states);
}
