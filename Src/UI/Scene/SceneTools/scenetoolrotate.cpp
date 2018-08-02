#include "scenetoolrotate.h"
#include "vect2convert.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Rect.hpp>

const sf::Color circleColor(sf::Color::Green);
constexpr float interCircleSize = 15;
constexpr float outerCircleSize = 20;
constexpr int segmentsCount = 50;

SceneToolRotate::SceneToolRotate(SceneNode *node)
    : SceneToolBase(node)
    , m_pressed(false)
{

}

bool SceneToolRotate::mouseMoveEvent(QMouseEvent * event)
{
    if(!m_pressed)
        return false;

    auto pos = m_node->getSFMLParentTransform().translate( m_node->getLocalTransform().position).transformPoint({0,0});
    auto rot = -angle(m_baseTransform.transformPoint({1, 0}) - m_baseTransform.transformPoint({0, 0}));
    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));

    auto localMousePos = t.getInverse().transformPoint(sf::Vector2f(event->x(), event->y()));
    auto localAngle = toDeg(angle(localMousePos));

    m_node->getLocalTransform().rotation = m_baseAngle + localAngle - m_baseMouseAngle;

    return false;
}

bool SceneToolRotate::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return false;

    m_mouseStartPos = sf::Vector2f(event->x(), event->y());
    m_baseTransform = m_node->getSFMLParentTransform().getInverse();

    m_baseAngle = m_node->getLocalTransform().rotation;

    auto pos = m_node->getSFMLParentTransform().translate( m_node->getLocalTransform().position).transformPoint({0,0});
    auto rot = -angle(m_baseTransform.transformPoint({1, 0}) - m_baseTransform.transformPoint({0, 0}));
    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));

    auto localMousePos = t.getInverse().transformPoint(m_mouseStartPos);
    m_baseMouseAngle = toDeg(angle(localMousePos));
    auto mouseDistSqr = normSqr(localMousePos);
    if(mouseDistSqr > outerCircleSize * outerCircleSize || mouseDistSqr < interCircleSize * interCircleSize)
        return false;

    m_pressed = true;

    return false;
}

bool SceneToolRotate::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return false;
    m_pressed = false;
    return false;
}

void SceneToolRotate::draw(sf::RenderTarget &target, sf::RenderStates) const
{
    if(m_node == nullptr)
        return;

    sf::VertexArray line(sf::Lines, segmentsCount * 4);
    constexpr float pi = 3.14159f;

    for(int i(0) ; i < segmentsCount ; i++)
    {
        float a1 = 2*pi*i/segmentsCount;
        float a2 = 2*pi*(i+1)/segmentsCount;

        line[4*i] = toVect(interCircleSize, a1);
        line[4*i+1] = toVect(interCircleSize, a2);
        line[4*i+2] = toVect(outerCircleSize, a1);
        line[4*i+3] = toVect(outerCircleSize, a2);
    }

    for(int i(0) ; i < segmentsCount * 4 ; i++)
        line[i].color = circleColor;

    auto transform = m_node->getSFMLParentTransform().translate(m_node->getLocalTransform().position);

    auto pos = transform.transformPoint({0,0});
    auto rot = angle(transform.transformPoint({1, 0}) - pos);

    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));
    sf::RenderStates states;
    states.transform = t;

    target.draw(line, states);
}
