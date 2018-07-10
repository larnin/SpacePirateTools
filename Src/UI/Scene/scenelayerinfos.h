#ifndef SCENELAYERINFOS_H
#define SCENELAYERINFOS_H

#include "Scene/scenelayer.h"
#include <QWidget>
#include <QTreeWidget>

class SceneLayerInfos : public QWidget
{
    Q_OBJECT
public:
    SceneLayerInfos(QWidget * parent = nullptr);

    void setCurrentLayer(SceneLayer *layer);

private:
    void updateTree();

    SceneLayer * m_layer;
    QTreeWidget * m_objects;

};

#endif // SCENELAYERINFOS_H
