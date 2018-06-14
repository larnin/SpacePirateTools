#include "scenedata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

SceneData::SceneData(const QString & fileName)
{
    load(fileName);
}

void SceneData::save(const QString & fileName) const
{
    QJsonObject obj;

    obj.insert("r", (int)backgroundColor.r);
    obj.insert("g", (int)backgroundColor.g);
    obj.insert("b", (int)backgroundColor.b);

    QJsonArray layers;
    for(const auto & l : *this)
        layers.append(l.save());
    obj.insert("layers", layers);

    QFile file(fileName);
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

    for(const auto & l : obj["layers"].toArray())
        push_back(SceneLayer(l.toObject()));
}
