#ifndef OBJECTVALUEVECTOR2F_H
#define OBJECTVALUEVECTOR2F_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueVector2f : public ObjectValueBase
{
public:
    ObjectValueVector2f();
    ObjectValueVector2f(const QJsonObject & obj);
    ObjectValueVector2f(const ObjectValueVector2f &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueVector2f>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEVECTOR2F_H
