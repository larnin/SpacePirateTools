#include "tilesetdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

TilesetData::TilesetData(const QString &fileName)
{
    load(fileName);
}

void TilesetData::save(const QString & fileName)
{
    QJsonObject obj;

    obj.insert("image", imageName);
    obj.insert("delta", int(delta));

    QJsonArray brushArray;
    for(const auto & brush : brushs)
        brushArray.append(brush->save());

    obj.insert("brushs", brushArray);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void TilesetData::load(const QString & fileName)
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

    imageName = obj["image"].toString();
    delta = obj["delta"].toInt();

    brushs.clear();
    auto brushIt = obj.find("brushs");
    if(brushIt == obj.end() || !brushIt->isArray())
        return;

    for(const auto & b : brushIt->toArray())
    {
        auto ptr = BrushBase::loadBrush(b.toObject());
        if(!ptr)
            continue;
        brushs.push_back(std::move(ptr));
    }
}
