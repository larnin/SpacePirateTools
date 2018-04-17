#include "sceneinfos.h"
#include "UI/linewidget.h"
#include "newlayerdialog.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QPushButton>

SceneInfos::SceneInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName)
    , m_currentIndex(-1)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
{
    initializeWidgets();
    updateLayerList();
}

SceneInfos::~SceneInfos()
{
    m_datas.save(m_assetName);
}

void SceneInfos::initializeWidgets()
{
    m_sizeX = new QSpinBox();
    m_sizeX->setRange(1, 1000);
    m_sizeX->setValue(m_datas.getSize().x);
    m_sizeY = new QSpinBox();
    m_sizeY->setRange(1, 1000);
    m_sizeY->setValue(m_datas.getSize().y);
    QHBoxLayout* sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("X : "));
    sizeLayout->addWidget(m_sizeX, 1);
    sizeLayout->addSpacing(5);
    sizeLayout->addWidget(new QLabel("Y :"));
    sizeLayout->addWidget(m_sizeY, 1);

    m_layers = new QListWidget();

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Taille"));
    layout->addLayout(sizeLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(new QLabel("Layers"));
    layout->addWidget(m_layers);

    setLayout(layout);

    connect(m_sizeX, SIGNAL(editingFinished()), this, SLOT(onSizeChange()));
    connect(m_sizeY, SIGNAL(editingFinished()), this, SLOT(onSizeChange()));
    m_layers->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_layers, SIGNAL(currentRowChanged(int)), this, SLOT(onLayerIndexChange(int)));
    connect(m_layers, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onLayerRightClick(QPoint)));
}

void SceneInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void SceneInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
}

void SceneInfos::onSizeChange()
{
    m_datas.setSize(sf::Vector2u(m_sizeX->value(), m_sizeY->value()));
}

void SceneInfos::onLayerIndexChange(int index)
{

}

void SceneInfos::onLayerRightClick(QPoint point)
{
    QPoint globalPos(m_layers->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aUp(nullptr);
    QAction *aDown(nullptr);
    QAction *aRename(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentIndex >= 0 && m_currentIndex < int(m_datas.layerCount()))
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renommer");
        if(m_currentIndex > 0)
            aUp = menu.addAction("Monter");
        if(m_currentIndex < int(m_datas.layerCount()) - 1)
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

void SceneInfos::addLayer()
{
    bool ok = true;
    auto layerInfos = NewLayerDialog::getLayerInfos(this, &ok);
}

void SceneInfos::delLayer(unsigned int index)
{

}

void SceneInfos::upLayer(unsigned int index)
{

}

void SceneInfos::downLayer(unsigned int index)
{

}

void SceneInfos::renameLayer(unsigned int index)
{

}

void SceneInfos::updateLayerList()
{
    m_layers->blockSignals(true);

    m_layers->clear();

    for(unsigned int i(0) ; i < m_datas.layerCount() ; i++)
    {
        const auto & layer = m_datas.layer(i);
        m_layers->addItem(layer.name + " : " + layerTypeToString(layer.getLayerType()));
        auto item = m_layers->item(m_layers->count() - 1);

        QWidget* widget = new QWidget();
        QPushButton* showButton = new QPushButton(QIcon("Img/View.png"), "");
        QPushButton* gizmoButton = new QPushButton(QIcon("Img/Gismos.png"), "");
        QHBoxLayout* layout = new QHBoxLayout();
        layout->addWidget(showButton);
        layout->addWidget(gizmoButton);
        widget->setLayout(layout);
        m_layers->setItemWidget(item, widget);
    }

    m_layers->blockSignals(false);
}
