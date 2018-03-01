#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDockWidget>
#include <QMainWindow>
#include <vector>
#include "Events/Event.h"
#include "Events/Args/openressourceevent.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void addRecentFile(QMenu* menu);

    void onNew();
    void onLoad();
    void onRecent(const QString & dir);
    void onSave();
    void onSaveAndQuit();

    void onUndo();
    void onRedo();
    void onCopy();
    void onCut();
    void onPast();
    void onSelectMode(bool mode);

    void onShowExplorer();
    void onShowAssetDocks();

private:
    void createMenus();
    void createDocks();
    void openProject(const QString & dir);

    void closeCurrentWidget();
    void openAnimation(const QString & filename);

    void onOpenRessource(const OpenRessourceEvent & e);
    void clearDocks();


    QDockWidget* m_explorerDock;
    std::vector<QDockWidget*> m_assetDocks;

    EventHolder<OpenRessourceEvent> m_openRessourceHolder;
};

#endif // MAINWINDOW_H
