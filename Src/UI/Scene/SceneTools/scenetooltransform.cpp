#include "scenetooltransform.h"
#include "vect2convert.h"
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

const sf::Color horizontalColor(sf::Color::Red);
const sf::Color verticalColor(sf::Color::Green);
const sf::Color surfaceBorderColor(sf::Color::Yellow);
const sf::Color surfaceFillColor(255, 255, 0, 100);
constexpr float arrowSize = 20;
constexpr float arrowSize2 = 4;
constexpr float squareSize = 5;

SceneToolTransform::SceneToolTransform(SceneNode *node)
    : SceneToolBase(node)
{

}

bool SceneToolTransform::mouseMoveEvent(QMouseEvent * event)
{
    return false;
}

bool SceneToolTransform::mousePressEvent(QMouseEvent * event)
{
    return false;
}

bool SceneToolTransform::mouseReleaseEvent(QMouseEvent * event)
{
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

    auto transform = m_node->getSFMLTransform();

    auto pos = transform.transformPoint({0,0});
    auto rot = angle(transform.transformPoint({1, 0}) - pos);

    sf::Transform t;
    t.translate(pos).rotate(toDeg(rot));
    sf::RenderStates states;
    states.transform = t;

    target.draw(line, states);
    target.draw(square, states);
}
