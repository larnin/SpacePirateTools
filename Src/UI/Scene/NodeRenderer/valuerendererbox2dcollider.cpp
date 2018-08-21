#include "valuerendererbox2dcollider.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/VertexArray.hpp>

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

    array[0].position = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[1].position = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[2].position = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);
    array[3].position = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[4].position = sf::Vector2f(-m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[5].position = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[6].position = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, -m_collider->size.y /2 + m_collider->center.y);
    array[7].position = sf::Vector2f(m_collider->size.x /2 + m_collider->center.x, m_collider->size.y /2 + m_collider->center.y);

    auto lineColor = sf::Color::White;
    if(ProjectInfos::instance().options().colliderLayers.size() > m_collider->collisionLayer)
        lineColor = ProjectInfos::instance().options().colliderLayers[m_collider->collisionLayer].color;

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = lineColor;

    target.draw(array, getTransform());
}

void ValueRendererBox2DCollider::update()
{

}
