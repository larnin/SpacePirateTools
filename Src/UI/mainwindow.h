#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

public slots:
    void createMenus();
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

private:
    void openProject(const QString & dir);
};

#endif // MAINWINDOW_H
