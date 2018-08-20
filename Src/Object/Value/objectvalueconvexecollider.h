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
    ObjectValueConvexeCollider(const ObjectValueConvexeCollider &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueConvexeCollider>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    std::vector<sf::Vector2f> points;
    unsigned int collisionLayer;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECONVEXECOLLIDER_H
