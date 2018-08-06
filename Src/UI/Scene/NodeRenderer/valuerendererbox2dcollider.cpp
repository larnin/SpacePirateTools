#include "valuerendererbox2dcollider.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

const sf::Color lineColor = sf::Color::Green;

ValueRendererBox2DCollider::ValueRendererBox2DCollider(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase(node, value)
    , m_collider(dynamic_cast<ObjectValueBox2DCollider*>(value))
{

}

void ValueRendererBox2DCollider::draw(sf::RenderTarget &) const
{

}

void ValueRendererBox2DCollider::drawGizmos(sf::RenderTarget &target) const
{
    sf::VertexArray array(sf::Lines, 8);

    array[0] = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[1] = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[2] = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[3] = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[4] = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[5] = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[6] = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[7] = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = lineColor;

    target.draw(array, getTransform());
}

void ValueRendererBox2DCollider::update()
{

}
