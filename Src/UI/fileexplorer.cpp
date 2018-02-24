#include "fileexplorer.h"
#include "ProjectInfos/assettype.h"
#include "ProjectInfos/projectinfos.h"
#include <QVBoxLayout>

FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
{
    m_tree = new QTreeWidget();
    m_tree->setHeaderHidden(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_tree);

    setLayout(layout);

    updateTree();
}

void FileExplorer::updateTree()
{
    m_tree->clear();

    if(!ProjectInfos::instance().projectLoaded())
    {
        auto item = new QTreeWidgetItem(m_tree);
        item->setText(0, "No project loaded");
        item->setDisabled(true);
        return;
    }

    for(unsigned int i(0) ; i < static_cast<unsigned int>(AssetType::Max) ; i++)
    {
        AssetType type(static_cast<AssetType>(i));
        QTreeWidgetItem * dirItem = new QTreeWidgetItem(m_tree);
        dirItem->setText(0, assetTypeToString(type));
        for(const auto & asset : ProjectInfos::instance().fileInfos(type))
        {
            auto item = new QTreeWidgetItem(dirItem);
            item->setText(0, asset);
        }
        m_tree->addTopLevelItem(dirItem);
    }
}
