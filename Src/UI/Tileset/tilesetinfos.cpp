#include "tilesetinfos.h"
#include "UI/linewidget.h"
#include "ProjectInfos/projectinfos.h"
#include "brushcreatedialog.h"
#include "centraltilesetwindow.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <QInputDialog>

TilesetInfos::TilesetInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_centralWindow(nullptr)
    , m_assetName(assetName)
    , m_datas(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
    , m_currentTile(-1)
{
    initializeWidgets();
    updateImageList();
    updateBrushList();
    updateValues();
}

TilesetInfos::~TilesetInfos()
{
    m_datas.save(m_assetName);
}

void TilesetInfos::initializeWidgets()
{
    m_tileSize = new QSpinBox();
    m_tileSize->setRange(1, 1000);
    QHBoxLayout *tileSizeLayout = new QHBoxLayout();
    tileSizeLayout->addWidget(new QLabel("Taille de tile :"));
    tileSizeLayout->addWidget(m_tileSize);

    m_delta = new QSpinBox();
    m_delta->setRange(0, 1000);
    QHBoxLayout *deltaLayout = new QHBoxLayout();
    deltaLayout->addWidget(new QLabel("Delta entre tile :"));
    deltaLayout->addWidget(m_delta);

    m_texture = new QComboBox();
    QHBoxLayout *textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture :"));
    textureLayout->addWidget(m_texture);

    m_listTile = new QListWidget;

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(tileSizeLayout);
    layout->addLayout(deltaLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(textureLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(new QLabel("Pinceaux :"));
    layout->addWidget(m_listTile);

    setLayout(layout);

    m_listTile->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_listTile, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClickBrush(QPoint)));

    connect(m_listTile, SIGNAL(currentRowChanged(int)), this, SLOT(onBrushSelected(int)));
    connect(m_delta, SIGNAL(valueChanged(int)), this, SLOT(onDeltaChanged()));
    connect(m_tileSize, SIGNAL(valueChanged(int)), this, SLOT(onTileSizeChanged()));
    connect(m_texture, SIGNAL(currentIndexChanged(int)), this, SLOT(onImageSelected(int)));
}

void TilesetInfos::updateImageList()
{
    m_texture->blockSignals(true);

    m_texture->clear();

    m_texture->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Image))
        m_texture->addItem(i);

    m_texture->setCurrentText(m_datas.imageName);
    if(m_texture->currentIndex() < 0)
    {
        m_texture->setCurrentIndex(0);
        m_datas.imageName = "";
    }
    if(m_centralWindow != nullptr)
        m_centralWindow->setTexture(m_datas.imageName);

    m_texture->blockSignals(false);
}

void TilesetInfos::updateBrushList()
{
    m_listTile->blockSignals(true);

    m_listTile->clear();

    for(const auto & b : m_datas.brushs)
        m_listTile->addItem(brushTypeToString(b->getBrushType()) + " - " + b->name);

    if(m_currentTile < m_listTile->count())
        m_listTile->setCurrentRow(m_currentTile);
    else m_currentTile = -1;

    m_listTile->blockSignals(false);
}

void TilesetInfos::updateValues()
{
    m_delta->blockSignals(true);
    m_tileSize->blockSignals(true);

    m_delta->setValue(m_datas.tileDelta);
    m_tileSize->setValue(m_datas.tileSize);

    m_delta->blockSignals(false);
    m_tileSize->blockSignals(false);
}

void TilesetInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void TilesetInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
    updateImageList();
}

void TilesetInfos::onRemove(const RemovedFileEvent &)
{
    updateImageList();
}

void TilesetInfos::onAdd(const AddedFileEvent &)
{
    updateImageList();
}

void TilesetInfos::onBrushSelected(int index)
{
    m_currentTile = index;

    if(m_centralWindow != nullptr)
    {
        if(m_currentTile >= 0 && m_currentTile < int(m_datas.brushs.size()))
            m_centralWindow->setBrushWindow(m_datas.brushs[m_currentTile]->getBrushWindows());
        else m_centralWindow->setBrushWindow(nullptr);
    }
}

void TilesetInfos::onRightClickBrush(QPoint point)
{
    QPoint globalPos(m_listTile->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aRename(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentTile >= 0 && m_currentTile < int(m_datas.brushs.size()))
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renommer");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
    {
        auto result = QMessageBox::question(this, "Supprimer", "Voulez vous vraiment supprimer " + m_datas.brushs[m_currentTile]->name + " ?");
        if(result != QMessageBox::Yes)
            return;

        m_datas.brushs.erase(m_datas.brushs.begin() + m_currentTile);
        m_currentTile = - 1;
        updateBrushList();
    }

    if(action == aRename)
    {
        bool ok;
        auto name = QInputDialog::getText(this, "Rename", "Donner un nouveau nom pour le pinceau " + m_datas.brushs[m_currentTile]->name, QLineEdit::Normal, m_datas.brushs[m_currentTile]->name, &ok);
        if(!ok)
            return;
        m_datas.brushs[m_currentTile]->name = name;
        updateBrushList();
    }

    if(action == aAdd)
    {
        bool ok;
        auto value = BrushCreateDialog::getBrush(this, &ok);
        if(!ok)
            return;
        m_datas.brushs.push_back(BrushBase::createBrush(value.type, value.name));
        updateBrushList();
    }
}

void TilesetInfos::onTileSizeChanged()
{
    m_datas.tileSize = m_tileSize->value();
    if(m_centralWindow != nullptr)
        m_centralWindow->setTileSize(m_datas.tileSize);
}

void TilesetInfos::onDeltaChanged()
{
    m_datas.tileDelta = m_delta->value();
    if(m_centralWindow != nullptr)
        m_centralWindow->setDeltaTile(m_datas.tileDelta);
}

void TilesetInfos::onImageSelected(int index)
{
    if(index <= 0)
        m_datas.imageName = "";
    else m_datas.imageName = m_texture->currentText();
    if(m_centralWindow != nullptr)
        m_centralWindow->setTexture(m_datas.imageName);
}

void TilesetInfos::setCentralTilesetWindow(CentralTilesetWindow * w)
{
    m_centralWindow = w;
    w->setTexture(m_datas.imageName);
    w->setDeltaTile(m_datas.tileDelta);
    w->setTileSize(m_datas.tileSize);
}
