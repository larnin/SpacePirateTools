#include "centralscenewidget.h"
#include "vect2convert.h"
#include "SceneTools/scenetooltransform.h"
#include "SceneTools/scenetoolscale.h"
#include "SceneTools/scenetoolrotate.h"
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <QWheelEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QVBoxLayout>
#include <QHBoxLayout>

constexpr unsigned int defaultZoomLevel(2);

CentralSceneWidget::CentralSceneWidget(SceneData &data, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_data(data)
    , m_dragScreen(false)
    , m_zoomLevel(defaultZoomLevel)
    , m_center(0, 0)
    , m_selectionState(SelectionState::Move)
    , m_currentLayerIndex(-1)
    , m_currentNodeIndex(-1)
    , m_mouseMoved(false)
    , m_render(data)
{
    m_selectionWidget = new SelectionModeWidget();
    QHBoxLayout * hLayout = new QHBoxLayout();
    hLayout->addWidget(m_selectionWidget);
    hLayout->addStretch();
    hLayout->setMargin(0);
    QVBoxLayout* vLayout = new QVBoxLayout();
    vLayout->addLayout(hLayout);
    vLayout->addStretch();
    vLayout->setMargin(0);
    setLayout(vLayout);

    connect(m_selectionWidget, SIGNAL(selectionStateChanged(SelectionState)), this, SLOT(onChangeSelectionState(SelectionState)));
    connect(this, SIGNAL(selectionStateChanged(SelectionState)), m_selectionWidget, SLOT(onChangeSelectionState(SelectionState)));
}

void CentralSceneWidget::OnUpdate()
{
    RenderWindow::clear(m_data.backgroundColor);

    m_render.update();

    drawCurrentLayerPositions();
    drawVisiblelayers();
    drawCurrentLayerGizmos();

    m_render.draw(*this);
    m_render.drawGizmos(*this);

    if(m_sceneTool)
        RenderWindow::draw(*m_sceneTool);
}

void CentralSceneWidget::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0 && m_zoomLevel > 0)
        m_zoomLevel--;
    if(event->angleDelta().y() < 0 && m_zoomLevel < zoomLevels().size() - 1)
        m_zoomLevel++;

    rebuildView();
}

void CentralSceneWidget::mouseMoveEvent(QMouseEvent * event)
{
    auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
    QMouseEvent toolEvent(*event);
    toolEvent.setLocalPos(QPointF(pos.x, pos.y));

    if(!m_sceneTool || !m_sceneTool->mouseMoveEvent(&toolEvent))
    {
        float z(zoom());
        sf::Vector2i newPos(event->x(), event->y());
        auto delta = newPos - m_mouseOldPos;
        m_mouseOldPos = newPos;

        if(m_dragScreen)
        {
            m_center -= sf::Vector2f(delta) / z;
            rebuildView();
            return;
        }

        m_mouseMoved = true;
    }

    if(m_sceneTool)
        emit currentNodeMoved();
}

void CentralSceneWidget::mousePressEvent(QMouseEvent * event)
{
    auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
    QMouseEvent toolEvent(*event);
    toolEvent.setLocalPos(QPointF(pos.x, pos.y));

    if(!m_sceneTool || !m_sceneTool->mousePressEvent(&toolEvent))
    {
        m_mouseOldPos = sf::Vector2i(event->x(), event->y());
        m_mouseStartPos = m_mouseOldPos;

        if(event->button() == Qt::MiddleButton)
            m_dragScreen = true;

        m_mouseMoved = false;
    }
}

void CentralSceneWidget::mouseReleaseEvent(QMouseEvent * event)
{
    auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
    QMouseEvent toolEvent(*event);
    toolEvent.setLocalPos(QPointF(pos.x, pos.y));

    if(!m_sceneTool || !m_sceneTool->mouseReleaseEvent(&toolEvent))
    {
        m_dragScreen = false;

        if(event->button() == Qt::LeftButton && !m_mouseMoved)
        {
            int oldNode = m_currentNodeIndex;
            m_currentNodeIndex = getNextSelectableNode();
            if(oldNode != m_currentNodeIndex)
            {
                emit currentNodeChanged(m_currentNodeIndex);
                setToolCurrentNode();
            }
        }
    }
}

void CentralSceneWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

void CentralSceneWidget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_R)
    {
        emit selectionStateChanged(SelectionState::Rotate);
        onChangeSelectionState(SelectionState::Rotate);
    }
    else if(event->key() == Qt::Key_M)
    {
        emit selectionStateChanged(SelectionState::Move);
        onChangeSelectionState(SelectionState::Move);
    }
    else if(event->key() == Qt::Key_S)
    {
        emit selectionStateChanged(SelectionState::Scale);
        onChangeSelectionState(SelectionState::Scale);
    }
}

