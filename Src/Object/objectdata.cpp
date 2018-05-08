#include "objectdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

ObjectData::ObjectData(const QString & fileName)
{
    load(fileName);
}

void ObjectData::save(const QString & fileName) const
{
    QJsonObject obj;

    QJsonArray properties;
    for(const auto & p : *this)
    {
        QJsonObject pObj;
        pObj.insert("name", p.name);
        //add value
        pObj.insert("iv", static_cast<int>(p.inspectorVisibility));
        pObj.insert("sv", static_cast<int>(p.sceneVisibility));
        properties.append(pObj);
    }
    obj.insert("properties", properties);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void ObjectData::load(const QString & fileName)
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

    auto propertiesObj = obj.find("properties");
    if(propertiesObj != obj.end() && propertiesObj->isArray())
    {
        for(const auto & v : propertiesObj->toArray())
        {
            auto p = v.toObject();

            ObjectProperty prop;
            prop.name = p["name"].toString();
            prop.inspectorVisibility = static_cast<InspectorVisibility>(p["iv"].toInt());
            prop.sceneVisibility = static_cast<SceneVisibility>(p["sv"].toInt());
            push_back(std::move(prop));
        }
    }
}
