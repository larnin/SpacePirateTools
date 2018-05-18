#include "prefabdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>

PrefabData::PrefabData()
{

}


PrefabData::PrefabData(const QString & fileName)
{
    load(fileName);
}

void PrefabData::save(const QString & fileName) const
{
    QJsonObject obj;

    QJsonArray objects;
    for(const auto & v : *this)
        objects.append(v->save());
    obj.insert("objects", objects);
    obj.insert("nodes", saveNodesHierarchy());

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void PrefabData::load(const QString & fileName)
{
    QFile file(fileName);
    if(!file.exists())
        return;
    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &error));
    file.close();
    if(error.error != QJsonParseError::NoError)
        return;
    if(!doc.isObject())
        return;

    QJsonObject obj(doc.object());

    auto objects = obj.find("objects");
    if(!objects->isArray())
        return;

    for(const auto & value : objects->toArray())
        emplace_back(std::make_unique<SceneNode>(value.toObject()));

    loadNodesHierarchy(obj["nodes"].toArray());
}

void PrefabData::loadNodesHierarchy(const QJsonArray & hierarchy)
{
    if(hierarchy.size() != int(size() * 2))
        return;

    for(unsigned int i(0) ; i < size() ; i++)
    {
        unsigned int v1 = hierarchy[2*i].toInt();
        unsigned int v2 = hierarchy[2*i+1].toInt();

        (*this)[v1]->parent = (*this)[v2].get();
        (*this)[v2]->childrens.push_back((*this)[v1].get());
    }
}

QJsonArray PrefabData::saveNodesHierarchy() const
{
    QJsonArray array;
    for(unsigned int i(0) ; i < size() ; i++)
    {
        auto it = std::find_if(begin(), end(), [parent = (*this)[i]->parent](const auto & v){return v.get() == parent;});
        array.append(int(i));
        array.append(std::distance(begin(), it));
    }
    return array;
}
