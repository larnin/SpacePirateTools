#include "tilemapinfos.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/linewidget.h"
#include "enumiterators.h"
//#include "Scene/Tools/singletilescenetool.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>
#include <QPushButton>

TilemapInfos::TilemapInfos(const QString &filename, QWidget* parent)
    : QWidget(parent)
    , m_centralWidget(nullptr)
    , m_filename(filename)
    , m_data(filename)
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
{
    loadTexture();

    initializeWidgets();

    updateBrushList();
    updateImageList();
    createBrushList();
    createTileColliderList();
}

TilemapInfos::~TilemapInfos()
{
    m_data.save(m_filename);
}

void TilemapInfos::initializeWidgets()
{
    m_sizeX = new QSpinBox();
    m_sizeX->setRange(1, 1000);
    m_sizeX->setValue(m_data.tiles.getSize().x);
    m_sizeY = new QSpinBox();
    m_sizeY->setRange(1, 1000);
    m_sizeY->setValue(m_data.tiles.getSize().y);
    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Taille : "));
    sizeLayout->addWidget(new QLabel("X"));
    sizeLayout->addWidget(m_sizeX, 1);
    sizeLayout->addSpacing(10);
    sizeLayout->addWidget(new QLabel("Y"));
    sizeLayout->addWidget(m_sizeY, 1);

    m_tileSize = new QSpinBox();
    m_tileSize->setRange(1, 1024);
    m_tileSize->setValue(m_data.tileSize);
    m_tileDelta = new QSpinBox();
    m_tileDelta->setRange(0, 1024);
    m_tileDelta->setValue(m_data.tileDelta);
    QHBoxLayout * tileSizeLayout = new QHBoxLayout();
    tileSizeLayout->addWidget(new QLabel("Taille tile : "));
    tileSizeLayout->addWidget(m_tileSize, 1);
    QHBoxLayout * tileDeltaLayout = new QHBoxLayout();
    tileDeltaLayout->addWidget(new QLabel("Delta tile : "));
    tileDeltaLayout->addWidget(m_tileDelta, 1);

    m_texture = new QComboBox();
    QHBoxLayout * textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture : "));
    textureLayout->addWidget(m_texture, 1);

    m_brushs = new QComboBox();
    QHBoxLayout * brushLayout = new QHBoxLayout();
    brushLayout->addWidget(new QLabel("Tileset : "));
    brushLayout->addWidget(m_brushs, 1);

    m_brushList = new QListWidget();

    QWidget * brushsWidget = new QWidget();
    QVBoxLayout* brushsLayout  = new QVBoxLayout();
    brushsLayout->addLayout(brushLayout);
    brushsLayout->addWidget(m_brushList);
    brushsWidget->setLayout(brushsLayout);

    m_blockView = new BlockView();
    m_blockView->setTexture(m_tilesTexture);
    m_blockView->setTileSize(m_data.tileSize);
    m_blockView->setTileDelta(m_data.tileDelta);
    QFrame * blockViewFrame = new QFrame();
    blockViewFrame->setFrameShape(QFrame::Box);
    QVBoxLayout * blockviewLayout = new QVBoxLayout();
    blockviewLayout->addWidget(m_blockView);
    blockViewFrame->setLayout(blockviewLayout);

    m_colliderType = new QComboBox();
    QHBoxLayout * colliderTypeLayout = new QHBoxLayout();
    colliderTypeLayout->addWidget(new QLabel("Collider type :"));
    colliderTypeLayout->addWidget(m_colliderType, 1);

    m_xFlipped = new QCheckBox("X");
    m_yFlipped = new QCheckBox("Y");

    QHBoxLayout * flipLayout = new QHBoxLayout();
    flipLayout->addWidget(new QLabel("Flip : "));
    flipLayout->addWidget(m_xFlipped);
    flipLayout->addSpacing(10);
    flipLayout->addWidget(m_yFlipped);

    m_rot0 = new QRadioButton("0");
    m_rot0->setChecked(true);
    m_rot90 = new QRadioButton("90");
    m_rot180 = new QRadioButton("180");
    m_rot270 = new QRadioButton("270");

    QGroupBox* radioGroup = new QGroupBox("Rotation");
    QHBoxLayout* radioLayout = new QHBoxLayout();
    radioLayout->addWidget(m_rot0);
    radioLayout->addWidget(m_rot90);
    radioLayout->addWidget(m_rot180);
    radioLayout->addWidget(m_rot270);
    radioGroup->setLayout(radioLayout);

    QGroupBox* colliderGroup = new QGroupBox("Collider");
    QVBoxLayout * colliderLayout = new QVBoxLayout();
    colliderLayout->addLayout(colliderTypeLayout);
    colliderLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    colliderLayout->addLayout(flipLayout);
    colliderLayout->addWidget(radioGroup);
    colliderGroup->setLayout(colliderLayout);

    QPushButton * selectButton = new QPushButton("Select");
    m_autoSelect = new QCheckBox("auto");
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(selectButton, 1);
    buttonLayout->addWidget(m_autoSelect);

    QWidget * singleTileHolder = new QWidget();
    QVBoxLayout * singleTileLayout = new QVBoxLayout();
    singleTileLayout->addWidget(new QLabel("Tile :"));
    singleTileLayout->addWidget(blockViewFrame, 1);
    singleTileLayout->addWidget(colliderGroup);
    singleTileLayout->addLayout(buttonLayout);
    singleTileHolder->setLayout(singleTileLayout);

    QTabWidget * tab = new QTabWidget();
    tab->addTab(brushsWidget, "Pinceaux");
    tab->addTab(singleTileHolder, "Tile seul");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(sizeLayout);
    layout->addLayout(textureLayout);
    layout->addLayout(tileSizeLayout);
    layout->addLayout(tileDeltaLayout);
    layout->addWidget(tab);

    setLayout(layout);

    connect(m_sizeX, SIGNAL(editingFinished()), this, SLOT(onSizeChanged()));
    connect(m_sizeY, SIGNAL(editingFinished()), this, SLOT(onSizeChanged()));
    connect(m_tileSize, SIGNAL(editingFinished()), this, SLOT(onTileSizeChanged()));
    connect(m_tileDelta, SIGNAL(editingFinished()), this, SLOT(onTileSizeChanged()));
    connect(m_texture, SIGNAL(currentIndexChanged(int)), this, SLOT(onTextureIndexChanged(int)));
    connect(m_brushs, SIGNAL(currentIndexChanged(int)), this, SLOT(onBrushIndexChanged(int)));
    connect(m_brushList, SIGNAL(currentRowChanged(int)), this, SLOT(onSelectBrush(int)));
    connect(m_blockView, SIGNAL(selectBlock(uint)), this, SLOT(onSelectTile(uint)));
    connect(m_colliderType, SIGNAL(currentIndexChanged(int)), this, SLOT(onColliderValueChanged()));
    connect(m_rot0, SIGNAL(clicked(bool)), this, SLOT(onColliderValueChanged()));
    connect(m_rot90, SIGNAL(clicked(bool)), this, SLOT(onColliderValueChanged()));
    connect(m_rot180, SIGNAL(clicked(bool)), this, SLOT(onColliderValueChanged()));
    connect(m_rot270, SIGNAL(clicked(bool)), this, SLOT(onColliderValueChanged()));
    connect(m_xFlipped, SIGNAL(toggled(bool)), this, SLOT(onColliderValueChanged()));
    connect(m_yFlipped, SIGNAL(toggled(bool)), this, SLOT(onColliderValueChanged()));
    connect(selectButton, SIGNAL(clicked(bool)), this, SLOT(onTileValidSelection()));
}

