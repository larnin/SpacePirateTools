#ifndef TILEMAPINFOS_H
#define TILEMAPINFOS_H

#include "Tilemap/tilemapdata.h"
#include "Tileset/tilesetdata.h"
#include "blockview.h"
#include "Events/Event.h"
#include "Events/Args/addedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/saveevent.h"
#include <QComboBox>
#include <QRadioButton>
#include <QWidget>
#include <QCheckBox>
#include <QListWidget>
#include <QSpinBox>

class CentralTilemapWidget;

class TilemapInfos : public QWidget
{
    Q_OBJECT
public:
    TilemapInfos(const QString & filename, QWidget* parent = nullptr);
    ~TilemapInfos();

    void setCentralWidget(CentralTilemapWidget * widget);
    inline TilemapData & getData() {return m_data;}

public slots:
    void onTextureIndexChanged(int index);
    void onBrushIndexChanged(int index);
    void onSelectBrush(int value);
    void onSelectTile(unsigned int);
    void onColliderValueChanged();
    void onTileValidSelection();
    void onLayerChange(int index);

    void onSizeChanged();
    void onTileSizeChanged();

private:
    void initializeWidgets();
    void createBrushList();
    void createTileColliderList();
    void updateImageList();
    void updateBrushList();
    void updateLayerList();

    void onRename(const RenamedFileEvent &);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);
    void onSave(const SaveEvent &);

    void loadTexture();

    CentralTilemapWidget * m_centralWidget;

    QString m_filename;
    TilemapData m_data;
    std::unique_ptr<TilesetData> m_tileset;
    Texture m_tilesTexture;

    QSpinBox * m_sizeX;
    QSpinBox * m_sizeY;

    QComboBox * m_texture;
    QSpinBox * m_tileSize;
    QSpinBox * m_tileDelta;
    QComboBox * m_brushs;

    QListWidget * m_brushList;

    BlockView * m_blockView;
    QComboBox * m_colliderType;
    QComboBox * m_colliderLayer;
    QRadioButton * m_rot0;
    QRadioButton * m_rot90;
    QRadioButton * m_rot180;
    QRadioButton * m_rot270;
    QCheckBox * m_xFlipped;
    QCheckBox * m_yFlipped;
    QCheckBox * m_autoSelect;

    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;
    EventHolder<SaveEvent> saveHolder;
};

#endif // TILEMAPINFOS_H
