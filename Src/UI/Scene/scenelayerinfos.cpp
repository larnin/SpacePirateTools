#include "scenelayerinfos.h"
#include "addnodedialog.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <vector>
#include <iostream>

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
                items[i]->setText(0, obj->name);
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
            items[i]->setText(0, obj->name);
            m_itemsinfos.push_back({items[i], obj.get()});
        }
    }
}

void SceneLayerInfos::onRightClick(QPoint point)
{
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
    bool ok = false;
    AddNodeDialog::getNewAsset(this, &ok);
}
