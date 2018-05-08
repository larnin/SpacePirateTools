#ifndef OBJECTPROPERTY_H
#define OBJECTPROPERTY_H

#include <QString>

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
    //add value

    InspectorVisibility inspectorVisibility;
    SceneVisibility sceneVisibility;
};

#endif // OBJECTPROPERTY_H
