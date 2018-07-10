#include "mainwindow.h"
#include "ProjectInfos/configs.h"
#include "ProjectInfos/projectinfos.h"
#include "Events/Event.h"
#include "Events/Args/projectloadedevent.h"
#include "Events/Args/clearevent.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/editionevents.h"
#include "dock.h"
#include "fileexplorer.h"
#include "UI/Animation/animationsinfos.h"
#include "UI/Animation/centralanimationwidget.h"
#include "UI/Animator/animatorinfos.h"
#include "UI/Animator/centralanimatorwidget.h"
#include "UI/Tileset/tilesetinfos.h"
#include "UI/Tileset/centraltilesetwindow.h"
#include "UI/Object/objectinfos.h"
#include "UI/imagewidget.h"
#include "UI/colliderlayerdialog.h"
#include "UI/Tilemap/centraltilemapwidget.h"
#include "UI/Tilemap/tilemapinfos.h"
#include "UI/Scene/scenelayersinfos.h"
#include "UI/Scene/scenelayerinfos.h"
#include <QMenuBar>
#include <QAction>
#include <QFileDialog>
#include <QMessageBox>
#include <QDir>

const QString defaultName = "Best editor ever";

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_openRessourceHolder(Event<OpenRessourceEvent>::connect([this](const auto & e){onOpenRessource(e);}))
{
    createMenus();
    createDocks();

    closeCurrentWidget();

    resize(800, 600);
}

void MainWindow::createMenus()
{
    QMenu *fileMenu = menuBar()->addMenu("&Fichier");
        auto newAction = fileMenu->addAction("&Nouveau projet");
        newAction->setShortcut(QKeySequence("Ctrl+N"));
        auto loadAction = fileMenu->addAction("&Ouvrir un projet");
        loadAction->setShortcut(QKeySequence("Ctrl+O"));
        addRecentFile(fileMenu);
        fileMenu->addSeparator();
        auto saveAction = fileMenu->addAction("&Sauvegarder");
        saveAction->setShortcut(QKeySequence("Ctrl+S"));
        auto saveAndQuitAction = fileMenu->addAction("Sauvegarder et &Quitter");

    QMenu *editMenu = menuBar()->addMenu("&Edition");
        auto undoAction = editMenu->addAction("&Annuler");
        undoAction->setShortcut(QKeySequence("Ctrl+Z"));
        auto redoAction = editMenu->addAction("&Refaire");
        redoAction->setShortcut(QKeySequence("Ctrl+Y"));
        editMenu->addSeparator();
        auto copyAction = editMenu->addAction("&Copier");
        copyAction->setShortcut(QKeySequence("Ctrl+C"));
        auto cutAction = editMenu->addAction("Couper");
        cutAction->setShortcut(QKeySequence("Ctrl+X"));
        auto pastAction = editMenu->addAction("Coller");
        pastAction->setShortcut(QKeySequence("Ctrl+V"));
        editMenu->addSeparator();

    QMenu *windowMenu = menuBar()->addMenu("&Fenetre");
        auto showExplorer = windowMenu->addAction("Afficher l'explorer");
        auto showAssetDocks = windowMenu->addAction("Reafficher les docks");
        auto showCollidersLayer = windowMenu->addAction("Afficher le menu des colliders");

    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(onNew()));
    connect(loadAction, SIGNAL(triggered(bool)), this, SLOT(onLoad()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(onSave()));
    connect(saveAndQuitAction, SIGNAL(triggered(bool)), this, SLOT(onSaveAndQuit()));

    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(onUndo()));
    connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(onRedo()));
    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(onCopy()));
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(onCut()));
    connect(pastAction, SIGNAL(triggered(bool)), this, SLOT(onPaste()));

    connect(showExplorer, SIGNAL(triggered(bool)), this, SLOT(onShowExplorer()));
    connect(showAssetDocks, SIGNAL(triggered(bool)), this, SLOT(onShowAssetDocks()));
    connect(showCollidersLayer, SIGNAL(triggered(bool)), this, SLOT(onShowCollidersLayer()));
}

void MainWindow::createDocks()
{
    m_explorerDock = new Dock<FileExplorer>("Explorer", false);
    addDockWidget(Qt::LeftDockWidgetArea, m_explorerDock);
}

void MainWindow::addRecentFile(QMenu* menu)
{
    const auto & recent = Configs::instance().lastProjects();
    if(recent.empty())
        return;

    auto recentMenu = menu->addMenu("Projet recent");
    for(const auto & item : recent)
    {
        auto action = recentMenu->addAction(item);
        connect(action, &QAction::triggered, [this, item](){onRecent(item);});
    }
}

void MainWindow::onNew()
{
    auto dir = QFileDialog::getExistingDirectory(this, "Nouveau projet");
    if(dir.isEmpty())
        return;

    if(!QDir(dir).isEmpty())
    {
        auto button = QMessageBox::question(this, "Dossier non vide", "Ce dossier n'est pas vide, etes vous sur de vouloir créer un projet ici ?");

        if(button != QMessageBox::Yes)
            return;
    }

    openProject(dir);
}

