#ifndef OBJECTVALUECIRCLECOLLIDER_H
#define OBJECTVALUECIRCLECOLLIDER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueCircleCollider : public ObjectValueBase
{
public:
    ObjectValueCircleCollider();
    ObjectValueCircleCollider(const QJsonObject & obj);
    ObjectValueCircleCollider(const ObjectValueCircleCollider &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueCircleCollider>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f center;
    float size;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECIRCLECOLLIDER_H
