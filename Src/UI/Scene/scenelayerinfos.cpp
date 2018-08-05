#include "scenelayerinfos.h"
#include "addnodedialog.h"
#include "Scene/scenedata.h"
#include "ProjectInfos/projectinfos.h"
#include "Events/Event.h"
#include "Events/Args/addedfileevent.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QMenu>
#include <QMessageBox>
#include <QInputDialog>
#include <QFile>
#include <vector>
#include <algorithm>
#include <functional>
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
    QAction *aNewObject(nullptr);
    QAction *aNewPrefab(nullptr);
    QAction *aAddHere(menu.addAction("Ajouter ici"));
    QAction *addRoot(menu.addAction("Ajouter racine"));

    auto item = m_objects->currentItem();
    if(item != nullptr)
    {
        aDel = menu.addAction("Supprimer");
        aNewObject = menu.addAction("Vers nouvel objet");
        aNewPrefab = menu.addAction("Vers nouveau prefab");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
        removeElement(item);

    if(action == aAddHere)
        addElement(item);

    if(action == addRoot)
        addElement(nullptr);

    if(action == aNewObject)
        createObject(item);

    if(action == aNewPrefab)
        createPrefab(item);
}

void removeRecursive(SceneLayer & layer, SceneNode * node)
{
    for(auto item : node->childrens)
        removeRecursive(layer, item);

    if(node->parent != nullptr)
    {
        auto& pChilds = node->parent->childrens;
        pChilds.erase(std::remove_if(pChilds.begin(), pChilds.end(), [node](const auto & n){return n == node;}), pChilds.end());
    }

    auto index = layer.indexOf(node);
    if(index < layer.size())
        layer[index].reset();
}

void SceneLayerInfos::removeElement(QTreeWidgetItem * widget)
{
    auto item = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [widget](const auto it){return it.item == widget;});
    if(item ==  m_itemsinfos.end())
        return;

    removeRecursive(*m_layer, item->node);
    m_layer->erase(std::remove_if(m_layer->begin(), m_layer->end(), [](const auto & n){return !n;}), m_layer->end());

    updateTree();
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

    prefabInfos.front()->parent = parentNode;
    prefabInfos.front()->prefabName = asset.assetName;
    prefabInfos.front()->name = asset.name;
    for(auto & node : prefabInfos)
        m_layer->emplace_back(std::move(node));
    updateTree();
}

void SceneLayerInfos::createObject(QTreeWidgetItem * widget)
{
    auto infos = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [widget](const auto it){return it.item == widget;});
    if(infos == m_itemsinfos.end())
        return;

    bool ok;
    QString name = QInputDialog::getText(this, "Nouvel objet", "Indiquez le nom du nouvel objet", QLineEdit::Normal, infos->node->objectName, &ok);
    if(name.isEmpty())
        return;

    QString extension = assetTypeExtension(AssetType::Object);
    if(!name.endsWith(extension))
    {
        if(!name.endsWith('.'))
            name += '.';
        name += extension;
    }

    auto fullName = ProjectInfos::instance().fullFileName(name, AssetType::Object);
    if(QFile::exists(fullName))
    {
        auto answer = QMessageBox::question(this, "Ecraser " + name, "L'objet " + name + " existe déja.\nVoulez vous l'écraser ?");
        if(answer != QMessageBox::Yes)
            return;
    }
    else
    {
        QFile file(fullName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, "Erreur creation", "Impossible de créer la ressource demandée");
            return;
        }
    }

    infos->node->objectName = name;
    infos->node->object.save(fullName);

    if(m_nodeWidget != nullptr)
        m_nodeWidget->updateFields();

    Event<AddedFileEvent>::send({fullName});
}

void cloneIterative(SceneLayer & layer, SceneNode * node, SceneNode * parent)
{
    layer.push_back(node->clone());
    SceneNode * pn = layer.back().get();
    pn->parent = parent;
    if(parent != nullptr)
        parent->childrens.push_back(pn);
    for(const auto & n : node->childrens)
        cloneIterative(layer, n, pn);
}

