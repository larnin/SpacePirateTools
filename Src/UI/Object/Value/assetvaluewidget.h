#ifndef ASSETVALUEWIDGET_H
#define ASSETVALUEWIDGET_H

#include "Object/Value/objectvalueasset.h"
#include "Events/Event.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include <QWidget>
#include <QComboBox>

class AssetValueWidget : public QWidget
{
    Q_OBJECT
public:
    AssetValueWidget(ObjectValueAsset & asset, QWidget * parent = nullptr);

public slots:
    void onValueChanged(int index);

private:
    void updateCombobox();

    void onRename(const RenamedFileEvent &);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    ObjectValueAsset & m_asset;

    QComboBox * m_value;

    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;
};

#endif // ASSETVALUEWIDGET_H
