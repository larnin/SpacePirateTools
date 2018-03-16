#include "centralanimatorwidget.h"
#include "vect2convert.h"
#include <QMouseEvent>
#include <QResizeEvent>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>

const sf::Color backgroundColor(60, 60, 60);
const sf::Color smallLineColor(45, 45, 45);
const sf::Color bigLineColor(30, 30, 30);
const sf::Color centerColor(200, 200, 200);
const sf::Color textColor(sf::Color::Black);
const sf::Color boxFillColor(180, 180, 180);
const sf::Color boxStartFillColor(255, 180, 130);
const sf::Color boxBorderColor(sf::Color::Black);
const sf::Color boxSelectedBorderColor(0, 255, 0);
const sf::Color transitionColor(sf::Color::White);
const sf::Color transitionSelectedColor(0, 255, 0);
constexpr unsigned int boxBoder(1);
constexpr unsigned int boxSelectedBorder(2);
constexpr int step(25);
constexpr int bigStep(10);
constexpr float crossSize(25);
constexpr float borderDelta(8);
constexpr float transitionOffset(5);
constexpr float arrowSize(10);
constexpr unsigned int characterSize(25);
constexpr int textMarge(15);
constexpr int textHeight(50);

CentralAnimatorWidget::CentralAnimatorWidget(AnimatorInfos *infos, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_infos(infos)
    , m_drag(DragType::None)
    , m_center(0, 0)
{
    m_font.loadFromFile("calibrib.ttf");
    rebuildView();
}

void CentralAnimatorWidget::OnUpdate()
{
    RenderWindow::clear(backgroundColor);

    RenderWindow::draw(drawGrid());

    drawTransitions();
    drawStates();
}

void CentralAnimatorWidget::mouseMoveEvent(QMouseEvent * event)
{
    if(m_drag == DragType::None)
        return;

    sf::Vector2i newPos(event->x(), event->y());
    auto delta = newPos - m_mouseOldPos;
    m_mouseOldPos = newPos;

    if(m_drag == DragType::Screen)
    {
        m_center -= sf::Vector2f(delta);
        rebuildView();
        return;
    }
}

void CentralAnimatorWidget::mousePressEvent(QMouseEvent * event)
{
    if(m_drag != DragType::None)
        return;

    m_mouseOldPos = sf::Vector2i(event->x(), event->y());

    if(event->button() == Qt::RightButton)
        m_drag = DragType::Screen;
}

void CentralAnimatorWidget::mouseReleaseEvent(QMouseEvent *)
{
    if(m_drag != DragType::Transition)
        m_drag = DragType::None;
}

void CentralAnimatorWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

void CentralAnimatorWidget::onRightClick(QPoint point)
{

}

void  CentralAnimatorWidget::rebuildView()
{
    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width(), QWidget::size().height());
    v.setCenter(m_center);
    RenderWindow::setView(v);
}

sf::VertexArray CentralAnimatorWidget::drawGrid() const
{
    sf::View v = RenderWindow::getView();

    sf::Vector2f min = v.getCenter() - v.getSize() / 2.0f;
    sf::Vector2f max = v.getCenter() + v.getSize() / 2.0f;

    sf::Vector2i minStep(min.x / step - 1, min.y / step - 1);
    sf::Vector2i maxStep(max.x / step + 1, max.y / step + 1);

    sf::VertexArray array(sf::Lines);

    for(int i(minStep.x) ; i < maxStep.x ; i++)
    {
        array.append(sf::Vertex(sf::Vector2f(i * step, min.y), i % bigStep == 0 ? bigLineColor : smallLineColor));
        array.append(sf::Vertex(sf::Vector2f(i * step, max.y), i % bigStep == 0 ? bigLineColor : smallLineColor));
    }

    for(int i(minStep.y) ; i < maxStep.y ; i++)
    {
        array.append(sf::Vertex(sf::Vector2f(min.x, i * step), i % bigStep == 0 ? bigLineColor : smallLineColor));
        array.append(sf::Vertex(sf::Vector2f(max.x, i * step), i % bigStep == 0 ? bigLineColor : smallLineColor));
    }

    if(sf::FloatRect(min, max - min).contains(0, 0))
    {
        array.append(sf::Vertex(sf::Vector2f(-crossSize, 0), centerColor));
        array.append(sf::Vertex(sf::Vector2f(crossSize, 0), centerColor));
        array.append(sf::Vertex(sf::Vector2f(0, -crossSize), centerColor));
        array.append(sf::Vertex(sf::Vector2f(0, crossSize), centerColor));
    }
    else
    {
        auto fCorners([](sf::VertexArray & array, const sf::Vector2f & pos, const sf::Vector2f & side)
        {
            array.append(sf::Vertex(pos, centerColor));
            array.append(sf::Vertex(pos + sf::Vector2f(crossSize * side.x, 0), centerColor));
            array.append(sf::Vertex(pos, centerColor));
            array.append(sf::Vertex(pos + sf::Vector2f(0, crossSize * side.y), centerColor));
        });
        auto fBorders([](sf::VertexArray & array, const sf::Vector2f & pos, const sf::Vector2f & side)
        {
           array.append(sf::Vertex(pos + side * crossSize, centerColor));
           array.append(sf::Vertex(pos - side * crossSize, centerColor));
        });

        if(min.x > 0 && min.y > 0)
            fCorners(array, sf::Vector2f(min.x + borderDelta, min.y + borderDelta), sf::Vector2f(1, 1));
        else if(min.x > 0 && max.y < 0)
            fCorners(array, sf::Vector2f(min.x + borderDelta, max.y - borderDelta), sf::Vector2f(1, -1));
        else if(max.x < 0 && max.y < 0)
            fCorners(array, sf::Vector2f(max.x - borderDelta, max.y - borderDelta), sf::Vector2f(-1, -1));
        else if(max.x < 0 && min.y > 0)
            fCorners(array, sf::Vector2f(max.x - borderDelta, min.y + borderDelta), sf::Vector2f(-1, 1));
        else if(min.x > 0)
            fBorders(array, sf::Vector2f(min.x + borderDelta, 0), sf::Vector2f(0, 1));
        else if(max.x < 0)
            fBorders(array, sf::Vector2f(max.x - borderDelta, 0), sf::Vector2f(0, 1));
        else if(min.y > 0)
            fBorders(array, sf::Vector2f(0, min.y + borderDelta), sf::Vector2f(1, 0));
        else if(max.y < 0)
            fBorders(array, sf::Vector2f(0, max.y - borderDelta), sf::Vector2f(1, 0));
    }

    return array;
}

