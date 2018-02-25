#ifndef FILEEXPLORER_H
#define FILEEXPLORER_H

#include <QWidget>
#include <QTreeWidget>
#include <QString>

class FileExplorer : public QWidget
{
    Q_OBJECT

public:
    FileExplorer(QWidget * parent = nullptr);
    virtual ~FileExplorer() = default;

signals:
    void openRessource(QString /*ressourceDirName*/);

public slots:
    void onItemDoubleClicked(QTreeWidgetItem *item, int column);

private:
    void updateTree();

    QTreeWidget* m_tree;
};

#endif // FILEEXPLORER_H
