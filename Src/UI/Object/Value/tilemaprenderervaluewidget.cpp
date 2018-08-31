#include "tilemaprenderervaluewidget.h"
#include "ProjectInfos/projectinfos.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

TilemapRendererValueWidget::TilemapRendererValueWidget(ObjectValueTilemapRenderer & tilemap, QWidget * parent)
    : QWidget (parent)
    , m_data(tilemap)
{
    m_tilemap = new QComboBox();
    updateTilemapWidget();
    QHBoxLayout * tilemapLayout = new QHBoxLayout();
    tilemapLayout->addWidget(new QLabel("Tilemap : "));
    tilemapLayout->addWidget(m_tilemap, 1);

    m_texture = new QComboBox();
    updateTextureWidget();
    QHBoxLayout * textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture : "));
    textureLayout->addWidget(m_texture, 1);

    m_size = new QSpinBox();
    m_size->setRange(1, 1000);
    m_size->setValue(m_data.tileSize);
    QHBoxLayout * sizeLayout = new QHBoxLayout();
    sizeLayout->addWidget(new QLabel("Taille de tile : "));
    sizeLayout->addWidget(m_size, 1);

    m_delta = new QSpinBox();
    m_delta->setRange(0, 1000);
    m_delta->setValue(m_data.tileDelta);
    QHBoxLayout * deltaLayout = new QHBoxLayout();
    deltaLayout->addWidget(new QLabel("Delta entre tile : "));
    deltaLayout->addWidget(m_delta, 1);

    m_offsetX = new QDoubleSpinBox();
    m_offsetX->setRange(-1000, 1000);
    m_offsetX->setDecimals(2);
    m_offsetX->setSingleStep(1);
    m_offsetX->setValue(m_data.offset.x);
    m_offsetY = new QDoubleSpinBox();
    m_offsetX->setRange(-1000, 1000);
    m_offsetY->setDecimals(2);
    m_offsetY->setSingleStep(1);
    m_offsetY->setValue(m_data.offset.y);
    QHBoxLayout * offsetLayout = new QHBoxLayout();
    offsetLayout->addWidget(new QLabel("Offset : X "));
    offsetLayout->addWidget(m_offsetX, 1);
    offsetLayout->addSpacing(10);
    offsetLayout->addWidget(new QLabel("Y "));
    offsetLayout->addWidget(m_offsetY, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(tilemapLayout);
    layout->addLayout(textureLayout);
    layout->addLayout(sizeLayout);
    layout->addLayout(deltaLayout);
    layout->addLayout(offsetLayout);

    setLayout(layout);

    connect(m_tilemap, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
    connect(m_texture, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
    connect(m_size, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_delta, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}


void TilemapRendererValueWidget::onValueChanged()
{
    if(m_tilemap->currentIndex() <= 0)
        m_data.tilemapName = "";
    else m_data.tilemapName = m_tilemap->currentText();

    if(m_texture->currentIndex() <= 0)
        m_data.textureName = "";
    else m_data.textureName = m_texture->currentText();

    m_data.tileSize = m_size->value();
    m_data.tileDelta = m_delta->value();

    m_data.offset.x = m_offsetX->value();
    m_data.offset.y = m_offsetY->value();
}

void TilemapRendererValueWidget::updateTilemapWidget()
{
    m_tilemap->blockSignals(true);

    m_tilemap->clear();

    m_tilemap->addItem("None");
    for(const auto & i : ProjectInfos::instance().fileInfos(AssetType::Tilemap))
        m_tilemap->addItem(i);

    m_tilemap->setCurrentText(m_data.tilemapName);
    if(m_tilemap->currentIndex() < 0)
        m_tilemap->setCurrentIndex(0);

    m_tilemap->blockSignals(false);
}

void TilemapRendererValueWidget::updateTextureWidget()
{
    m_texture->blockSignals(true);

    m_texture->clear();

    m_texture->addItem("None");
    for(const auto & i : ProjectInfos::instance().fileInfos(AssetType::Image))
        m_texture->addItem(i);

    m_texture->setCurrentText(m_data.textureName);
    if(m_texture->currentIndex() < 0)
        m_texture->setCurrentIndex(0);

    m_texture->blockSignals(false);
}
