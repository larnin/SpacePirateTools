#include "centraltilesetwindow.h"
#include "ProjectInfos/projectinfos.h"

CentralTilesetWindow::CentralTilesetWindow(TilesetInfos *infos, QWidget *parent)
    : QWidget(parent)
    , m_infos(infos)
    , m_brushWindow(nullptr)
    , m_delta(0)
    , m_size(0)
{
    m_infos->setCentralTilesetWindow(this);

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(192, 192, 192));
    setAutoFillBackground(true);
    setPalette(pal);

    m_layout = new QVBoxLayout();
    setLayout(m_layout);
}

void CentralTilesetWindow::setTexture(const QString & textureName)
{
    if(textureName.isEmpty())
        m_texture = Texture();
    else
    {
        AssetType img = AssetType::Image;
        QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(img) + "/" + textureName/* + "." + assetTypeExtension(img)*/;

        m_texture = Texture(fullName.toStdString());
    }

    if(m_brushWindow)
        m_brushWindow->setTexture(m_texture);
}

void CentralTilesetWindow::setDeltaTile(unsigned int delta)
{
    m_delta = delta;
    if(m_brushWindow)
        m_brushWindow->setDeltaTile(delta);
}

void CentralTilesetWindow::setTileSize(unsigned int size)
{
    m_size = size;
    if(m_brushWindow)
        m_brushWindow->setTileSize(size);
}

void CentralTilesetWindow::setBrushWindow(BrushWindowBase * window)
{
    if(m_brushWindow != nullptr)
    {
        m_layout->removeWidget(m_brushWindow);
        delete m_brushWindow;
    }

    m_brushWindow = window;

    if(m_brushWindow != nullptr)
    {
        m_brushWindow->setTexture(m_texture);
        m_brushWindow->setDeltaTile(m_delta);
        m_brushWindow->setTileSize(m_size);
        m_layout->addWidget(m_brushWindow);
    }
}