void TilemapInfos::createBrushList()
{
    m_brushList->clear();

    if(m_data.brushName.isEmpty())
    {
        m_tileset = std::unique_ptr<TilesetData>();
        return;
    }

    AssetType type = AssetType::Tileset;
    QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(type) + "/" + m_data.brushName;

    m_tileset = std::make_unique<TilesetData>(fullName);

    for(const auto & b : m_tileset->brushs)
        m_brushList->addItem(b->name + " : " + brushTypeToString(b->getBrushType()));
}

void TilemapInfos::createTileColliderList()
{
    m_colliderType->clear();

    for(auto t : TileColliderType::Max)
        m_colliderType->addItem(tileColliderTypeToString(t));
}

void TilemapInfos::updateImageList()
{
    m_texture->blockSignals(true);

    m_texture->clear();

    m_texture->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Image))
        m_texture->addItem(i);

    m_texture->setCurrentText(m_data.textureName);
    if(m_texture->currentIndex() < 0)
    {
        m_texture->setCurrentIndex(0);
        m_data.textureName = "";
        loadTexture();
    }

    m_blockView->setTexture(m_tilesTexture);

    m_texture->blockSignals(false);
}

void TilemapInfos::updateBrushList()
{
    m_brushs->blockSignals(true);

    m_brushs->clear();

    m_brushs->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Tileset))
        m_brushs->addItem(i);

    m_brushs->setCurrentText(m_data.brushName);
    if(m_brushs->currentIndex() < 0)
    {
        m_brushs->setCurrentIndex(0);
        m_data.brushName = "";
    }

    createBrushList();

    m_brushs->blockSignals(false);
}

