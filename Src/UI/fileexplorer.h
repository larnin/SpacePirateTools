#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include "ProjectInfos/assettype.h"
#include "Events/Event.h"
#include "Events/Args/projectloadedevent.h"
#include <QWidget>
#include <QTreeWidget>
#include <QString>

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    FileExplorer(QWidget * parent = nullptr);
    FileExplorer(const FileExplorer &) = delete;
    FileExplorer(FileExplorer &&) = delete;
    virtual ~FileExplorer() = default;

    static QString getFullName(QTreeWidgetItem *item);
    static AssetType getType(QTreeWidgetItem *item);
    static bool isDirectory(QTreeWidgetItem *item);

public slots:
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);
    void onRightClick(QPoint point);

private:
    void updateTree();
    void onProjectLoaded(const ProjectLoadedEvent &);

    void rename(QTreeWidgetItem *item);
    void del(QTreeWidgetItem *item);
    void add(AssetType type);
    void import();

    QTreeWidget* m_tree;

    EventHolder<ProjectLoadedEvent> m_projectLoadedHolder;
};

#endif // FILEEXPLORER_H
