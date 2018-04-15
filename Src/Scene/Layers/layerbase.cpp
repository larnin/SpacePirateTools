#include "layerbase.h"


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
    //todo
    return {};
}

std::unique_ptr<LayerBase> LayerBase::createLayer(LayerType type, const QString & name, const sf::Vector2u & size)
{
    //todo
    return {};
}
