#include "scenenode.h"

SceneNode::SceneNode(const QJsonObject &obj)
    : name(obj["name"].toString())
    , parent(nullptr)
    , object(obj["obj"].toObject())
{

}

QString SceneNode::globalName() const
{
    if(parent != nullptr)
        return parent->globalName() + "/" + name;
    return name;
}

QJsonObject SceneNode::save() const
{
    QJsonObject obj;

    obj.insert("obj", object.save());
    obj.insert("name", name);

    return obj;
}
