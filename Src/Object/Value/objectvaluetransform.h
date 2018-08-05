#ifndef OBJECTVALUETRANSFORM_H
#define OBJECTVALUETRANSFORM_H

#include "objectvaluebase.h"
#include <SFML/Graphics/Transform.hpp>
#include <SFML/System/Vector2.hpp>

class ObjectValueTransform : public ObjectValueBase
{
public:
    ObjectValueTransform();
    ObjectValueTransform(const QJsonObject & obj);
    ObjectValueTransform(const ObjectValueTransform &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueTransform>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::Transform getSFMLLocalTransform() const;

    sf::Vector2f position;
    sf::Vector2f scale;
    float rotation;

protected:
    void onSave(QJsonObject & obj) const override;
};
#endif // OBJECTVALUETRANSFORM_H
