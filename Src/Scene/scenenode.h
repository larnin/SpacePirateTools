#ifndef SCENENODE_H
#define SCENENODE_H

#include "Object/objectdata.h"
#include <SFML/Graphics/Transform.hpp>
#include <vector>

class SceneNode
{
public:
    SceneNode();

    ObjectValueTransform getLocalTransform() const;
    ObjectValueTransform getTransform() const;

    SceneNode * parent;
    std::vector<SceneNode> * childrens;

    ObjectData object;

    QString name;
};

#endif // SCENENODE_H
