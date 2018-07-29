#include "centralscenewidget.h"
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

    //do stuff
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
}

void CentralSceneWidget::mousePressEvent(QMouseEvent * event)
{
    m_mouseOldPos = sf::Vector2i(event->x(), event->y());
    m_mouseStartPos = m_mouseOldPos;

    if(event->button() == Qt::MiddleButton)
        m_dragScreen = true;
}

void CentralSceneWidget::mouseReleaseEvent(QMouseEvent *)
{
    m_dragScreen = false;
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
}

