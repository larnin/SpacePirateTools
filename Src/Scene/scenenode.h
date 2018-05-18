#ifndef SCENENODE_H
#define SCENENODE_H

#include "Object/objectdata.h"
#include <QString>
#include <vector>

class SceneNode
{
public:
    SceneNode(const QJsonObject & obj);

    QString globalName() const;

    QJsonObject save() const;

    QString name;
    SceneNode * parent;
    std::vector<SceneNode*> childrens;

    ObjectData object;
};

#endif // SCENENODE_H
