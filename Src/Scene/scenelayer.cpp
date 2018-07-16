#include "scenelayer.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

SceneLayer::SceneLayer(const QString & _name)
    : name(_name)
{

}

SceneLayer::SceneLayer(const QJsonObject & obj)
{
    load(obj);
}

QJsonObject SceneLayer::save() const
{
    QJsonObject obj;
    QJsonArray nodes;
    QJsonArray indexs;
    for(unsigned int i(0) ; i < size() ; i++)
    {
        const auto & node = (*this)[i];

        nodes.append(node->save());
        if(node->parent != nullptr)
        {
            QJsonArray index;
            index.append(int(i));
            auto it = std::find_if(begin(), end(), [parent = node->parent](const auto & n){return n.get() == parent;});
            if(it == end())
                continue;
            index.append(std::distance(begin(), it));
            indexs.append(index);
        }
    }
    obj.insert("nodes", nodes);
    obj.insert("indexs", indexs);
    obj.insert("name", name);

    return obj;
}

void SceneLayer::load(const QJsonObject & obj)
{
    name = obj["name"].toString();

    for(const auto & jsonNode : obj["nodes"].toArray())
        push_back(std::make_unique<SceneNode>(jsonNode.toObject()));

    for(const auto & jsonIndex : obj["indexs"].toArray())
    {
        auto index = jsonIndex.toArray();
        auto current = index[0].toInt();
        auto parent = index[1].toInt();

        if(current >= 0 && parent >= 0 && current < int(size()) && parent < int(size()) && current != parent)
        {
            (*this)[current]->parent = (*this)[parent].get();
            (*this)[parent]->childrens.push_back((*this)[current].get());
        }
    }
}

unsigned int SceneLayer::indexOf(SceneNode * node) const
{
    auto it = std::find_if(begin(), end(), [node](const auto & n){return n.get() == node;});
    if(it == end())
        return -1;
    return std::distance(begin(), it);
}
