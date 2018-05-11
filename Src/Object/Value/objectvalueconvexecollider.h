#ifndef OBJECTVALUECONVEXECOLLIDER_H
#define OBJECTVALUECONVEXECOLLIDER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

class ObjectValueConvexeCollider : public ObjectValueBase
{
public:
    ObjectValueConvexeCollider();
    ObjectValueConvexeCollider(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    std::vector<sf::Vector2f> points;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECONVEXECOLLIDER_H
