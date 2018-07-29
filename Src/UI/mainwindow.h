#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "Events/Event.h"
#include "Events/Args/openressourceevent.h"
#include "Events/Args/closeressourceevent.h"
#include <QDockWidget>
#include <QMainWindow>
#include <vector>

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
    void onPaste();

    void onShowExplorer();
    void onShowAssetDocks();
    void onShowCollidersLayer();

private:
    void createMenus();
    void createDocks();
    void openProject(const QString & dir);

    void closeCurrentWidget();
    void openAnimation(const QString & filename);
    void openAnimator(const QString & filename);
    void openImage(const QString & filename);
    void openTileset(const QString & filename);
    void openScene(const QString & filename);
    void openObject(const QString & filename);
    void openTilemap(const QString & filename);

    void onOpenRessource(const QString & ressourceDirName, AssetType assetType);
    void onCloseRessource(const QString & ressourceDirName);
    void clearDocks();


    QDockWidget* m_explorerDock;
    std::vector<QDockWidget*> m_assetDocks;

    EventHolder<OpenRessourceEvent> m_openRessourceHolder;
    EventHolder<CloseRessourceEvent> m_closeRessourceHolder;


    QString m_currentRessource;
};

#endif // MAINWINDOW_H
