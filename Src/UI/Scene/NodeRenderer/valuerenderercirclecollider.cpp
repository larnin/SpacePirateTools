#include "valuerenderercirclecollider.h"
#include "vect2convert.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

const sf::Color lineColor = sf::Color::Green;
constexpr unsigned int pointsCount = 50;
constexpr float pi = 3.14159f;

ValueRendererCircleCollider::ValueRendererCircleCollider(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase(node, value)
    , m_collider(dynamic_cast<ObjectValueCircleCollider*>(value))
{

}

void ValueRendererCircleCollider::draw(sf::RenderTarget &) const
{

}

void ValueRendererCircleCollider::drawGizmos(sf::RenderTarget &target) const
{
    sf::VertexArray array(sf::Lines, pointsCount*2);

    for(unsigned int i(0) ; i < pointsCount ; i++)
    {
        float a1 = pi * 2 *(i+1) / pointsCount;
        float a2 = pi * 2 * i / pointsCount;

        array[2*i] = toVect(m_collider->size, a1) + m_collider->center;
        array[2*i+1] = toVect(m_collider->size, a2) + m_collider->center;
    }

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = lineColor;

    target.draw(array, getTransform());
}

void ValueRendererCircleCollider::update()
{

}
