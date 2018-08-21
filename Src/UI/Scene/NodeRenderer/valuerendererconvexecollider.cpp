#include "valuerendererconvexecollider.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/VertexArray.hpp>

ValueRendererConvexeCollider::ValueRendererConvexeCollider(SceneNode *node, ObjectValueBase *value)
    : ValueRendererBase(node, value)
    , m_collider(dynamic_cast<ObjectValueConvexeCollider*>(value))
{

}

void ValueRendererConvexeCollider::draw(sf::RenderTarget &) const
{

}

void ValueRendererConvexeCollider::drawGizmos(sf::RenderTarget &target) const
{
    sf::VertexArray array(sf::Lines, m_collider->points.size()*2);

    for(unsigned int i(0) ; i < m_collider->points.size() ; i++)
    {
        unsigned int lastI = i == 0 ? m_collider->points.size()-1 : i-1;
        array[2*i].position = m_collider->points[i];
        array[2*i+1].position = m_collider->points[lastI];
    }

    auto lineColor = sf::Color::White;
    if(ProjectInfos::instance().options().colliderLayers.size() > m_collider->collisionLayer)
        lineColor = ProjectInfos::instance().options().colliderLayers[m_collider->collisionLayer].color;

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = lineColor;

    target.draw(array, getTransform());
}

void ValueRendererConvexeCollider::update()
{

}
