#ifndef OBJECTVALUETRANSFORM_H
#define OBJECTVALUETRANSFORM_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueTransform : public ObjectValueBase
{
public:
    ObjectValueTransform();
    ObjectValueTransform(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

protected:
    void onSave(QJsonObject & obj) const override;
};
#endif // OBJECTVALUETRANSFORM_H
