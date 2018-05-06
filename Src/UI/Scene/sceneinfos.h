#ifndef SCENEINFOS_H
#define SCENEINFOS_H

#include "Scene/scenedata.h"
#include "layertoolholder.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include "Events/Args/editionevents.h"
#include <QString>
#include <QWidget>
#include <QListWidget>
#include <QSpinBox>
#include <QPushButton>
#include <QCheckBox>

class CentralSceneWindow;

class SceneInfos : public QWidget
{
    friend class CentralSceneWindow;

    Q_OBJECT
public:
    SceneInfos(const QString &assetName, QWidget * parent = nullptr);
    ~SceneInfos();

    inline SceneData & getDatas(){ return m_datas;}
    inline void setLayerHolder(LayerToolHolder * layerTool) { m_layerToolHolder = layerTool;}

public slots:
    void onColorCLicked();
    void onSizeChange();
    void onLayerIndexChange(int index);
    void onLayerRightClick(QPoint point);
    void updateGizmos(unsigned int index, bool value);
    void updateVisibility(unsigned int index, bool value);

    inline bool showGrid() const {return m_showGrid->isChecked();}

private:
    inline void setCentralSceneWindow(CentralSceneWindow * scene) { m_sceneWindow = scene;}
    void initializeWidgets();
    void addLayer();
    void delLayer(unsigned int index);
    void upLayer(unsigned int index);
    void downLayer(unsigned int index);
    void renameLayer(unsigned int index);

    void updateLayerList();
    void updateColorButton();

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);
    void onSelectModeSwitch(const SelectModeSwitchEvent & e);

    SceneData m_datas;
    QString m_assetName;

    int m_currentIndex;

    QPushButton* m_colorButton;
    QSpinBox* m_sizeX;
    QSpinBox* m_sizeY;
    QListWidget* m_layers;
    QCheckBox* m_showGrid;

    LayerToolHolder * m_layerToolHolder;

    EventHolder<SaveEvent> m_saveHolder;
    EventHolder<RenamedFileEvent> m_renameHolder;
    EventHolder<SelectModeSwitchEvent> m_selectModeSwitchHolder;

    CentralSceneWindow * m_sceneWindow;
};

#endif // SCENEINFOS_H
