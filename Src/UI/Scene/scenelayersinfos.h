#ifndef SCENELAYERSINFOS_H
#define SCENELAYERSINFOS_H

#include "Scene/scenedata.h"
#include "Events/Args/saveevent.h"
#include "Events/Event.h"
#include "scenelayerinfos.h"
#include <QWidget>
#include <QListWidget>
#include <QPushButton>

class SceneLayersinfos : public QWidget
{
    Q_OBJECT
public:
    SceneLayersinfos(const QString &assetName, SceneLayerInfos * layerInfosWidget, QWidget * parent = nullptr);
    ~SceneLayersinfos();

    inline SceneData & getSceneData(){return m_datas;}

public slots:
    void onColorClicked();
    void onLayerIndexChange(int index);
    void onLayerRightClick(QPoint point);
    void updateGizmos(unsigned int index, bool value);
    void updateVisibility(unsigned int index, bool value);

private:
    void initializeWidgets();
    void onSave(const SaveEvent &);
    void updateColorButton();
    void updateLayerList();
    void addLayer();
   void delLayer(unsigned int index);
   void upLayer(unsigned int index);
   void downLayer(unsigned int index);
   void renameLayer(unsigned int index);

    SceneData m_datas;
    QString m_assetName;

    SceneLayerInfos* m_layerInfosWidget;

    EventHolder<SaveEvent> saveHolder;

    QPushButton *m_colorButton;
    QListWidget *m_layers;

    int m_currentIndex;
};

#endif // SCENELAYERSINFOS_H
