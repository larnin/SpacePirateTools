#ifndef SCENENODE_H
#define SCENENODE_H

#include "Object/objectdata.h"
#include <SFML/Graphics/Transform.hpp>
#include <QJsonObject>
#include <vector>

class SceneNode
{
public:
    SceneNode(const QString & _name, const QString & _objectName);
    SceneNode(const QJsonObject & obj);
    SceneNode(const ObjectData & _object);

    std::unique_ptr<SceneNode> clone() const;

    void revertObject(const QString & modelName);
    void revertObject(SceneNode & node);

    QJsonObject save() const;

    ObjectValueTransform getLocalTransform() const;
    ObjectValueTransform getTransform() const;

    void loadObject(const QString & _objectName);

    SceneNode * parent;
    std::vector<SceneNode*> childrens;

    ObjectData object;

    QString name;

    QString objectName;
    QString prefabName;

private:
};

#endif // SCENENODE_H
