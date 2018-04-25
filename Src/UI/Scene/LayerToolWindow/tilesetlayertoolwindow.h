#ifndef TILESETLAYERTOOLWINDOW_H
#define TILESETLAYERTOOLWINDOW_H

#include "UI/Scene/centralscenewindow.h"
#include "UI/Scene/blockview.h"
#include "Scene/Layers/tilesetlayer.h"
#include "Tileset/tilesetdata.h"
#include <QWidget>
#include <QComboBox>
#include <QListWidget>
#include <QRadioButton>
#include <QCheckBox>
#include <memory>

class TilesetLayerToolWindow : public QWidget
{
    Q_OBJECT
public:
    TilesetLayerToolWindow(CentralSceneWindow * centralScene, TilesetLayer & layer, QWidget* parent = nullptr);

public slots:
    void onTextureIndexChanged(int index);
    void onBrushIndexChanged(int index);
    void onSelectBrush(int value);
    void onSelectTile(unsigned int id);
    void onColliderValueChanged();

private:
    void initializeWidgets();
    void createBrushList();
    void createTileColliderList();
    void updateImageList();
    void updateBrushList();

    void onRename(const RenamedFileEvent &);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    CentralSceneWindow* m_centralScene;
    TilesetLayer& m_layer;
    std::unique_ptr<TilesetData> m_tileset;

    QComboBox * m_texture;
    QComboBox * m_brushs;

    QListWidget * m_brushList;

    BlockView * m_blockView;
    QComboBox * m_colliderType;
    QRadioButton * m_rot0;
    QRadioButton * m_rot90;
    QRadioButton * m_rot180;
    QRadioButton * m_rot270;
    QCheckBox * m_xFlipped;
    QCheckBox * m_yFlipped;

    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;
};

#endif // TILESETLAYERTOOLWINDOW_H
