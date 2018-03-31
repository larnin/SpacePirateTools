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

class TilesetInfos : public QWidget
{
    Q_OBJECT
public:
    TilesetInfos(const QString &assetName, QWidget * parent = nullptr);
    ~TilesetInfos();

    inline TilesetData & getTilesetData() { return m_tileset;}

private:
    void initializeWidgets();

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    QString m_assetName;

    TilesetData m_tileset;

    QSpinBox *m_tileSize;
    QComboBox *m_texture;
    QSpinBox *m_delta;
    QListWidget *m_listTile;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;
};

#endif // TILESETINFOS_H
