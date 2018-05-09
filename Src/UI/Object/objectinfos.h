#ifndef OBJECTINFOS_H
#define OBJECTINFOS_H

#include "Object/objectdata.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Event.h"
#include <QWidget>
#include <QVBoxLayout>
#include <vector>

class ObjectInfos : public QWidget
{
    Q_OBJECT
public:
    ObjectInfos(const QString &assetName, QWidget * parent = nullptr);
    ~ObjectInfos();

public slots:
    void onAddClicked();

private:
    void initializeWidgets();

    void addPropertyWidget(ObjectProperty & p);
    void removePropertyWidget(unsigned int index);

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);

    QString m_assetName;
    ObjectData m_datas;

    std::vector<QWidget*> m_widgets;
    QVBoxLayout* m_propertiesLayout;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;
};

#endif // OBJECTINFOS_H
