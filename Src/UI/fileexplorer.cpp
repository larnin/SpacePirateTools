#include "fileexplorer.h"
#include "ProjectInfos/assettype.h"
#include "ProjectInfos/projectinfos.h"
#include "Events/Args/openressourceevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include <QVBoxLayout>
#include <QMessageBox>
#include <QInputDialog>
#include <QFileDialog>
#include <QMenu>
#include <QFile>

#include <QDebug>
FileExplorer::FileExplorer(QWidget *parent)
    : QWidget(parent)
    , m_projectLoadedHolder(Event<ProjectLoadedEvent>::connect([this](auto v){onProjectLoaded(v);}))
{
    m_tree = new QTreeWidget();
    m_tree->setHeaderHidden(true);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(m_tree);

    setLayout(layout);


    m_tree->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_tree, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClick(QPoint)));

    connect(m_tree, SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)), this, SLOT(onItemDoubleClicked(QTreeWidgetItem*,int)));

    updateTree();
}

void FileExplorer::updateTree()
{
    m_tree->clear();

    if(!ProjectInfos::instance().projectLoaded())
    {
        auto item = new QTreeWidgetItem(m_tree);
        item->setText(0, "No project loaded");
        item->setDisabled(true);
        return;
    }

    for(unsigned int i(0) ; i <= static_cast<unsigned int>(AssetType::Max) ; i++)
    {
        AssetType type(static_cast<AssetType>(i));
        QTreeWidgetItem * dirItem = new QTreeWidgetItem(m_tree);
        dirItem->setText(0, assetTypeToString(type));
        auto extension = assetTypeExtension(type);
        for(auto asset : ProjectInfos::instance().fileInfos(type))
        {
            auto item = new QTreeWidgetItem(dirItem);
            item->setText(0, asset.remove(asset.size() - extension.size() - 1, extension.size() + 1));
        }
        m_tree->addTopLevelItem(dirItem);
    }
}

void FileExplorer::onItemDoubleClicked(QTreeWidgetItem *item, int column)
{
    if(column != 0)
        return;

    auto parent = item->parent();
    if(parent == nullptr)
        return;
    auto dir = parent->text(0);
    auto type = stringToAssetType(dir);
    if(type == AssetType::Unknow)
        return;
    Event<OpenRessourceEvent>::send({type, dir + "/" + item->text(0) + "." + assetTypeExtension(type)});
}

void FileExplorer::onProjectLoaded(const ProjectLoadedEvent &)
{
    updateTree();
}

void FileExplorer::onRightClick(QPoint point)
{
    if(!ProjectInfos::instance().projectLoaded())
        return;

    auto current = m_tree->currentItem();

    QPoint globalPos(m_tree->viewport()->mapToGlobal(point));
    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aRename(nullptr);
    QMenu *aAdd(menu.addMenu("Ajouter"));
    std::vector<QAction*> aAdds;
    for(unsigned int i(0) ; i <= static_cast<unsigned int>(AssetType::Max) ; i++)
    {
        auto assetType = static_cast<AssetType>(i);
        if(!assetCanBeCreated(assetType))
            continue;
        aAdds.push_back(aAdd->addAction(assetTypeToString(assetType)));
    }
    QAction *aImport(menu.addAction("Importer"));
    if(current->parent() != nullptr)
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renomer");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
        del(current);

    if(action == aImport)
        import();

    if(action == aRename)
        rename(current);

    for(const auto & a : aAdds)
    {
        if(action != a)
            continue;

        add(stringToAssetType(action->text()));
    }
}

#include <QDebug>

void FileExplorer::rename(QTreeWidgetItem *item)
{
    auto oldName = getFullName(item);
    bool ok = false;
    auto text = QInputDialog::getText(this, "Renomer " + item->text(0), "Donnez un nouveau nom pour l'asset " + item->text(0), QLineEdit::Normal, "", &ok);
    if(!ok || text.isEmpty())
        return;

    auto oldShortName = item->text(0);
    item->setText(0, text);
    auto newName = getFullName(item);
    auto projectDir = ProjectInfos::instance().projectDirectory() + "/";

    auto done = QFile::rename(projectDir + oldName, projectDir + newName);
    if(!done)
    {
        QMessageBox::critical(this, "Erreur lors du renommage", QString("Impossible de renommer ce fichier.\n") +
                              "Etes vous sur que le fichier " + text + " n'existe pas ?");
        item->setText(0, oldShortName);
        return;
    }

    ProjectInfos::instance().reloadFileList();
    updateTree();

    Event<RenamedFileEvent>::send(RenamedFileEvent{oldName, newName});
}

