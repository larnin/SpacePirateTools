#include "scenenodeinfos.h"
#include "UI/linewidget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>

SceneNodeInfos::SceneNodeInfos(QWidget *parent)
    : QWidget(parent)
{
    m_revertObjectButton = new QPushButton("Revert object");
    m_revertPrefabButton = new QPushButton("Revert prefab");
    QHBoxLayout * revertLayout = new QHBoxLayout();
    revertLayout->addWidget(m_revertObjectButton);
    revertLayout->addWidget(m_revertPrefabButton);

    m_nameWidget = new QLineEdit();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Nom : "));
    nameLayout->addWidget(m_nameWidget);

    m_propertiesLayout = new QVBoxLayout();
    QWidget* w = new QWidget();
    w->setLayout(m_propertiesLayout);

    QScrollArea * area = new QScrollArea();
    area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    area->setWidgetResizable(true);
    area->setWidget(w);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(revertLayout);
    layout->addLayout(nameLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(area);

    setLayout(layout);

    setNode(nullptr);

    connect(m_revertPrefabButton, SIGNAL(clicked(bool)), this, SLOT(onRevertPrefabClick()));
    connect(m_revertObjectButton, SIGNAL(clicked(bool)), this, SLOT(onRevertObjectClick()));
}

void SceneNodeInfos::setNode(SceneNode * node)
{
    m_node = node;
    updatePropertiesList();
    updateButtonsState();
    updateName();
}

void SceneNodeInfos::updatePropertiesList()
{
    clearPropertiesList();

    if(m_node == nullptr)
        return;

    for(const auto & p : m_node->object)
    {
        PropertyWidget* widget = new PropertyWidget(*p, false);
        m_propertiesLayout->addWidget(widget);
        m_properties.push_back(widget);
    }
}

void SceneNodeInfos::clearPropertiesList()
{
    for(auto & e : m_properties)
    {
        m_propertiesLayout->removeWidget(e);
        delete e;
    }
    m_properties.clear();
}

void SceneNodeInfos::updateButtonsState()
{
    if(m_node == nullptr)
    {
        m_revertObjectButton->setEnabled(false);
        m_revertPrefabButton->setEnabled(false);
        return;
    }
    m_revertObjectButton->setEnabled(true);
    m_revertObjectButton->setEnabled(!m_node->prefabName.isEmpty());
}

void SceneNodeInfos::updateName()
{
    if(m_node == nullptr)
    {
        m_nameWidget->setText("Pas de node selectionnée");
        m_nameWidget->setEnabled(false);
        return;
    }
    m_nameWidget->setEnabled(true);
    m_nameWidget->setText(m_node->name);
}

void SceneNodeInfos::onRevertObjectClick()
{
    //todo
}

void SceneNodeInfos::onRevertPrefabClick()
{
    emit requestRevert(m_node);
}
