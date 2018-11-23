#include "objectproperty.h"
#include <cassert>

QString inspectorVisibilityToString(InspectorVisibility v)
{
    switch(v)
    {
    case InspectorVisibility::Hidden:
        return "Caché";
    case InspectorVisibility::Visible:
        return "Visible";
    case InspectorVisibility::AsString:
        return "En String";
    }

    assert(false);
    return "";
}

QString sceneVisibilityToString(SceneVisibility v)
{
    switch (v)
    {
    case SceneVisibility::RenderOnly:
        return "Seulement le rendu";
    case SceneVisibility::GizmoOnly:
        return "Seulement les gizmos";
    case SceneVisibility::All:
        return "Tout";
    case SceneVisibility::None:
        return "Rien";
    }

    assert(false);
    return "";
}

std::unique_ptr<ObjectProperty> ObjectProperty::clone() const
{
    std::unique_ptr<ObjectProperty> property(std::make_unique<ObjectProperty>());
    property->name = name;
    property->inspectorVisibility = inspectorVisibility;
    property->sceneVisibility = sceneVisibility;

    property->value = value->clone();

    return property;
}
