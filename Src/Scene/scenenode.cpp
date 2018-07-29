#include "scenenode.h"
#include "ProjectInfos/projectinfos.h"

SceneNode::SceneNode(const QString &_name, const QString &_objectName)
    : parent(nullptr)
    , name(_name)
{
    loadObject(_objectName);
}

SceneNode::SceneNode(const QJsonObject & obj)
    : parent(nullptr)
    , object(obj["object"].toObject())
{
    name = obj["name"].toString();
    objectName = obj["objectName"].toString();
    prefabName = obj["prefabName"].toString();
}

SceneNode::SceneNode(const ObjectData & _object)
    : parent(nullptr)
    , object(_object)
{

}

std::unique_ptr<SceneNode> SceneNode::clone() const
{
    std::unique_ptr<SceneNode> node(std::make_unique<SceneNode>(object));
    node->name = name;
    node->objectName = objectName;
    node->prefabName = prefabName;

    return node;
}

void SceneNode::revertObject(const QString & modelName)
{
    if(!ProjectInfos::instance().fileExist(modelName, AssetType::Object))
        return;

    SceneNode temp("Temp", modelName);
    revertObject(temp);
}

void SceneNode::revertObject(SceneNode & node)
{
    //remove everything else the Transform at index 0
    for(unsigned int i(0) ; i < object.size() ; i++)
        object.pop_back();

    //temp node vampirisation
    for(unsigned int i(1) ; i < node.object.size() ; i++)
        object.emplace_back(std::move(node.object[i]));
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
    auto fullName = ProjectInfos::instance().fullFileName(objectName, AssetType::Object);
    object = ObjectData(fullName);
}
