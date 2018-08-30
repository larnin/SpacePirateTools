#include "tilemapcollidervaluewidget.h"
#include "ProjectInfos/projectinfos.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

TilemapColliderValueWidget::TilemapColliderValueWidget(ObjectValueTilemapCollider &collider, QWidget *parent)
    : QWidget(parent)
    , m_collider(collider)
{
    m_asset = new QComboBox();
    updateAssetWidget();
    QHBoxLayout * assetLayout = new QHBoxLayout();
    assetLayout->addWidget(new QLabel("Tilemap : "));
    assetLayout->addWidget(m_asset, 1);

    m_tileSize = new QSpinBox();
    m_tileSize->setRange(1, 1000);
    m_tileSize->setValue(m_collider.tileSize);
    QHBoxLayout * tileSizeLayout = new QHBoxLayout();
    tileSizeLayout->addWidget(new QLabel("Talle de tile : "));
    tileSizeLayout->addWidget(m_tileSize, 1);

    m_offsetX = new QDoubleSpinBox();
    m_offsetX->setRange(-1000, 1000);
    m_offsetX->setDecimals(2);
    m_offsetX->setSingleStep(1);
    m_offsetX->setValue(m_collider.offset.x);
    m_offsetY = new QDoubleSpinBox();
    m_offsetX->setRange(-1000, 1000);
    m_offsetY->setDecimals(2);
    m_offsetY->setSingleStep(1);
    m_offsetY->setValue(m_collider.offset.y);
    QHBoxLayout * offsetLayout = new QHBoxLayout();
    offsetLayout->addWidget(new QLabel("Offset : X "));
    offsetLayout->addWidget(m_offsetX, 1);
    offsetLayout->addSpacing(10);
    offsetLayout->addWidget(new QLabel("Y "));
    offsetLayout->addWidget(m_offsetY, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(assetLayout);
    layout->addLayout(tileSizeLayout);
    layout->addLayout(offsetLayout);

    setLayout(layout);

    connect(m_asset, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged()));
    connect(m_tileSize, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetX, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_offsetY, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void TilemapColliderValueWidget::onValueChanged()
{
    if(m_asset->currentIndex() <= 0)
        m_collider.tilemapName = "";
    else m_collider.tilemapName = m_asset->currentText();

    m_collider.tileSize = m_tileSize->value();

    m_collider.offset.x = m_offsetX->value();
    m_collider.offset.y = m_offsetY->value();
}

void TilemapColliderValueWidget::updateAssetWidget()
{
    m_asset->blockSignals(true);

    m_asset->clear();

    m_asset->addItem("None");
    for(const auto & i : ProjectInfos::instance().fileInfos(AssetType::Tilemap))
        m_asset->addItem(i);

    m_asset->setCurrentText(m_collider.tilemapName);
    if(m_asset->currentIndex() < 0)
        m_asset->setCurrentIndex(0);

    m_asset->blockSignals(false);
}
