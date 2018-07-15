#include "scenenodeinfos.h"
#include "ProjectInfos/projectinfos.h"
#include "UI/linewidget.h"
#include <QHBoxLayout>
#include <QScrollArea>

SceneNodeInfos::SceneNodeInfos(QWidget *parent)
    : QWidget(parent)
{
    m_objectLabel = new QLabel("none");
    m_revertObjectButton = new QPushButton("Revert object");
    m_prefabLabel = new QLabel("none");
    m_revertPrefabButton = new QPushButton("Revert prefab");
    QHBoxLayout * revertObjectLayout = new QHBoxLayout();
    revertObjectLayout->addWidget(m_objectLabel);
    revertObjectLayout->addWidget(m_revertObjectButton);
    QHBoxLayout * revertPrefabLayout = new QHBoxLayout();
    revertPrefabLayout->addWidget(m_prefabLabel);
    revertPrefabLayout->addWidget(m_revertPrefabButton);

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
    layout->addLayout(revertObjectLayout);
    layout->addLayout(revertPrefabLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(nameLayout);
    layout->addWidget(area);

    setLayout(layout);

    setNode(nullptr);

    connect(m_revertPrefabButton, SIGNAL(clicked(bool)), this, SLOT(onRevertPrefabClick()));
    connect(m_revertObjectButton, SIGNAL(clicked(bool)), this, SLOT(onRevertObjectClick()));
    connect(m_nameWidget, SIGNAL(editingFinished()), this, SLOT(onNameChanged()));
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
        m_objectLabel->setEnabled(false);
        m_prefabLabel->setEnabled(false);
        m_objectLabel->setText("none");
        m_prefabLabel->setText("none");
        return;
    }
    m_revertObjectButton->setEnabled(true);
    m_revertObjectButton->setEnabled(!m_node->objectName.isEmpty());
    m_objectLabel->setEnabled(true);
    m_prefabLabel->setEnabled(!m_node->prefabName.isEmpty());
    m_objectLabel->setText(m_node->objectName);
    m_prefabLabel->setText(!m_node->prefabName.isEmpty() ? "none" : m_node->prefabName);
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
    if(!ProjectInfos::instance().fileExist(m_node->objectName, AssetType::Object))
    {
        m_node->objectName = "";
        updateName();
        return;
    }

    m_node->revertObject(m_node->objectName);
    setNode(m_node);
}

void SceneNodeInfos::onRevertPrefabClick()
{
    if(!m_node->prefabName.isEmpty())
        emit requestRevert(m_node);
}

void SceneNodeInfos::onNameChanged()
{
    if(m_node == nullptr)
        return;

    m_node->name = m_nameWidget->text();
    emit nameChanged(m_node);
}
