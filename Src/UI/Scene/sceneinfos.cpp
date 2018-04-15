#include "sceneinfos.h"
#include "UI/linewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

SceneInfos::SceneInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName), saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
{
    initializeWidgets();
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
