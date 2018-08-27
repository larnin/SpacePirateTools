#include "valuerenderercamera.h"
#include <SFML/Graphics/VertexArray.hpp>

const sf::Color color(sf::Color::White);

ValueRendererCamera::ValueRendererCamera(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase(node, value)
    , m_camera(dynamic_cast<ObjectValueCamera*>(value))
{

}

void ValueRendererCamera::draw(sf::RenderTarget &) const
{

}

void ValueRendererCamera::drawGizmos(sf::RenderTarget & target) const
{
    auto size = target.getSize();

    sf::Vector2f rectSize(0, 0);
    if(m_camera->fixedSize)
    {
        rectSize.y = m_camera->value;
        rectSize.x = size.x * rectSize.y / size.y;
    }
    else
    {
        rectSize.x = size.x / m_camera->value;
        rectSize.y = size.y / m_camera->value;
    }
    rectSize /= 2.0f;

    sf::VertexArray array(sf::Lines, 8);

    array[0].position = -rectSize;
    array[1].position = sf::Vector2f(-rectSize.x, rectSize.y);
    array[2].position = sf::Vector2f(-rectSize.x, rectSize.y);
    array[3].position = rectSize;
    array[4].position = rectSize;
    array[5].position = sf::Vector2f(rectSize.x, -rectSize.y);
    array[6].position = sf::Vector2f(rectSize.x, -rectSize.y);
    array[7].position = -rectSize;

    for(unsigned int i(0) ; i < 8 ; i++)
        array[i].color = color;

    target.draw(array, getTransform());
}

void ValueRendererCamera::update()
{

}
