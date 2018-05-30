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
    load(obj);

    if(empty() || (*this)[0]->values.empty() || (*this)[0]->values[0]->type() != ValueType::Transform)
        insert(begin(), createDefaultTransform());
    checkObjectIntegrity();
}

ObjectData::ObjectData(const QJsonObject & obj)
{
    load(obj);

    if(empty() || (*this)[0]->values.empty() || (*this)[0]->values[0]->type() != ValueType::Transform)
        insert(begin(), createDefaultTransform());
    checkObjectIntegrity();
}

void ObjectData::save(const QString & fileName) const
{
    QFile file(fileName);
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

        QJsonArray values;
        for(const auto & v : p->values)
            values.append(v->save());
        pObj.insert("values", values);
        pObj.insert("iv", static_cast<int>(p->inspectorVisibility));
        pObj.insert("sv", static_cast<int>(p->sceneVisibility));
        pObj.insert("fixed", p->fixedSize ? 1 : 0);
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
        for(const auto & v : propertiesObj->toArray())
        {
            auto p = v.toObject();

            auto prop = std::make_unique<ObjectProperty>();
            prop->name = p["name"].toString();
            auto values = p["values"].toArray();
            for(const auto & v : values)
                prop->values.push_back(ObjectValueBase::loadValue(v.toObject()));
            prop->inspectorVisibility = static_cast<InspectorVisibility>(p["iv"].toInt());
            prop->sceneVisibility = static_cast<SceneVisibility>(p["sv"].toInt());
            prop->fixedSize = p["fixed"].toInt() > 0;
            push_back(std::move(prop));
        }
    }
}

ObjectValueTransform & ObjectData::transform()
{
    assert(!empty());
    assert(!(*this)[0]->values.empty());
    assert((*this)[0]->values[0]->type() == ValueType::Transform);

    return *dynamic_cast<ObjectValueTransform*>((*this)[0]->values[0].get());
}

std::unique_ptr<ObjectProperty> ObjectData::createDefaultTransform()
{
    auto property = std::make_unique<ObjectProperty>();
    property->name = "Transform";
    property->inspectorVisibility = InspectorVisibility::Visible;
    property->sceneVisibility = SceneVisibility::All;
    property->fixedSize = true;
    property->values.push_back(ObjectValueBase::createValue(ValueType::Transform));
    return std::move(property);
}

void ObjectData::checkObjectIntegrity()
{
    erase(std::remove_if(begin(), end(), [](const auto & p){return p->values.empty();}), end());

    if(empty() || (*this)[0]->values.empty() || (*this)[0]->values[0]->type() != ValueType::Transform)
        insert(begin(), createDefaultTransform());
}
