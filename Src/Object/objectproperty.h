#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include "Value/objectvaluebase.h"
#include <QString>
#include <memory>

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

    QString name;
    std::unique_ptr<ObjectValueBase> value;
    InspectorVisibility inspectorVisibility;
    SceneVisibility sceneVisibility;
};

#endif // OBJECTPROPERTY_H
