#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include "Value/objectvaluebase.h"
#include <QString>
#include <QWidget>
#include <memory>
#include <vector>

enum class InspectorVisibility
{
    Hidden,
    Visible,
    AsString,
    Max = AsString
};

QString inspectorVisibilityToString(InspectorVisibility v);

enum class SceneVisibility
{
    RenderOnly,
    GizmoOnly,
    All,
    None,
    Max = None
};

QString sceneVisibilityToString(SceneVisibility v);

class ObjectProperty
{
public:
    ObjectProperty() = default;
    ObjectProperty(ObjectProperty &&) = default;
    ObjectProperty & operator=(ObjectProperty &&) = default;

    std::unique_ptr<ObjectProperty> clone() const;

    QString name;
    std::vector<std::unique_ptr<ObjectValueBase>> values;
    InspectorVisibility inspectorVisibility;
    SceneVisibility sceneVisibility;
    bool fixedSize;
};

#endif // OBJECTPROPERTY_H
