#ifndef OBJECTVALUECIRCLECOLLIDER_H
#define OBJECTVALUECIRCLECOLLIDER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueCircleCollider : public ObjectValueBase
{
public:
    ObjectValueCircleCollider();
    ObjectValueCircleCollider(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f center;
    float size;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECIRCLECOLLIDER_H
