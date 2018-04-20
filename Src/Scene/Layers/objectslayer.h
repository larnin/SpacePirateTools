#ifndef OBJECTSLAYER_H
#define OBJECTSLAYER_H

#include "layerbase.h"
#include <QObject>

class ObjectsLayer : public LayerBase
{
public:
    ObjectsLayer(const QString & name, const QJsonObject & obj);
    ObjectsLayer(const QString & name, const sf::Vector2u &);

    void setSize(const sf::Vector2u & size) override;

protected:
    void onSave(QJsonObject & obj) const override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
};

#endif // OBJECTSLAYER_H
