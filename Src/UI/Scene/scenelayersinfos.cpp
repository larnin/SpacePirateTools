#include "scenelayersinfos.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <QMenu>

SceneLayersinfos::SceneLayersinfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , m_currentIndex(-1)
{
    initializeWidgets();
    updateColorButton();
    updateLayerList();
}

SceneLayersinfos::~SceneLayersinfos()
{
    m_datas.save(m_assetName);
}

void SceneLayersinfos::initializeWidgets()
{
    m_colorButton = new QPushButton("");
    m_colorButton->setFixedWidth(30);
    QHBoxLayout * colorLayout = new QHBoxLayout();
    colorLayout->addWidget(new QLabel("Couleur de fond :"));
    colorLayout->addWidget(m_colorButton);

    m_layers = new QListWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(colorLayout);
    layout->addSpacing(5);
    layout->addWidget(new QLabel("Layers :"));
    layout->addWidget(m_layers, 1);

    setLayout(layout);

    connect(m_colorButton, SIGNAL(clicked(bool)), this, SLOT(onColorClicked()));
    m_layers->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_layers, SIGNAL(currentRowChanged(int)), this, SLOT(onLayerIndexChange(int)));
    connect(m_layers, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onLayerRightClick(QPoint)));
}

void SceneLayersinfos::updateColorButton()
{
    constexpr int size(30);
    QPixmap map(size, size);
    auto color = m_datas.backgroundColor;
    map.fill(QColor(color.r, color.g, color.b));
    m_colorButton->setIcon(QIcon(map));
}

void SceneLayersinfos::updateLayerList()
{

}

void SceneLayersinfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void SceneLayersinfos::onColorClicked()
{
    QColor oldColor(m_datas.backgroundColor.r, m_datas.backgroundColor.g, m_datas.backgroundColor.b);
    auto color = QColorDialog::getColor(oldColor, this, "Couleur de fond");
    if(!color.isValid())
        return;

    m_datas.backgroundColor = sf::Color(color.red(), color.green(), color.blue());
    updateColorButton();
}

void SceneLayersinfos::onLayerIndexChange(int index)
{
    m_currentIndex = index;
}

void SceneLayersinfos::onLayerRightClick(QPoint point)
{
    QPoint globalPos(m_layers->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aUp(nullptr);
    QAction *aDown(nullptr);
    QAction *aRename(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentIndex >= 0 && m_currentIndex < int(m_datas.size()))
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renommer");
        if(m_currentIndex > 0)
            aUp = menu.addAction("Monter");
        if(m_currentIndex < int(m_datas.size()) - 1)
            aDown = menu.addAction("Descendre");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
        delLayer(m_currentIndex);

    if(action == aUp)
        upLayer(m_currentIndex);

    if(action == aDown)
        downLayer(m_currentIndex);

    if(action == aRename)
        renameLayer(m_currentIndex);

    if(action == aAdd)
        addLayer();
}

void SceneLayersinfos::updateGizmos(unsigned int index, bool value)
{

}

void SceneLayersinfos::updateVisibility(unsigned int index, bool value)
{

}

void SceneLayersinfos::addLayer()
{

}

void SceneLayersinfos::delLayer(unsigned int index)
{

}

void SceneLayersinfos::upLayer(unsigned int index)
{

}

void SceneLayersinfos::downLayer(unsigned int index)
{

}

void SceneLayersinfos::renameLayer(unsigned int index)
{

}

