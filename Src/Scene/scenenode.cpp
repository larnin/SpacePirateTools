#include "scenenode.h"
#include "ProjectInfos/projectinfos.h"

SceneNode::SceneNode(const QString &_name, const QString &_objectName)
    : name(_name)
{
    loadObject(_objectName);
}

SceneNode::SceneNode(const QJsonObject & obj)
    : object(obj["object"].toObject())
{
    name = obj["name"].toString();
    objectName = obj["objectName"].toString();
    prefabName = obj["prefabName"].toString();
}

QJsonObject SceneNode::save() const
{
    QJsonObject obj;
    obj.insert("object", object.save());
    obj.insert("name", name);
    obj.insert("objectName", objectName);
    obj.insert("prefabName", prefabName);

    return obj;
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

void SceneNode::loadObject(const QString & _objectName)
{
    objectName = _objectName;
    auto fullName = ProjectInfos::instance().projectDirectory() + "/" + assetTypeToString(AssetType::Object) + "/" + objectName;
    object = ObjectData(fullName);
}
