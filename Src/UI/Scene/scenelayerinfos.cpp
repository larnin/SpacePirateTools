#include "scenelayerinfos.h"
#include "addnodedialog.h"
#include "Scene/scenedata.h"
#include "ProjectInfos/projectinfos.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <vector>
#include <iostream>
#include <algorithm>

SceneLayerInfos::SceneLayerInfos(SceneNodeInfos *nodeWidget, QWidget *parent)
    : QWidget(parent)
    , m_nodeWidget(nodeWidget)
    , m_layer(nullptr)
{
    m_objects = new QTreeWidget();
    m_objects->setHeaderHidden(true);
    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Objets :"));
    layout->addWidget(m_objects);

    setLayout(layout);
    updateTree();

    m_objects->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_objects, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClick(QPoint)));
    connect(m_objects, SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)), this, SLOT(onElementSelect(QTreeWidgetItem*)));

    if(m_nodeWidget != nullptr)
    {
        connect(m_nodeWidget, SIGNAL(requestRevert(SceneNode*)), this, SLOT(onRevertPrefab(SceneNode*)));
        connect(m_nodeWidget, SIGNAL(nameChanged(SceneNode*)), this, SLOT(onNameChanged(SceneNode*)));
    }
}

void SceneLayerInfos::setCurrentLayer(SceneLayer *layer)
{
    m_layer = layer;
    updateTree();
}

void SceneLayerInfos::updateTree()
{
    m_objects->clear();
    m_itemsinfos.clear();

    if(m_layer == nullptr)
    {
        auto item = new QTreeWidgetItem(m_objects);
        item->setDisabled(true);
        item->setText(0, "Pas de layer selectionné");
        return;
    }
    m_objects->setEnabled(true);

    std::vector<QTreeWidgetItem*> items(m_layer->size(), nullptr);

    bool needNewPass(true);
    constexpr unsigned int maxPass = 1000;
    unsigned int currentPass(0);
    while(needNewPass)
    {
        needNewPass = false;

        currentPass++;
        if(currentPass > maxPass)
        {
            std::cout << "Profondeur maximale atteinte !" << std::endl;
            break;
        }

        for(unsigned int i(0) ; i < m_layer->size() ; i++)
        {
            if(items[i] != nullptr)
                continue;

            const auto & obj = (*m_layer)[i];
            if(obj->parent == nullptr)
            {
                items[i] = new QTreeWidgetItem(m_objects);
                items[i]->setText(0, formatedName(obj.get()));
                m_itemsinfos.push_back({items[i], obj.get()});
                continue;
            }
            unsigned int parentIndex = m_layer->indexOf((*m_layer)[i]->parent);
            if(items[parentIndex] == nullptr)
            {
                needNewPass = true;
                continue;
            }
            items[i] = new QTreeWidgetItem(items[parentIndex]);
            items[i]->setText(0, formatedName(obj.get()));
            m_itemsinfos.push_back({items[i], obj.get()});
        }
    }
}

void SceneLayerInfos::onRightClick(QPoint point)
{
    if(m_layer == nullptr)
        return;

    QPoint globalPos(m_objects->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aAddHere(menu.addAction("Ajouter ici"));
    QAction *addRoot(menu.addAction("Ajouter racine"));

    auto item = m_objects->currentItem();
    if(item != nullptr)
        aDel = menu.addAction("Supprimer");

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
        removeElement(item);

    if(action == aAddHere)
        addElement(item);

    if(action == addRoot)
        addElement(nullptr);
}

void SceneLayerInfos::removeElement(QTreeWidgetItem * widget)
{

}

void SceneLayerInfos::addElement(QTreeWidgetItem * parent)
{
    if(m_layer == nullptr)
        return;

    bool ok = false;
    auto asset = AddNodeDialog::getNewAsset(this, &ok);
    if(!ok)
        return;

    auto item = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [parent](const auto it){return it.item == parent;});
    auto parentNode = item == m_itemsinfos.end() ? nullptr : item->node;

    if(!asset.isPrefab)
    {
        m_layer->emplace_back(std::make_unique<SceneNode>(asset.name, asset.assetName));
        if(parentNode != nullptr)
            m_layer->back()->parent = parentNode;
        updateTree();

        return;
    }

    auto prefabInfos = SceneData(ProjectInfos::instance().fullFileName(asset.assetName, AssetType::Scene)).asPrefab();
    if(prefabInfos.empty())
        return;

    std::cout << "S " <<  prefabInfos.size() << std::endl;

    prefabInfos.front()->parent = parentNode;
    prefabInfos.front()->prefabName = asset.assetName;
    prefabInfos.front()->name = asset.name;
    for(auto & node : prefabInfos)
        m_layer->emplace_back(std::move(node));
    updateTree();
}

void SceneLayerInfos::onElementSelect(QTreeWidgetItem *item)
{
    auto infos = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [item](const auto it){return it.item == item;});
    if(infos == m_itemsinfos.end())
        return;

    if(m_nodeWidget != nullptr)
        m_nodeWidget->setNode(infos->node);
}

void SceneLayerInfos::onRevertPrefab(SceneNode * parent)
{

}

void SceneLayerInfos::onNameChanged(SceneNode * node)
{
    auto it = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [node](const auto & it){return it.node == node;});
    if(it != m_itemsinfos.end())
        it->item->setText(0, formatedName(node));
}


QString SceneLayerInfos::formatedName(SceneNode * node) const
{
    QString name;
    if(node->name.isEmpty())
        name = "[noName]";
    else name = node->name;
    if(!node->prefabName.isEmpty())
        name = "[p]" + name;
    return name;
}
