#include "scenelayerinfos.h"
#include <QLabel>
#include <QVBoxLayout>
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
}

void SceneLayerInfos::setCurrentLayer(SceneLayer *layer)
{
    m_layer = layer;
    updateTree();
}

void SceneLayerInfos::updateTree()
{
    m_objects->clear();

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
        }
    }
}
