#ifndef SCENEINFOS_H
#define SCENEINFOS_H

#include "Scene/scenedata.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include <QString>
#include <QWidget>
#include <QListWidget>
#include <QSpinBox>

class SceneInfos : public QWidget
{
    Q_OBJECT
public:
    SceneInfos(const QString &assetName, QWidget * parent = nullptr);
    ~SceneInfos();

    inline SceneData & getDatas(){ return m_datas;}

public slots:
    void onSizeChange();
    void onLayerIndexChange(int index);
    void onLayerRightClick(QPoint point);

private:
    void initializeWidgets();
    void addLayer();
    void delLayer(unsigned int index);
    void upLayer(unsigned int index);
    void downLayer(unsigned int index);
    void renameLayer(unsigned int index);

    void updateLayerList();

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);

    SceneData m_datas;
    QString m_assetName;

    int m_currentIndex;

    QSpinBox* m_sizeX;
    QSpinBox* m_sizeY;
    QListWidget* m_layers;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;

};

#endif // SCENEINFOS_H
