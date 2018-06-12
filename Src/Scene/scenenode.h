#ifndef SCENENODE_H
#define SCENENODE_H

#include "Object/objectdata.h"
#include <SFML/Graphics/Transform.hpp>
#include <QJsonObject>
#include <vector>

class SceneNode
{
public:
    SceneNode();
    SceneNode(const QJsonObject & obj);

    QJsonObject save() const;

    ObjectValueTransform getLocalTransform() const;
    ObjectValueTransform getTransform() const;

    SceneNode * parent;
    std::vector<SceneNode> * childrens;

    ObjectData object;

    QString name;
};

#endif // SCENENODE_H
