#include "tilesetinfos.h"
#include "UI/linewidget.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

TilesetInfos::TilesetInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_assetName(assetName)
    , m_tileset(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
{
    initializeWidgets();
}

TilesetInfos::~TilesetInfos()
{
    m_tileset.save(m_assetName);
}

void TilesetInfos::initializeWidgets()
{
    m_tileSize = new QSpinBox();
    m_tileSize->setRange(1, 1000);
    QHBoxLayout *tileSizeLayout = new QHBoxLayout();
    tileSizeLayout->addWidget(new QLabel("Taille de tile :"));
    tileSizeLayout->addWidget(m_tileSize);

    QLabel *tileSizeLabel = new QLabel("La taille de tile est global à la scene");
    tileSizeLabel->setStyleSheet("font-weight: bold; color: red");

    m_texture = new QComboBox();
    QHBoxLayout *textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture :"));
    textureLayout->addWidget(m_texture);

    m_delta = new QSpinBox();
    m_delta->setRange(0, 1000);
    QHBoxLayout *deltaLayout = new QHBoxLayout();
    deltaLayout->addWidget(new QLabel("Delta entre tile :"));
    deltaLayout->addWidget(m_delta);

    m_listTile = new QListWidget;

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(tileSizeLabel);
    layout->addLayout(tileSizeLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(textureLayout);
    layout->addLayout(deltaLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(new QLabel("Pinceaux :"));
    layout->addWidget(m_listTile);

    setLayout(layout);
}

void TilesetInfos::onSave(const SaveEvent &)
{
    m_tileset.save(m_assetName);
}

void TilesetInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
}

void TilesetInfos::onRemove(const RemovedFileEvent &)
{

}

void TilesetInfos::onAdd(const AddedFileEvent &)
{

}
