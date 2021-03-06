#include "centraltilemapwidget.h"
#include "MapTool/copymaptool.h"
#include "MapTool/pastemaptool.h"
#include "MapTool/singletilemaptool.h"
#include <QWheelEvent>
#include <QMouseEvent>
#include <QResizeEvent>
#include <QKeyEvent>
#include <QMenu>

constexpr unsigned int defaultZoomLevel(2);
const sf::Color gridColor(128, 128, 128, 128);

CentralTilemapWidget::CentralTilemapWidget(TilemapInfos *tilemap, QWidget *parent)
    : QSFMLCanvas(20, parent)
    , m_infos(tilemap)
    , m_renderer(tilemap->getData())
    , m_zoomLevel(defaultZoomLevel)
    , m_center(100, 100)
    , m_draging(false)
    , m_showGrid(false)
    , m_drawColliders(false)
    , m_selectionMode(false)
    , m_pickMode(false)
    , m_pasteHolder(Event<PasteEvent>::connect([this](const auto & e){onPaste(e);}))
{
    tilemap->setCentralWidget(this);
    setMouseTracking(true);
    //grabKeyboard();

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClick(QPoint)));
}

void CentralTilemapWidget::setTool(std::unique_ptr<BaseMapTool> && tool)
{
    m_tool = std::move(tool);
    if(m_tool)
    {
        m_tool->setTexture(m_texture);
        m_selectionMode = m_tool->isSelectionTool();
    }
    else if(m_selectionMode)
        setSelectionTool();
}

void CentralTilemapWidget::setTexture(const Texture & texture)
{
    m_texture = texture;
    m_renderer.setTexture(texture);
    if(m_tool)
        m_tool->setTexture(texture);
}

void CentralTilemapWidget::OnUpdate()
{
    RenderWindow::clear(sf::Color::Black);

    m_renderer.drawTiles(*this);
    if(m_drawColliders)
        m_renderer.drawColliders(*this);

    if(m_tool)
        RenderWindow::draw(*m_tool);

    if(m_showGrid)
        drawGrid();
}

void CentralTilemapWidget::wheelEvent(QWheelEvent * event)
{
    if(event->angleDelta().y() > 0 && m_zoomLevel > 0)
        m_zoomLevel--;
    if(event->angleDelta().y() < 0 && m_zoomLevel < zoomLevels().size() - 1)
        m_zoomLevel++;

    rebuildView();
}

void CentralTilemapWidget::mouseMoveEvent(QMouseEvent * event)
{
    float z(zoom());
    sf::Vector2i newPos(event->x(), event->y());
    auto delta = newPos - m_mouseOldPos;
    m_mouseOldPos = newPos;

    if(m_draging)
    {
        m_center -= sf::Vector2f(delta) / z;
        rebuildView();
        return;
    }

    if(m_tool)
    {
        auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
        event->setLocalPos(QPointF(pos.x, pos.y));
        m_tool->mouseMoveEvent(event);
    }
}

void CentralTilemapWidget::mousePressEvent(QMouseEvent * event)
{
    if(m_draging)
        return;

    m_mouseOldPos = sf::Vector2i(event->x(), event->y());

    if(event->button() == Qt::MiddleButton)
    {
        m_draging = true;
        return;
    }

    if(event->button() == Qt::LeftButton && m_pickMode)
    {
        auto eventPos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
        auto tileSize = m_infos->getData().tileSize;
        auto size = m_infos->getData().tiles.getSize();

        sf::Vector2i pos((eventPos.x + tileSize / 2) / tileSize, (eventPos.y + tileSize / 2) / tileSize);
        if(pos.x >= int(size.x) || pos.y > int(size.y) || pos.x < 0 || pos.y < 0)
            return;

        setTool(std::make_unique<SingleTileMapTool>(m_infos->getData(), m_infos->getData().tiles(sf::Vector2u(pos))));

        return;
    }

    if(m_tool)
    {
        auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
        event->setLocalPos(QPointF(pos.x, pos.y));
        m_tool->mousePressEvent(event);
    }
}

void CentralTilemapWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MiddleButton)
            m_draging = false;

    if(m_tool)
    {
        auto pos = RenderWindow::mapPixelToCoords(sf::Vector2i(event->x(), event->y()));
        event->setLocalPos(QPointF(pos.x, pos.y));
        m_tool->mouseReleaseEvent(event);
    }
}

void CentralTilemapWidget::resizeEvent(QResizeEvent * event)
{
    QWidget::resizeEvent(event);
    rebuildView();
}

void CentralTilemapWidget::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_S)
    {
        m_selectionMode = !m_selectionMode;
        if(m_selectionMode)
            setSelectionTool();
        else setTool({});
    }
    if(event->key() == Qt::Key_Escape && !m_selectionMode)
        setTool({});

    if(event->key() == Qt::Key_Shift)
        m_pickMode = true;

    if(m_tool)
        m_tool->keyPressEvent(event);
}

void CentralTilemapWidget::keyReleaseEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Shift)
        m_pickMode = false;

    if(m_tool)
        m_tool->keyReleaseEvent(event);
}

const std::vector<float> & CentralTilemapWidget::zoomLevels()
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

float CentralTilemapWidget::zoom()
{
    if(m_zoomLevel >= zoomLevels().size())
        m_zoomLevel = zoomLevels().size() - 1;
    return zoomLevels()[m_zoomLevel];
}

void CentralTilemapWidget::rebuildView()
{
    float z(zoom());

    sf::View v(RenderWindow::getView());
    v.setSize(QWidget::size().width() / z, QWidget::size().height() / z);
    v.setCenter(m_center);
    RenderWindow::setView(v);
}

void CentralTilemapWidget::drawGrid()
{
    unsigned int tileSize = m_infos->getData().tileSize;
    auto size = m_infos->getData().tiles.getSize();

    float left = -(tileSize / 2.0f);
    float right = tileSize * size.x + left;
    float top = -(tileSize / 2.0f);
    float bottom = tileSize * size.y + top;

    sf::VertexArray array(sf::Lines, (size.x + size.y + 2) * 2);

    for(unsigned int i(0) ; i <= size.x ; i++)
    {
        array[2*i].position = sf::Vector2f(left + tileSize * i, top);
        array[2*i+1].position = sf::Vector2f(left + tileSize * i, bottom);
    }
    for(unsigned int j(0) ; j <= size.y ; j++)
    {
        array[2*size.x + 2*j + 2].position = sf::Vector2f(left, top + tileSize * j);
        array[2*size.x + 2*j + 3].position = sf::Vector2f(right, top + tileSize * j);
    }

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        array[i].color = gridColor;

    RenderWindow::draw(array);
}

void CentralTilemapWidget::setSelectionTool()
{
    setTool(std::make_unique<CopyMapTool>(m_infos->getData()));
}

void CentralTilemapWidget::onRightClick(QPoint point)
{
    QMenu menu;
    QAction *aGrid(menu.addAction(m_showGrid ? "Cacher la grille" : "Afficher la grille"));
    QAction *aColliders(menu.addAction(m_drawColliders ? "Cacher les colliders" : "Afficher les colliders"));
    QAction *aSelect(menu.addAction(m_selectionMode ? "Mode dessin" : "Mode de selection"));

    QAction* action = menu.exec(point + QWidget::mapToGlobal(QPoint(0, 0)));
    if(action == nullptr)
        return;

    if(action == aGrid)
        m_showGrid = !m_showGrid;
    if(action == aColliders)
        m_drawColliders = !m_drawColliders;
    if(action == aSelect)
    {
        m_selectionMode = !m_selectionMode;
        if(m_selectionMode)
            setSelectionTool();
        else setTool({});
    }
}

void CentralTilemapWidget::onPaste(const PasteEvent &)
{
    if(!CopyMapTool::copyBuffer().empty())
        setTool(std::make_unique<PasteMapTool>(m_infos->getData(), CopyMapTool::copyBuffer()));
}