void SceneLayerInfos::createPrefab(QTreeWidgetItem * widget)
{
    auto infos = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [widget](const auto it){return it.item == widget;});
    if(infos == m_itemsinfos.end())
        return;

    bool ok;
    QString name = QInputDialog::getText(this, "Nouveau prefab", "Indiquez le nom du nouveau prefab", QLineEdit::Normal, infos->node->prefabName, &ok);
    if(name.isEmpty())
        return;

    QString extension = assetTypeExtension(AssetType::Scene);
    if(!name.endsWith(extension))
    {
        if(!name.endsWith('.'))
            name += '.';
        name += extension;
    }

    auto fullName = ProjectInfos::instance().fullFileName(name, AssetType::Scene);
    if(QFile::exists(fullName))
    {
        auto answer = QMessageBox::question(this, "Ecraser " + name, "Le prefab " + name + " existe déja.\nVoulez vous l'écraser ?");
        if(answer != QMessageBox::Yes)
            return;
    }
    else
    {
        QFile file(fullName);
        if(!file.open(QIODevice::WriteOnly))
        {
            QMessageBox::critical(this, "Erreur creation", "Impossible de créer la ressource demandée");
            return;
        }
    }

    SceneData prefab;
    prefab.push_back(std::make_unique<SceneLayer>("Prefab"));
    auto & prefabLayer = *(prefab.front().get());
    infos->node->prefabName = "";
    cloneIterative(prefabLayer, infos->node, nullptr);
    infos->node->prefabName = name;

    prefab.save(fullName);

    if(m_nodeWidget != nullptr)
        m_nodeWidget->updateFields();

    Event<AddedFileEvent>::send({fullName});
}

void SceneLayerInfos::onElementSelect(QTreeWidgetItem *item)
{
    auto infos = std::find_if(m_itemsinfos.begin(), m_itemsinfos.end(), [item](const auto it){return it.item == item;});
    if(infos == m_itemsinfos.end())
        return;

    if(m_nodeWidget != nullptr)
        m_nodeWidget->setNode(infos->node);

    emit currentNodeChanged(std::distance(m_itemsinfos.begin(), infos));
}

void SceneLayerInfos::onCurrentNodeChanged(int index)
{
    if(index < 0 || index > static_cast<int>(m_itemsinfos.size()))
    {
        m_objects->setCurrentItem(nullptr);
        return;
    }

    m_objects->setCurrentItem(m_itemsinfos[index].item);
}

void SceneLayerInfos::onRevertPrefab(SceneNode * parent)
{
    auto answer = QMessageBox::question(this, "Reinitialiser " + parent->name + " ?", "Etes vous sur de vouloir réinitialiser " + parent->name + " vers " + parent->prefabName + " ?\n" + "Toute sa hierarchie enfant sera perdue.");
    if(answer != QMessageBox::Yes)
        return;

    auto prefabInfos = SceneData(ProjectInfos::instance().fullFileName(parent->prefabName, AssetType::Scene)).asPrefab();
    if(prefabInfos.empty())
    {
        parent->prefabName = "";
        if(m_nodeWidget != nullptr)
            m_nodeWidget->setNode(parent);
        updateTree();
        return;
    }

    for(auto n : parent->childrens)
        removeRecursive(*m_layer, n);

    m_layer->erase(std::remove_if(m_layer->begin(), m_layer->end(), [](const auto & node){return !node;}), m_layer->end());

    parent->revertObject(*(prefabInfos[0]));
    parent->childrens.clear();

    for(unsigned int i(1) ; i < prefabInfos.size() ; i++)
    {
        auto & n(prefabInfos[i]);
        if(n->parent == prefabInfos[0].get())
        {
            n->parent = parent;
            parent->childrens.push_back(n.get());
        }
        m_layer->push_back(std::move(n));
    }

    if(m_nodeWidget != nullptr)
        m_nodeWidget->setNode(parent);
    updateTree();
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
