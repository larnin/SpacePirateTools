#include "objectslayer.h"

ObjectsLayer::ObjectsLayer(const QString & name, const QJsonObject & obj)
    : LayerBase(LayerType::Objects, name)
{

}

ObjectsLayer::ObjectsLayer(const QString & name, const sf::Vector2u &)
    : LayerBase(LayerType::Objects, name)
{

}

void ObjectsLayer::onSave(QJsonObject & obj) const
{

}

void ObjectsLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void ObjectsLayer::setSize(const sf::Vector2u & size)
{

}