const std::vector<float> & CentralSceneWidget::zoomLevels()
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

float CentralSceneWidget::zoom()
{
    if(m_zoomLevel >= zoomLevels().size())
        m_zoomLevel = zoomLevels().size() - 1;
    return zoomLevels()[m_zoomLevel];
}

void CentralSceneWidget::rebuildView()
{
    float z(zoom());

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width() / z, QWidget::size().height() / z);
    v.setCenter(m_center);
    RenderWindow::setView(v);
}

void CentralSceneWidget::onChangeSelectionState(SelectionState state)
{
    m_selectionState = state;
    setToolCurrentNode();
}

void CentralSceneWidget::onChangeLayer(int layerIndex)
{
    m_currentLayerIndex = layerIndex;
    m_currentNodeIndex = -1;
    setToolCurrentNode();
}

void CentralSceneWidget::onChangeNode(int nodeIndex)
{
    m_currentNodeIndex = nodeIndex;
    setToolCurrentNode();
}

void CentralSceneWidget::drawCurrentLayerPositions()
{
    const sf::Color crossColor(100, 100, 100, 150);
    const int crossSize = 5;

    if(m_currentLayerIndex < 0 || m_currentLayerIndex >= static_cast<int>(m_data.size()))
        return;

    sf::VertexArray array(sf::PrimitiveType::Lines, 4);
    array[0].position = sf::Vector2f(-crossSize, 0);
    array[1].position = sf::Vector2f(crossSize, 0);
    array[2].position = sf::Vector2f(0, -crossSize);
    array[3].position = sf::Vector2f(0, crossSize);
    for(unsigned int i(0) ; i < 4 ; i++)
        array[i].color = crossColor;

    sf::RenderStates states;
    SceneLayer & layer = *m_data[m_currentLayerIndex];

    for(const auto & n : layer)
    {
        states.transform = n->getSFMLTransform();
        sf::RenderWindow::draw(array, states);
    }
}

void CentralSceneWidget::drawVisiblelayers()
{
    for(const auto & l : m_data)
    {
        if(l->hidden)
            continue;
        //draw layer
    }
}

void CentralSceneWidget::drawCurrentLayerGizmos()
{
    if(m_currentLayerIndex < 0 || m_currentLayerIndex >= static_cast<int>(m_data.size()))
        return;

    SceneLayer & layer = *m_data[m_currentLayerIndex];
    if(!layer.showGizmos)
        return;
    //draw gizmos
}

int CentralSceneWidget::getNextSelectableNode()
{
    constexpr float maxRadiusSqr = 50 * 50;

    if(m_currentLayerIndex < 0 || m_currentLayerIndex >= static_cast<int>(m_data.size()))
        return -1;

    SceneLayer & layer = *m_data[m_currentLayerIndex];

    std::vector<unsigned int> m_validIndexs;
    for(unsigned int i(0) ; i < layer.size() ; i++)
    {
        auto nodePos = layer[i]->getPosition();
        auto screenNodePos = RenderWindow::mapCoordsToPixel(nodePos);

        if(normSqr(sf::Vector2f(m_mouseOldPos - screenNodePos)) < maxRadiusSqr)
            m_validIndexs.push_back(i);
    }

    if(m_validIndexs.empty())
        return -1;

    for(auto i : m_validIndexs)
        if(static_cast<int>(i) > m_currentNodeIndex)
            return i;
    return m_validIndexs[0];
}

void CentralSceneWidget::setToolCurrentNode()
{
    if(m_sceneTool)
        m_sceneTool.reset();

    if(m_currentLayerIndex < 0 || m_currentLayerIndex >= static_cast<int>(m_data.size()))
        return;

    SceneLayer & layer = *m_data[m_currentLayerIndex];

    if(m_currentNodeIndex < 0 || m_currentNodeIndex >= static_cast<int>(layer.size()))
        return;

    switch(m_selectionState)
    {
    case SelectionState::Move:
        m_sceneTool = std::make_unique<SceneToolTransform>(layer[m_currentNodeIndex].get());
        break;
    case SelectionState::Scale:
        m_sceneTool = std::make_unique<SceneToolScale>(layer[m_currentNodeIndex].get());
        break;
    case SelectionState::Rotate:
        m_sceneTool = std::make_unique<SceneToolRotate>(layer[m_currentNodeIndex].get());
    default:
        break;
    }
}
