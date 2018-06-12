#include "scenenode.h"

SceneNode::SceneNode()
{

}

SceneNode::SceneNode(const QJsonObject & obj)
{

}

QJsonObject SceneNode::save() const
{
    return {};
}

ObjectValueTransform SceneNode::getLocalTransform() const
{
    return object.transform();
}

ObjectValueTransform SceneNode::getTransform() const
{
    if(parent == nullptr)
        return object.transform();

    auto parentTransform = parent->getTransform();
    auto transform = object.transform();

    //todo child transform transformed with parent transform

    return transform;
}
