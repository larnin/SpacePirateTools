#ifndef SCENELAYERINFOS_H
#define SCENELAYERINFOS_H

#include "Scene/scenelayer.h"
#include "scenenodeinfos.h"
#include <QWidget>
#include <QTreeWidget>

class SceneLayerInfos : public QWidget
{
    Q_OBJECT
public:
    SceneLayerInfos(SceneNodeInfos * nodeWidget, QWidget * parent = nullptr);

    void setCurrentLayer(SceneLayer *layer);

private:
    void updateTree();

    SceneNodeInfos m_nodeWidget;

    SceneLayer * m_layer;
    QTreeWidget * m_objects;

};

#endif // SCENELAYERINFOS_H
