#include "scenenodeinfos.h"
#include "UI/linewidget.h"
#include <QHBoxLayout>
#include <QLabel>

SceneNodeInfos::SceneNodeInfos(QWidget *parent)
    : QWidget(parent)
{
    QHBoxLayout * revertLayout = new QHBoxLayout();
    m_revertObjectButton = new QPushButton("Revert object");
    m_revertPrefabButton = new QPushButton("Revert prefab");

    m_nameWidget = new QLineEdit();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Nom : "));
    nameLayout->addWidget(m_nameWidget);

    m_propertiesLayout = new QVBoxLayout();

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(revertLayout);
    layout->addLayout(nameLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addLayout(m_propertiesLayout);
}

void SceneNodeInfos::setNode(SceneNode * node)
{
    m_node = node;
    updatePropertiesList();
}

void SceneNodeInfos::updatePropertiesList()
{

}

void SceneNodeInfos::updateButtonsState()
{

}
