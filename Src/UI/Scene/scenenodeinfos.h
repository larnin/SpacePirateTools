#ifndef SCENENODEINFOS_H
#define SCENENODEINFOS_H

#include "Scene/scenenode.h"
#include "UI/Object/propertywidget.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <vector>

class SceneNodeInfos : public QWidget
{
    Q_OBJECT
public:
    SceneNodeInfos(QWidget * parent = nullptr);
    void setNode(SceneNode * node);

private:
    void updatePropertiesList();
    void updateButtonsState();

    SceneNode * m_node;
    QLineEdit* m_nameWidget;
    QVBoxLayout* m_propertiesLayout;
    std::vector<PropertyWidget> m_properties;
    QPushButton* m_revertObjectButton;
    QPushButton* m_revertPrefabButton;
};

#endif // SCENENODEINFOS_H
