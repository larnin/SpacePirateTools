#ifndef SCENENODEINFOS_H
#define SCENENODEINFOS_H

#include "Scene/scenenode.h"
#include "UI/Object/propertywidget.h"
#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QLabel>
#include <vector>

class SceneNodeInfos : public QWidget
{
    Q_OBJECT
public:
    SceneNodeInfos(QWidget * parent = nullptr);

public slots:
    void setNode(SceneNode * node);
    void onRevertObjectClick();
    void onRevertPrefabClick();
    void onNameChanged();

signals:
    void requestRevert(SceneNode * n);
    void nameChanged(SceneNode * n);

private:
    void updatePropertiesList();
    void clearPropertiesList();
    void updateButtonsState();
    void updateName();

    SceneNode * m_node;
    QLineEdit* m_nameWidget;
    QVBoxLayout* m_propertiesLayout;
    std::vector<PropertyWidget*> m_properties;
    QPushButton* m_revertObjectButton;
    QLabel * m_objectLabel;
    QPushButton* m_revertPrefabButton;
    QLabel * m_prefabLabel;
};

#endif // SCENENODEINFOS_H
