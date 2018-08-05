#ifndef OBJECTVALUEVECTOR2I_H
#define OBJECTVALUEVECTOR2I_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueVector2i : public ObjectValueBase
{
public:
    ObjectValueVector2i();
    ObjectValueVector2i(const QJsonObject & obj);
    ObjectValueVector2i(const ObjectValueVector2i &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueVector2i>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2i value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEVECTOR2I_H
