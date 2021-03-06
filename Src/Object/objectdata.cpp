#include "objectdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>
#include <cassert>

ObjectData::ObjectData()
{
    push_back(createDefaultTransform());
    checkObjectIntegrity();
}

ObjectData::ObjectData(const QString & fileName)
{
    QFile file(fileName);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        checkObjectIntegrity();
        return;
    }

    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &error));
    file.close();
    if(error.error != QJsonParseError::NoError || !doc.isObject())
    {
        checkObjectIntegrity();
        return;
    }

    QJsonObject obj(doc.object());
    load(obj);

    checkObjectIntegrity();
}

ObjectData::ObjectData(const QJsonObject & obj)
{
    load(obj);

    checkObjectIntegrity();
}


ObjectData::ObjectData(const ObjectData & data)
    : std::vector<std::unique_ptr<ObjectProperty>>()
{
    for(const auto & p : data)
        push_back(p->clone());
}

void ObjectData::save(const QString & fileName) const
{
    QFile file(fileName);
    if(!file.exists())
        return;
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(save()).toJson(QJsonDocument::Compact));
    file.close();
}

QJsonObject ObjectData::save() const
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

    return obj;
}

void ObjectData::load(const QJsonObject &obj)
{
    clear();

    auto propertiesObj = obj.find("properties");
    if(propertiesObj != obj.end() && propertiesObj->isArray())
    {
        for(const auto v : propertiesObj->toArray())
        {
            auto p = v.toObject();

            auto prop = std::make_unique<ObjectProperty>();
            prop->name = p["name"].toString();
            auto value = p["value"].toObject();
            prop->value = ObjectValueBase::loadValue(value);
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

ObjectValueTransform const & ObjectData::transform() const
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
    return property;
}

void ObjectData::checkObjectIntegrity()
{
    if(empty() || (*this)[0]->value->type() != ValueType::Transform)
        insert(begin(), createDefaultTransform());
}


ObjectValueBase* ObjectData::getFirstValueOfType(ValueType type)
{
    for(const auto & p : *this)
        if(p->value->type() == type)
            return p->value.get();

    return nullptr;
}

std::vector<ObjectValueBase*> ObjectData::getAllValueOfType(ValueType type)
{
    std::vector<ObjectValueBase*> properties;

    for(const auto & p : *this)
        if(p->value->type() == type)
            properties.push_back(p->value.get());
    return properties;
}
