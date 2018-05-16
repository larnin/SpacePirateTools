#include "colliderlayerdialog.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/linewidget.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

ColliderLayerDialog::ColliderLayerDialog(QWidget * parent)
    : QDialog(parent)
{
    m_layerList = new QListWidget();

    m_r = new QSpinBox();
    m_g = new QSpinBox();
    m_b = new QSpinBox();
    m_colorbutton = new QPushButton("");
    updateColorButton(sf::Color::White);
    QHBoxLayout * colorLayout = new QHBoxLayout();
    colorLayout->addWidget(new QLabel("Couleur : "));
    colorLayout->addWidget(new QLabel("R"));
    colorLayout->addWidget(m_r, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(new QLabel("G"));
    colorLayout->addWidget(m_g, 1);
    colorLayout->addSpacing(10);
    colorLayout->addWidget(new QLabel("B"));
    colorLayout->addWidget(m_b, 1);
    colorLayout->addWidget(m_colorbutton);

    QVBoxLayout * listLayout = new QVBoxLayout();
    listLayout->addWidget(new QLabel("Layers :"));
    listLayout->addWidget(m_layerList, 1);
    listLayout->addLayout(colorLayout);

    m_pointsLayout = new QGridLayout();
    for(unsigned int i(0) ; i < ProjectInfos::instance().options().colliderLayers.size() ; i++)
        addPoints(i);
    QVBoxLayout * pointsLayout = new QVBoxLayout();
    pointsLayout->addLayout(m_pointsLayout);
    pointsLayout->addStretch(1);

    QHBoxLayout * fullLayout = new QHBoxLayout();
    fullLayout->addLayout(listLayout, 1);
    fullLayout->addWidget(new LineWidget(LineOrientation::Vertical));
    fullLayout->addLayout(pointsLayout);

    QPushButton * acceptButton = new QPushButton("Valider");
    QPushButton * cancelButton = new QPushButton("Annuler");
    QHBoxLayout * buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(fullLayout);
    layout->addLayout(buttonsLayout);

    setLayout(layout);
}

unsigned int ColliderLayerDialog::get() const
{
    return 0;
}

unsigned int ColliderLayerDialog::getNewLayerID(QWidget* parent, bool *ok)
{
    ColliderLayerDialog dialog(parent);
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
        m_layerList->addItem(l.name);

    m_layerList->blockSignals(false);

    m_layerList->setCurrentRow(index);
}

void ColliderLayerDialog::updateColorButton(sf::Color color)
{
    constexpr int size(30);
    QPixmap map(size, size);
    map.fill(QColor(color.r, color.g, color.b));
    m_colorbutton->setIcon(QIcon(map));
}

void ColliderLayerDialog::addPoints(unsigned int index)
{

}
