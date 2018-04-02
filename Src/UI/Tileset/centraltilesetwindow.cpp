#include "centraltilesetwindow.h"
#include "ProjectInfos/projectinfos.h"

CentralTilesetWindow::CentralTilesetWindow(TilesetInfos *infos, QWidget *parent)
    : QWidget(parent)
    , m_infos(infos)
    , m_brushWindow(nullptr)
{
    m_infos->setCentralTilesetWindow(this);
    setStyleSheet("background-color:#C0C0C0;");

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
        m_layout->addWidget(m_brushWindow);
    }
}
