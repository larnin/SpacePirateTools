#include "tilesetlayertoolwindow.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/linewidget.h"
#include "enumiterators.h"
#include <QTabWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>
#include <QFrame>

TilesetLayerToolWindow::TilesetLayerToolWindow(CentralSceneWindow * centralScene, TilesetLayer &layer, QWidget *parent)
    : QWidget(parent)
    , m_centralScene(centralScene)
    , m_layer(layer)
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
{
    initializeWidgets();

    updateBrushList();
    updateImageList();
    createBrushList();
    createTileColliderList();
}

void TilesetLayerToolWindow::initializeWidgets()
{
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
    m_blockView->setTexture(m_layer.texture());
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

    QWidget * singleTileHolder = new QWidget();
    QVBoxLayout * singleTileLayout = new QVBoxLayout();
    singleTileLayout->addWidget(new QLabel("Tile :"));
    singleTileLayout->addWidget(blockViewFrame, 1);
    singleTileLayout->addWidget(colliderGroup);
    singleTileHolder->setLayout(singleTileLayout);

    QTabWidget * tab = new QTabWidget();
    tab->addTab(brushsWidget, "Pinceaux");
    tab->addTab(singleTileHolder, "Tile seul");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(textureLayout);
    layout->addWidget(tab);

    setLayout(layout);

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
}

void TilesetLayerToolWindow::createBrushList()
{
    m_brushList->clear();

    if(m_layer.brushName.isEmpty())
    {
        m_tileset = std::unique_ptr<TilesetData>();
        return;
    }

    AssetType type = AssetType::Tileset;
    QString fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(type) + "/" + m_layer.brushName/* + "." + assetTypeExtension(img)*/;

    m_tileset = std::make_unique<TilesetData>(fullName);

    for(const auto & b : m_tileset->brushs)
        m_brushList->addItem(b->name + " : " + brushTypeToString(b->getBrushType()));
}

void TilesetLayerToolWindow::createTileColliderList()
{
    m_colliderType->clear();

    for(auto t : TileColliderType::Max)
        m_colliderType->addItem(tileColliderTypeToString(t));
}

void TilesetLayerToolWindow::updateImageList()
{
    m_texture->blockSignals(true);

    m_texture->clear();

    m_texture->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Image))
        m_texture->addItem(i);

    m_texture->setCurrentText(m_layer.textureName());
    if(m_texture->currentIndex() < 0)
    {
        m_texture->setCurrentIndex(0);
        m_layer.setTextureName("");
    }

    m_blockView->setTexture(m_layer.texture());

    m_texture->blockSignals(false);
}

void TilesetLayerToolWindow::updateBrushList()
{
    m_brushs->blockSignals(true);

    m_brushs->clear();

    m_brushs->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Tileset))
        m_brushs->addItem(i);

    m_brushs->setCurrentText(m_layer.brushName);
    if(m_brushs->currentIndex() < 0)
    {
        m_brushs->setCurrentIndex(0);
        m_layer.brushName = "";
    }

    createBrushList();

    m_brushs->blockSignals(false);
}

void TilesetLayerToolWindow::onTextureIndexChanged(int index)
{
    if(index <= 0)
        m_layer.setTextureName("");
    else m_layer.setTextureName(m_texture->currentText());
    m_blockView->setTexture(m_layer.texture());
}

void TilesetLayerToolWindow::onBrushIndexChanged(int index)
{
    if(index <= 0)
        m_layer.brushName = "";
    else m_layer.brushName = m_brushs->currentText();
    createBrushList();
}

void TilesetLayerToolWindow::onSelectBrush(int value)
{
    //todo
}

void TilesetLayerToolWindow::onSelectTile(unsigned int id)
{
    //todo
}

void TilesetLayerToolWindow::onColliderValueChanged()
{
    TileCollider collider;
    collider.type = tileColliderTypeFromString(m_colliderType->currentText());
    collider.xFlipped = m_xFlipped->isChecked();
    collider.yFlipped = m_yFlipped->isChecked();
    collider.rotation = m_rot0->isChecked() ? TileColliderRotation::R_0
                      : (m_rot90->isChecked() ? TileColliderRotation::R_90
                      : (m_rot180->isChecked() ? TileColliderRotation::R180
                      : TileColliderRotation::R270));

    //todo
}

void TilesetLayerToolWindow::onRename(const RenamedFileEvent &)
{
    updateImageList();
    updateBrushList();
}

void TilesetLayerToolWindow::onRemove(const RemovedFileEvent &)
{
    updateImageList();
    updateBrushList();
}

void TilesetLayerToolWindow::onAdd(const AddedFileEvent &)
{
    updateImageList();
    updateBrushList();
}
