#include "layerbase.h"
#include "objectslayer.h"
#include "tilesetlayer.h"
#include <cassert>

QString layerTypeToString(LayerType type)
{
    switch(type)
    {
    case LayerType::Objects:
        return "Objects";
    case LayerType::Tilemap:
        return "Tilemap";
    }
    return "";
}

LayerBase::LayerBase(LayerType type, const QString & _name)
    : name(_name)
    , hidden(false)
    , showGizmos(false)
    , m_type(type)
{

}

QJsonObject LayerBase::save() const
{
    QJsonObject obj;
    obj.insert("name", name);
    obj.insert("type", static_cast<int>(m_type));

    onSave(obj);

    return obj;
}

std::unique_ptr<LayerBase> LayerBase::loadLayer(const QJsonObject & obj)
{
    auto name = obj["name"].toString();
    auto type = static_cast<LayerType>(obj["type"].toInt());

    switch(type)
    {
    case LayerType::Objects:
        return std::make_unique<ObjectsLayer>(name, obj);
    case LayerType::Tilemap:
        return std::make_unique<TilesetLayer>(name, obj);
    }

    assert(false);
    return {};
}

std::unique_ptr<LayerBase> LayerBase::createLayer(LayerType type, const QString & name, const sf::Vector2u & size)
{
    switch(type)
    {
    case LayerType::Objects:
        return std::make_unique<ObjectsLayer>(name, size);
    case LayerType::Tilemap:
        return std::make_unique<TilesetLayer>(name, size);
    }

    assert(false);
    return {};
}