void TilemapInfos::onTextureIndexChanged(int index)
{
    if(index <= 0)
        m_data.textureName = "";
    else m_data.textureName = m_texture->currentText();
    loadTexture();
    m_blockView->setTexture(m_tilesTexture);
}

void TilemapInfos::onBrushIndexChanged(int index)
{
    if(index <= 0)
        m_data.brushName = "";
    else m_data.brushName = m_brushs->currentText();
    createBrushList();
}

void TilemapInfos::onSelectBrush(int value)
{
    /*if(value >= int(m_tileset->brushs.size()) || value < 0)
        m_centralScene->setTool({});
    else m_centralScene->setTool(m_tileset->brushs[value]->getSceneTool(m_layer));*/
}

void TilemapInfos::onSelectTile(unsigned int)
{
    if(m_autoSelect->isChecked())
        onTileValidSelection();
}

void TilemapInfos::onColliderValueChanged()
{
    if(m_autoSelect->isChecked())
        onTileValidSelection();
}

void TilemapInfos::onTileValidSelection()
{
    TileCollider collider;
    collider.type = tileColliderTypeFromString(m_colliderType->currentText());
    collider.xFlipped = m_xFlipped->isChecked();
    collider.yFlipped = m_yFlipped->isChecked();
    collider.rotation = m_rot0->isChecked() ? TileColliderRotation::R_0
                      : (m_rot90->isChecked() ? TileColliderRotation::R_90
                      : (m_rot180->isChecked() ? TileColliderRotation::R180
                      : TileColliderRotation::R270));

    //m_centralScene->setTool(std::make_unique<SingleTileSceneTool>(m_layer, TileInfos{m_blockView->getCurrentBlock(), collider}));
}


void TilemapInfos::onSizeChanged()
{
    m_data.tiles.resize(sf::Vector2u(m_sizeX->value(), m_sizeY->value()));
}

void TilemapInfos::onTileSizeChanged()
{
    m_data.tileSize = m_tileSize->value();
    m_data.tileDelta = m_tileDelta->value();

    m_blockView->setTileSize(m_data.tileSize);
    m_blockView->setTileDelta(m_data.tileDelta);
}

void TilemapInfos::onRename(const RenamedFileEvent &)
{
    updateImageList();
    updateBrushList();
}

void TilemapInfos::onRemove(const RemovedFileEvent &)
{
    updateImageList();
    updateBrushList();
}

void TilemapInfos::onAdd(const AddedFileEvent &)
{
    updateImageList();
    updateBrushList();
}


void TilemapInfos::onSave(const SaveEvent &)
{
    m_data.save(m_filename);
}

void TilemapInfos::loadTexture()
{
    if(m_data.textureName == "")
        m_tilesTexture = Texture();
    else m_tilesTexture = Texture((ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(AssetType::Image) + "/" + m_data.textureName).toStdString());
}
