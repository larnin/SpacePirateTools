#include "assetvaluewidget.h"
#include "ProjectInfos/projectinfos.h"
#include <QLabel>
#include <QHBoxLayout>

AssetValueWidget::AssetValueWidget(ObjectValueAsset &asset, QWidget *parent)
    : QWidget(parent)
    , m_asset(asset)
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
{
    m_value = new QComboBox();
    updateCombobox();

    QHBoxLayout * valueLayout = new QHBoxLayout;
    valueLayout->addWidget(new QLabel("Asset : "));
    valueLayout->addWidget(m_value, 1);

    setLayout(valueLayout);

    connect(m_value, SIGNAL(currentIndexChanged(int)), this, SLOT(onValueChanged(int)));
}

void AssetValueWidget::updateCombobox()
{
    m_value->blockSignals(true);

    m_value->clear();

    m_value->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(m_asset.getAssetType()))
        m_value->addItem(i);

    m_value->setCurrentText(m_asset.assetName);
    if(m_value->currentIndex() < 0)
    {
        m_value->setCurrentIndex(0);
    }

    m_value->blockSignals(false);
}

void AssetValueWidget::onValueChanged(int index)
{
    if(index <= 0)
        m_asset.assetName = "";
    else m_asset.assetName = m_value->currentText();
}

void AssetValueWidget::onRename(const RenamedFileEvent &)
{
    updateCombobox();
}

void AssetValueWidget::onRemove(const RemovedFileEvent &)
{
    updateCombobox();
}

void AssetValueWidget::onAdd(const AddedFileEvent &)
{
    updateCombobox();
}
