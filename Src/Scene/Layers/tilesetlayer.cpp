#include "tilesetlayer.h"

TilesetLayer::TilesetLayer(const QString &name, const QJsonObject &obj)
    : LayerBase(LayerType::Tilemap, name)
{

}


TilesetLayer::TilesetLayer(const QString & name, const sf::Vector2u &size)
    : LayerBase(LayerType::Tilemap, name)
{

}

void TilesetLayer::onSave(QJsonObject & obj) const
{

}

void TilesetLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void TilesetLayer::setSize(const sf::Vector2u & size)
{

}
