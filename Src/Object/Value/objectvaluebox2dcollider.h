#ifndef OBJECTVALUEBOX2DCOLLIDER_H
#define OBJECTVALUEBOX2DCOLLIDER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueBox2DCollider : public ObjectValueBase
{
public:
    ObjectValueBox2DCollider();
    ObjectValueBox2DCollider(const QJsonObject & obj);
    ObjectValueBox2DCollider(const ObjectValueBox2DCollider &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueBox2DCollider>(*this); }

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f center;
    sf::Vector2f size;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEBOX2DCOLLIDER_H
