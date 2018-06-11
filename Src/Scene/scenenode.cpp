#include "scenenode.h"

SceneNode::SceneNode()
{

}

ObjectValueTransform SceneNode::getLocalTransform() const
{
    return object.transform();
}

ObjectValueTransform SceneNode::getTransform() const
{
    if(parent == null)
        return object.transform();

    auto parentTransform = parent->getTransform();
    auto transform = object.transform();


}