void MainWindow::onLoad()
{
    auto dir = QFileDialog::getExistingDirectory(this, "Nouveau projet");
    if(dir.isEmpty())
        return;

    openProject(dir);
}

void MainWindow::onRecent(const QString & dir)
{
    openProject(dir);
}

void MainWindow::onSave()
{
    Event<SaveEvent>::send({});
}

void MainWindow::onSaveAndQuit()
{
    onSave();

    close();
}

void MainWindow::onUndo()
{
    Event<UndoEvent>::send({});
}

void MainWindow::onRedo()
{
    Event<RedoEvent>::send({});
}

void MainWindow::onCopy()
{
    Event<CopyEvent>::send({});
}

void MainWindow::onCut()
{
    Event<CutEvent>::send({});
}

void MainWindow::onPaste()
{
    Event<PasteEvent>::send({});
}

void MainWindow::onShowExplorer()
{
    if(!m_explorerDock->isHidden())
        m_explorerDock->setFocus();
    m_explorerDock->show();
}

void MainWindow::onShowAssetDocks()
{
    for(auto d : m_assetDocks)
        if(d->isHidden())
            d->show();
}


void MainWindow::onShowCollidersLayer()
{
    ColliderLayerDialog::getNewLayerID(false, this);
}

void MainWindow::openProject(const QString & dir)
{
    onSave();

    Event<ClearEvent>::send({});

    ProjectInfos::instance().loadProject(dir);
    if(ProjectInfos::instance().projectLoaded())
        Event<ProjectLoadedEvent>::send({});
}


void MainWindow::onOpenRessource(const OpenRessourceEvent & e)
{
    clearDocks();

    setWindowTitle(e.ressourceDirName);

    auto fullName = ProjectInfos::instance().projectDirectory() + "/" + e.ressourceDirName;

    switch(e.assetType)
    {
    case AssetType::Animation:
        openAnimation(fullName);
        break;
    case AssetType::Animator:
        openAnimator(fullName);
        break;
    case AssetType::Scene:
        openScene(fullName);
        break;
    case AssetType::Tileset:
        openTileset(fullName);
        break;
    case AssetType::Image:
        openImage(fullName);
        break;
    case AssetType::Object:
        openObject(fullName);
        break;
    case AssetType::Tilemap:
        openTilemap(fullName);
        break;
    default:
        closeCurrentWidget();
        break;
    }
}

void MainWindow::closeCurrentWidget()
{
    clearDocks();

    QWidget * w = new QWidget();
    w->setStyleSheet("background-color:black;");

    setCentralWidget(w);

    setWindowTitle(defaultName);
}

void MainWindow::openAnimation(const QString & filename)
{
    AnimationsInfos *a = new AnimationsInfos(filename);
    CentralAnimationWidget *animWidget = new CentralAnimationWidget(a);
    setCentralWidget(animWidget);
    m_assetDocks.push_back(new Dock<AnimationsInfos>(a, "Animation", false));
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.back());
}

void MainWindow::openAnimator(const QString & filename)
{
    AnimatorInfos *a = new AnimatorInfos(filename);
    CentralAnimatorWidget *animWidget = new CentralAnimatorWidget(a);
    setCentralWidget(animWidget);
    m_assetDocks.push_back(new Dock<AnimatorInfos>(a, "Animator", false));
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.back());
}

void MainWindow::openImage(const QString & filename)
{
    setCentralWidget(new ImageWidget(filename));
}

void MainWindow::openTileset(const QString & filename)
{
    TilesetInfos *a = new TilesetInfos(filename);
    CentralTilesetWindow *tilesetWidget = new CentralTilesetWindow(a);
    setCentralWidget(tilesetWidget);
    m_assetDocks.push_back(new Dock<TilesetInfos>(a, "Tileset", false));
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.back());
}

void MainWindow::openScene(const QString & filename)
{
    SceneLayersinfos *a = new SceneLayersinfos(filename);
    SceneLayerInfos * layer = new SceneLayerInfos();
    m_assetDocks.push_back(new Dock<SceneLayersinfos>(a, "Layers", false));
    addDockWidget(Qt::LeftDockWidgetArea, m_assetDocks.back());
    m_assetDocks.push_back(new Dock<SceneLayerInfos>(layer, "Layer", false));
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.back());
}

void MainWindow::openObject(const QString & filename)
{
    setCentralWidget(new ObjectInfos(filename));
}

void MainWindow::openTilemap(const QString & filename)
{
    TilemapInfos *a = new TilemapInfos(filename);
    CentralTilemapWidget *tilemap = new CentralTilemapWidget(a);
    setCentralWidget(tilemap);
    m_assetDocks.push_back(new Dock<TilemapInfos>(a, "Tilemap", false));
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.back());
}

void MainWindow::clearDocks()
{
    for(auto d : m_assetDocks)
    {
        d->setAttribute(Qt::WA_DeleteOnClose, true);
        d->close();
    }
    m_assetDocks.clear();
}

