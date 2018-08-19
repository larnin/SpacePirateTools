#include "scenedata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

SceneData::SceneData(const QString & fileName)
{
    load(fileName);
}

void SceneData::save(const QString & fileName) const
{
    QJsonObject obj;

    obj.insert("r", static_cast<int>(backgroundColor.r));
    obj.insert("g", static_cast<int>(backgroundColor.g));
    obj.insert("b", static_cast<int>(backgroundColor.b));

    QJsonArray layers;
    for(const auto & l : *this)
        layers.append(l->save());
    obj.insert("layers", layers);

    QFile file(fileName);
    if(!file.exists())
        return;
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void SceneData::load(const QString & fileName)
{
    clear();

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

    backgroundColor.r = obj["r"].toInt();
    backgroundColor.g = obj["g"].toInt();
    backgroundColor.b = obj["b"].toInt();

    for(const auto l : obj["layers"].toArray())
        emplace_back(std::make_unique<SceneLayer>(l.toObject()));
}

std::vector<std::unique_ptr<SceneNode>> SceneData::asPrefab()
{
    if(empty())
        return {};
    auto & layer = *((*this)[0].get());
    if(layer.empty())
        return {};
    auto parent = std::find_if(layer.begin(), layer.end(), [](const auto & node){return node->parent == nullptr;});
    if(parent == layer.end())
        return {};
    std::vector<std::unique_ptr<SceneNode>> vect;
    addNodeAndChildrens(parent->get(), layer, vect);
    return vect;
}

void SceneData::addNodeAndChildrens(SceneNode * node, SceneLayer & layer, std::vector<std::unique_ptr<SceneNode>> & vect)
{
    auto index = layer.indexOf(node);
    if(index >= layer.size())
            return;
    vect.push_back(std::move(layer[index]));
    layer[index].reset();

    for(auto & n : node->childrens)
        addNodeAndChildrens(n, layer, vect);
}
