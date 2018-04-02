#ifndef TILESETINFOS_H
#define TILESETINFOS_H

#include "Events/Args/saveevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include "Events/Event.h"
#include "Tileset/tilesetdata.h"
#include <QWidget>
#include <QComboBox>
#include <QSpinBox>
#include <QListWidget>

class CentralTilesetWindow;

class TilesetInfos : public QWidget
{
    friend class CentralTilesetWindow;
    Q_OBJECT
public:
    TilesetInfos(const QString &assetName, QWidget * parent = nullptr);
    ~TilesetInfos();

    inline TilesetData & getTilesetData() { return m_datas;}

public slots:
    void onBrushSelected(int index);
    void onRightClickBrush(QPoint point);
    void onTileSizeChanged();
    void onDeltaChanged();
    void onImageSelected(int index);

private:
    void setCentralTilesetWindow(CentralTilesetWindow * w);
    void initializeWidgets();

    void updateImageList();
    void updateBrushList();
    void updateValues();

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    CentralTilesetWindow * m_centralWindow;
    QString m_assetName;

    TilesetData m_datas;

    QSpinBox *m_tileSize;
    QComboBox *m_texture;
    QSpinBox *m_delta;
    QListWidget *m_listTile;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;

    int m_currentTile;
};

#endif // TILESETINFOS_H
