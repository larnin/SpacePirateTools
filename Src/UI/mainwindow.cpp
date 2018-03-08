#include "mainwindow.h"
#include "ProjectInfos/configs.h"
#include "ProjectInfos/projectinfos.h"
#include "Events/Event.h"
#include "Events/Args/projectloadedevent.h"
#include "Events/Args/clearevent.h"
#include "Events/Args/saveevent.h"
#include "dock.h"
#include "fileexplorer.h"
#include "UI/Animation/animationsinfos.h"
#include "UI/Animation/centralanimationwidget.h"
#include "UI/Animator/animatorinfos.h"
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
        auto selectModeAction = editMenu->addAction("Mode de &selection");
        selectModeAction->setShortcut(QKeySequence("Tab"));

    QMenu *windowMenu = menuBar()->addMenu("&Fenetre");
        auto showExplorer = windowMenu->addAction("Afficher l'explorer");
        auto showAssetDocks = windowMenu->addAction("Reafficher les docks");

    connect(newAction, SIGNAL(triggered(bool)), this, SLOT(onNew()));
    connect(loadAction, SIGNAL(triggered(bool)), this, SLOT(onLoad()));
    connect(saveAction, SIGNAL(triggered(bool)), this, SLOT(onSave()));
    connect(saveAndQuitAction, SIGNAL(triggered(bool)), this, SLOT(onSaveAndQuit()));

    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(onUndo()));
    connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(onRedo()));
    connect(copyAction, SIGNAL(triggered(bool)), this, SLOT(onCopy()));
    connect(cutAction, SIGNAL(triggered(bool)), this, SLOT(onCut()));
    connect(pastAction, SIGNAL(triggered(bool)), this, SLOT(onPast()));
    connect(selectModeAction, SIGNAL(toggled(bool)), this, SLOT(onSelectMode(bool)));

    connect(showExplorer, SIGNAL(triggered(bool)), this, SLOT(onShowExplorer()));
    connect(showAssetDocks, SIGNAL(triggered(bool)), this, SLOT(onShowAssetDocks()));
}

void MainWindow::createDocks()
{
    m_explorerDock = new Dock<FileExplorer>("Explorer", false);
    addDockWidget(Qt::LeftDockWidgetArea, m_explorerDock);
    AnimatorInfos* i = new AnimatorInfos("");
    addDockWidget(Qt::RightDockWidgetArea, new Dock<AnimatorInfos>(i, "Animator", true));
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
    QMessageBox::information(this, "Not implemented", "Undo n'est pas encore implémenté, veuillez reessayer plus tard.");
}

void MainWindow::onRedo()
{
    QMessageBox::information(this, "Not implemented", "Redo n'est pas encore implémenté, veuillez reessayer plus tard.");
}

void MainWindow::onCopy()
{
    QMessageBox::information(this, "Not implemented", "Copy n'est pas encore implémenté, veuillez reessayer plus tard.");
}

void MainWindow::onCut()
{
    QMessageBox::information(this, "Not implemented", "Cut n'est pas encore implémenté, veuillez reessayer plus tard.");
}

void MainWindow::onPast()
{
    QMessageBox::information(this, "Not implemented", "Past n'est pas encore implémenté, veuillez reessayer plus tard.");
}

void MainWindow::onSelectMode(bool /*mode*/)
{
    QMessageBox::information(this, "Not implemented", "Le mode selection n'est pas encore implémenté, veuillez reessayer plus tard.");
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

        break;
    case AssetType::Scene:

        break;
    case AssetType::Tileset:

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
    addDockWidget(Qt::RightDockWidgetArea, m_assetDocks.front());
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

