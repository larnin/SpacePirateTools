#ifndef TILESETLAYER_H
#define TILESETLAYER_H

#include "layerbase.h"
#include <QJsonObject>

class TilesetLayer : public LayerBase
{
public:
    TilesetLayer(const QString & name, const QJsonObject & obj);
    TilesetLayer(const QString & name, const sf::Vector2u &size);

    void setSize(const sf::Vector2u & size) override;

protected:
    void onSave(QJsonObject & obj) const override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // TILESETLAYER_H
