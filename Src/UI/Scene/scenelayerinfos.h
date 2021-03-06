#ifndef SCENELAYERINFOS_H
#define SCENELAYERINFOS_H

#include "Scene/scenelayer.h"
#include "scenenodeinfos.h"
#include <QWidget>
#include <QTreeWidget>
#include <vector>

class SceneLayerInfos : public QWidget
{
    struct ItemInfos
    {
        QTreeWidgetItem * item;
        SceneNode * node;
    };

    Q_OBJECT
public:
    SceneLayerInfos(SceneNodeInfos * nodeWidget, QWidget * parent = nullptr);

    void setCurrentLayer(SceneLayer *layer);

public slots:
    void onRightClick(QPoint point);
    void onElementSelect(QTreeWidgetItem * item);
    void onRevertPrefab(SceneNode * parent);
    void onNameChanged(SceneNode * node);
    void onCurrentNodeChanged(int index);

signals:
    void currentNodeChanged(int index);

private:
    void updateTree();
    void removeElement(QTreeWidgetItem *widget);
    void addElement(QTreeWidgetItem * parent);
    void createObject(QTreeWidgetItem * widget);
    void createPrefab(QTreeWidgetItem * widget);
    QString formatedName(SceneNode * node) const;

    SceneNodeInfos* m_nodeWidget;

    SceneLayer * m_layer;
    QTreeWidget * m_objects;
    std::vector<ItemInfos> m_itemsinfos;

};

#endif // SCENELAYERINFOS_H
