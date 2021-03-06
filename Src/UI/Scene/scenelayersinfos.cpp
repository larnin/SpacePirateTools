#include "scenelayersinfos.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QColorDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QMenu>

SceneLayersinfos::SceneLayersinfos(const QString &assetName, SceneLayerInfos * layerInfosWidget, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName)
    , m_layerInfosWidget(layerInfosWidget)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , m_currentIndex(-1)
{
    initializeWidgets();
    updateColorButton();
    updateLayerList();
}

SceneLayersinfos::~SceneLayersinfos()
{
    m_datas.save(m_assetName);
}

void SceneLayersinfos::initializeWidgets()
{
    m_colorButton = new QPushButton("");
    m_colorButton->setFixedWidth(30);
    QHBoxLayout * colorLayout = new QHBoxLayout();
    colorLayout->addWidget(new QLabel("Couleur de fond :"));
    colorLayout->addWidget(m_colorButton);

    m_layers = new QListWidget();
    QVBoxLayout* layout = new QVBoxLayout();
    layout->addLayout(colorLayout);
    layout->addSpacing(5);
    layout->addWidget(new QLabel("Layers :"));
    layout->addWidget(m_layers, 1);

    setLayout(layout);

    connect(m_colorButton, SIGNAL(clicked(bool)), this, SLOT(onColorClicked()));
    m_layers->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_layers, SIGNAL(currentRowChanged(int)), this, SLOT(onLayerIndexChange(int)));
    connect(m_layers, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onLayerRightClick(QPoint)));
}

void SceneLayersinfos::updateColorButton()
{
    constexpr int size(30);
    QPixmap map(size, size);
    auto color = m_datas.backgroundColor;
    map.fill(QColor(color.r, color.g, color.b));
    m_colorButton->setIcon(QIcon(map));
}

void SceneLayersinfos::updateLayerList()
{
    m_layers->blockSignals(true);

   m_layers->clear();

   for(unsigned int i(0) ; i < m_datas.size() ; i++)
   {
       const auto & layer = m_datas[i];
       m_layers->addItem(layer->name);
       auto item = m_layers->item(m_layers->count() - 1);

       QWidget* widget = new QWidget();
       QPushButton* showButton = new QPushButton(QIcon("Img/View.png"), "");
       showButton->setFixedSize(24, 24);
       showButton->setCheckable(true);
       showButton->setChecked(!layer->hidden);
       QPushButton* gizmoButton = new QPushButton(QIcon("Img/Gizmos.png"), "");
       gizmoButton->setFixedSize(24, 24);
       gizmoButton->setCheckable(true);
       gizmoButton->setChecked(layer->showGizmos);
       QHBoxLayout* layout = new QHBoxLayout();
       layout->addStretch(1);
       layout->addWidget(showButton);
       layout->addWidget(gizmoButton);
       layout->setContentsMargins(0, 0, 0, 0);
       widget->setLayout(layout);
       item->setSizeHint(widget->sizeHint());
       m_layers->setItemWidget(item, widget);

       connect(showButton, &QPushButton::toggled, this, [this, i](bool value){updateVisibility(i, value);});
       connect(gizmoButton, &QPushButton::toggled, this, [this, i](bool value){updateGizmos(i, value);});
   }

   m_layers->blockSignals(false);

   if(m_currentIndex < m_layers->count())
       m_layers->setCurrentRow(m_currentIndex);
   onLayerIndexChange(m_layers->currentRow());
}

void SceneLayersinfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void SceneLayersinfos::onColorClicked()
{
    QColor oldColor(m_datas.backgroundColor.r, m_datas.backgroundColor.g, m_datas.backgroundColor.b);
    auto color = QColorDialog::getColor(oldColor, this, "Couleur de fond");
    if(!color.isValid())
        return;

    m_datas.backgroundColor = sf::Color(color.red(), color.green(), color.blue());
    updateColorButton();
}

void SceneLayersinfos::onLayerIndexChange(int index)
{
    m_currentIndex = index;
    if(m_layerInfosWidget != nullptr)
    {
        if(m_currentIndex >= 0 && m_currentIndex <= int(m_datas.size()))
            m_layerInfosWidget->setCurrentLayer(m_datas[m_currentIndex].get());
        else m_layerInfosWidget->setCurrentLayer(nullptr);
    }

    emit currentLayerChanged(index);
}

void SceneLayersinfos::onLayerRightClick(QPoint point)
{
    QPoint globalPos(m_layers->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aUp(nullptr);
    QAction *aDown(nullptr);
    QAction *aRename(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentIndex >= 0 && m_currentIndex < int(m_datas.size()))
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renommer");
        if(m_currentIndex > 0)
            aUp = menu.addAction("Monter");
        if(m_currentIndex < int(m_datas.size()) - 1)
            aDown = menu.addAction("Descendre");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
        delLayer(m_currentIndex);

    if(action == aUp)
        upLayer(m_currentIndex);

    if(action == aDown)
        downLayer(m_currentIndex);

    if(action == aRename)
        renameLayer(m_currentIndex);

    if(action == aAdd)
        addLayer();
}

void SceneLayersinfos::updateGizmos(unsigned int index, bool value)
{
    if(m_datas.size() <= index)
            return;

    m_datas[index]->showGizmos = value;
}

void SceneLayersinfos::updateVisibility(unsigned int index, bool value)
{
    if(m_datas.size() <= index)
            return;

    m_datas[index]->hidden = !value;
}

void SceneLayersinfos::addLayer()
{
    bool ok = true;
    auto layerName = QInputDialog::getText(this, "Nouveau layer", "Indiquez le nom du nouveau layer", QLineEdit::Normal, "", &ok);

    if(!ok)
        return;

    m_datas.emplace_back(std::make_unique<SceneLayer>(layerName));
    updateLayerList();
}

void SceneLayersinfos::delLayer(unsigned int index)
{
    auto answer = QMessageBox::question(this, "Supprimer un layer", "Etes vous sur de vouloir supprimer ce layer ?");
    if(answer != QMessageBox::Yes)
        return;

    m_datas.erase(m_datas.begin() + index);
    updateLayerList();
}

void SceneLayersinfos::upLayer(unsigned int index)
{
    if(index == 0)
        return;

    std::swap(m_datas[index], m_datas[index - 1]);
    updateLayerList();
}

void SceneLayersinfos::downLayer(unsigned int index)
{
    if(index >= m_datas.size() - 1)
        return;

    std::swap(m_datas[index], m_datas[index + 1]);
    updateLayerList();
}

void SceneLayersinfos::renameLayer(unsigned int index)
{
    auto & l = m_datas[index];
    bool ok = true;
    auto name = QInputDialog::getText(this, "Renommer un layer", "Indiquez le nouveau nom du layer", QLineEdit::Normal, l->name, &ok);

    if(ok)
    {
        l->name = name;
        updateLayerList();
    }
}