void FileExplorer::del(QTreeWidgetItem *item)
{
    auto fullName = getFullName(item);
    auto value = QMessageBox::question(this, "Supprimer " + item->text(0), "Etes vous sur de vouloir supprimer " + item->text(0) + " ?");

    if(value != QMessageBox::Yes)
        return;

    QFile::remove(ProjectInfos::instance().projectDirectory() + "/" + fullName);

    ProjectInfos::instance().reloadFileList();
    updateTree();

    Event<RemovedFileEvent>::send({fullName});
}
void FileExplorer::add(AssetType type)
{
    if(!assetCanBeCreated(type))
        return;

    bool ok = false;
    auto text = QInputDialog::getText(this, "Créer " + assetTypeToString(type), "Donner un nom a la nouvelle ressource", QLineEdit::Normal, "", &ok);
    if(!ok || text.isEmpty())
        return;

    auto fullName = assetTypeToString(type) + "/" + text + "." + assetTypeExtension(type);
    auto dir = ProjectInfos::instance().projectDirectory() + "/";

    if(QFile::exists(dir + fullName))
    {
        QMessageBox::information(this, "La ressource existe", "La ressource " + fullName + " existe déja");
        return;
    }

    QFile file(dir + fullName);
    if(!file.open(QIODevice::WriteOnly))
    {
        QMessageBox::critical(this, "Erreur creation", "Impossible de créer la ressource demandée");
        return;
    }
    file.close();

    ProjectInfos::instance().reloadFileList();
    updateTree();

    Event<OpenRessourceEvent>::send({type, fullName});
}

void FileExplorer::import()
{
    auto file = QFileDialog::getOpenFileName(this, "Importer une ressource");
    if(file.isEmpty())
        return;

    QFileInfo fileInfo(file);
    auto name = fileInfo.completeBaseName();
    auto extension = fileInfo.suffix();

    auto assetType = extensionToAssetType(extension);
    if(assetType == AssetType::Unknow)
    {
        QMessageBox::information(this, "Erreur importer", "Type de ressource non supportée");
        return;
    }

    auto dir = ProjectInfos::instance().projectDirectory() + "/";
    auto assetfullName = assetTypeToString(assetType) + "/" + name + "." + extension;
    auto fullName = dir + assetfullName;

    if(QFile::exists(fullName))
    {
        auto value = QMessageBox::question(this, "Ecraser", "Le ficher " + name + "." + extension + " existe déja.\nL'écraser ?");
        if(value != QMessageBox::Yes)
            return;

        QFile::remove(fullName);
    }

    if(!QFile::copy(file, fullName))
    {
        QMessageBox::critical(this, "Erreur importer", "une erreur est survenue lors de l'importation de la ressource.");
        return;
    }

    ProjectInfos::instance().reloadFileList();
    updateTree();

    Event<OpenRessourceEvent>::send({assetType, assetfullName});
}

QString FileExplorer::getFullName(QTreeWidgetItem *item)
{
    bool isFolder = isDirectory(item);

    auto extension = assetTypeExtension(getType(item));
    QString name;

    while(item != nullptr)
    {
        name = item->text(0) + "/" + name;
        item = item->parent();
    }

    if(isFolder)
        return name;
    name = name.remove(name.size() - 1, 1);
    return name + "." + extension;
}

AssetType FileExplorer::getType(QTreeWidgetItem *item)
{
    if(item->parent() != nullptr)
        return getType(item->parent());

    return stringToAssetType(item->text(0));
}

bool FileExplorer::isDirectory(QTreeWidgetItem *item)
{
    return item->childCount() > 0;
}