void CentralAnimatorWidget::drawTransitions()
{
    sf::VertexArray array(sf::Lines);

    const auto & transitions = m_infos->getAnimatorData().transitions;
    const auto & states = m_infos->getAnimatorData().states;

    for(unsigned int i(0) ; i < transitions.size() ; i++)
    {
        sf::Color color = i == m_infos->getSelectedTransitionID() ? transitionSelectedColor : transitionColor;

        bool haveOtherTransition(false);
        for(unsigned int j(0) ; j < transitions.size() ; j++)
        {
            if(transitions[i].previousState == transitions[j].nextState && transitions[i].nextState == transitions[j].previousState)
            {
                haveOtherTransition = true;
                break;
            }
        }

        const AnimatorState & startState = states[transitions[i].previousState];
        const AnimatorState & endState = states[transitions[i].nextState];

        sf::Vector2f start(startState.rect.left + startState.rect.width / 2, startState.rect.top + startState.rect.height / 2);
        sf::Vector2f end(endState.rect.left + endState.rect.width / 2, endState.rect.top + endState.rect.height / 2);

        if(haveOtherTransition)
        {
            sf::Vector2f dir = ortho(normalize(end - start)) * transitionOffset;
            start += dir;
            end += dir;
        }

        array.append(sf::Vertex(start, color));
        array.append(sf::Vertex(end, color));

        sf::Vector2f center = (start + end) / 2.0f;

        float a = angle(end - start);
        int nbPoints(3);
        for(int i(0) ; i < nbPoints; i++)
        {
            array.append(sf::Vertex(center + toVect(arrowSize, a + 3.14159 * 2 / nbPoints * i), color));
            array.append(sf::Vertex(center + toVect(arrowSize, a + 3.14159 * 2 / nbPoints * (i + 1)), color));
        }
    }

    RenderWindow::draw(array);
}

void CentralAnimatorWidget::drawStates()
{
    for(unsigned int i(0) ; i < m_infos->getAnimatorData().states.size() ; i++)
    {
        AnimatorState & s = m_infos->getAnimatorData().states[i];

        sf::Text text(s.stateName.toStdString(), m_font, characterSize);
        text.setFillColor(textColor);
        s.rect.width = int((text.getGlobalBounds().width + 2 * textMarge + step) / step) * step;
        s.rect.height = textHeight;

        sf::RectangleShape shape(sf::Vector2f(s.rect.width, s.rect.height));
        shape.setPosition(s.rect.left, s.rect.top);

        if(i == m_infos->getAnimatorData().startIndex)
            shape.setFillColor(boxStartFillColor);
        else shape.setFillColor(boxFillColor);

        if(m_infos->getSelectedStateID() == int(i))
        {
            shape.setOutlineColor(boxSelectedBorderColor);
            shape.setOutlineThickness(boxSelectedBorder);
        }
        else
        {
            shape.setOutlineColor(boxBorderColor);
            shape.setOutlineThickness(boxBoder);
        }

        RenderWindow::draw(shape);

        auto bound = text.getGlobalBounds();
        text.setPosition(-bound.left + s.rect.left + (s.rect.width - bound.width) / 2, -bound.top + s.rect.top + (s.rect.height - bound.height) / 2);
        RenderWindow::draw(text);
    }
}
