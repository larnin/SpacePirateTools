#include "colliderlayerdialog.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/linewidget.h"
#include "UI/verticallabel.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QMenu>

sf::Color defaultLayerColor(unsigned int layer);

ColliderLayerDialog::ColliderLayerDialog(bool showButtons, QWidget * parent)
    : QDialog(parent)
{
    m_layerList = new QListWidget();

    QVBoxLayout * listLayout = new QVBoxLayout();
    listLayout->addWidget(new QLabel("Layers :"));
    listLayout->addWidget(m_layerList, 1);

    m_pointsLayout = new QGridLayout();
    QVBoxLayout * pointsLayout = new QVBoxLayout();
    pointsLayout->addWidget(new QLabel("Layer matrix"));
    pointsLayout->addLayout(m_pointsLayout);
    pointsLayout->addStretch(1);
    pointsLayout->addWidget(new QLabel("Checked : Collision entre les layers"));
    pointsLayout->addWidget(new QLabel("Point : Trigger - ne bloque pas"));

    QHBoxLayout * fullLayout = new QHBoxLayout();
    fullLayout->addLayout(listLayout, 1);
    fullLayout->addWidget(new LineWidget(LineOrientation::Vertical));
    fullLayout->addLayout(pointsLayout);


    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    if(showButtons)
    {
        QPushButton * acceptButton = new QPushButton("Valider");
        QPushButton * cancelButton = new QPushButton("Annuler");
        buttonsLayout->addWidget(acceptButton);
        buttonsLayout->addWidget(cancelButton);
        connect(acceptButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
        connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    }

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(fullLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    updateLayerList();
    setPoints();

    m_layerList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_layerList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClickLayerList(QPoint)));
}

unsigned int ColliderLayerDialog::get() const
{
    return 0;
}

unsigned int ColliderLayerDialog::getNewLayerID(bool showButtons, QWidget* parent, bool *ok)
{
    ColliderLayerDialog dialog(showButtons, parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}

void ColliderLayerDialog::updateLayerList()
{
    m_layerList->blockSignals(true);

    int index = m_layerList->currentRow();

    m_layerList->clear();

    for(const auto & l : ProjectInfos::instance().options().colliderLayers)
        m_layerList->addItem(new QListWidgetItem(makeIcon(l.color), l.name));

    m_layerList->blockSignals(false);

    m_layerList->setCurrentRow(index);
}

QIcon ColliderLayerDialog::makeIcon(const sf::Color & color)
{
    constexpr unsigned int size(30);
    QPixmap map(size, size);
    map.fill(QColor(color.r, color.g, color.b));
    return QIcon(map);
}

void ColliderLayerDialog::setPoints()
{
    auto del([layout = m_pointsLayout](QWidget * w){layout->removeWidget(w); delete w;});

    for(auto l : m_xLabels)
        del(l);
    for(auto l : m_yLabels)
        del(l);
    for(const auto & l : m_checkboxs)
        del(l.second);
    m_xLabels.clear();
    m_yLabels.clear();
    m_checkboxs.clear();

    constexpr unsigned int maxIndex = 32;

    for(unsigned int index(0) ; index < ProjectInfos::instance().options().colliderLayers.size() && index < maxIndex ; index++)
    {
        const auto & layer = ProjectInfos::instance().options().colliderLayers[index];

        QLabel * yLabel = new QLabel(layer.name);
        VerticalLabel * xLabel = new VerticalLabel(layer.name);

        m_xLabels.push_back(xLabel);
        m_yLabels.push_back(yLabel);

        m_pointsLayout->addWidget(xLabel, 0, maxIndex - index, 1, 1, Qt::AlignBottom);
        m_pointsLayout->addWidget(yLabel, index + 1, 0, 1, 1, Qt::AlignRight);

        for(unsigned int i(0) ; i <= index ; i++)
        {
            QCheckBox * check = new QCheckBox("");
            check->setTristate(true);
            m_checkboxs.push_back(std::make_pair(sf::Vector2u(index, i), check));
            m_pointsLayout->addWidget(check, i + 1, maxIndex - index);

            connect(check, &QCheckBox::stateChanged, this, [this, index, i](const auto & state){this->onCheck(index, i, Qt::CheckState(state));});
        }
    }
}

void ColliderLayerDialog::onCheck(unsigned int x, unsigned int y, Qt::CheckState state)
{

}

void ColliderLayerDialog::onRightClickLayerList(QPoint point)
{
    QPoint globalPos(m_layerList->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aRename(nullptr);
    QAction *aColor(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    int current = m_layerList->currentRow();

    if(current >= 0 && current < m_layerList->count())
    {
        aDel = menu.addAction("Supprimer");
        aRename = menu.addAction("Renommer");
        aColor = menu.addAction("Colorer");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
    {

    }

    if(action == aRename)
    {

    }

    if(action == aColor)
    {

    }

    if(action == aAdd)
    {

    }
}

sf::Color defaultLayerColor(unsigned int layer)
{
    std::vector<sf::Color> colors
    {
        {255, 0, 0},
        {255, 255, 0},
        {128, 255, 0},
        {0, 255, 64},
        {0, 255, 255},
        {0, 128, 192},
        {255, 0, 255},
        {128, 0, 0},
        {255, 128, 0},
        {128, 128, 0},
        {0, 128, 0},
        {0, 0, 255},
        {0, 128, 255},
        {255, 128, 192},
        {128, 64, 0},
        {128, 128, 128}
    };
    return colors[layer % colors.size()];
}
