#include "objectdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <cassert>

ObjectData::ObjectData()
{
    push_back(createDefaultTransform());
}

ObjectData::ObjectData(const QString & fileName)
{
    load(fileName);

    if(empty() || (*this)[0]->value->type() != ValueType::Transform)
        insert(begin(), createDefaultTransform());
}

void ObjectData::save(const QString & fileName) const
{
    QJsonObject obj;

    QJsonArray properties;
    for(const auto & p : *this)
    {
        QJsonObject pObj;
        pObj.insert("name", p->name);
        pObj.insert("value", p->value->save());
        pObj.insert("iv", static_cast<int>(p->inspectorVisibility));
        pObj.insert("sv", static_cast<int>(p->sceneVisibility));
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

            auto prop = std::make_unique<ObjectProperty>();
            prop->name = p["name"].toString();
            prop->value = ObjectValueBase::loadValue(p["value"].toObject());
            prop->inspectorVisibility = static_cast<InspectorVisibility>(p["iv"].toInt());
            prop->sceneVisibility = static_cast<SceneVisibility>(p["sv"].toInt());
            push_back(std::move(prop));
        }
    }
}

ObjectValueTransform & ObjectData::transform()
{
    assert(!empty());
    assert((*this)[0]->value->type() == ValueType::Transform);

    return *dynamic_cast<ObjectValueTransform*>((*this)[0]->value.get());
}

std::unique_ptr<ObjectProperty> ObjectData::createDefaultTransform()
{
    auto property = std::make_unique<ObjectProperty>();
    property->name = "Transform";
    property->inspectorVisibility = InspectorVisibility::Visible;
    property->sceneVisibility = SceneVisibility::All;
    property->value = ObjectValueBase::createValue(ValueType::Transform);
    return std::move(property);
}
