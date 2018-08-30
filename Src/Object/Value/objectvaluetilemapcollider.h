#ifndef OBJECTVALUETILEMAPCOLLIDER_H
#define OBJECTVALUETILEMAPCOLLIDER_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>
#include <QString>

class ObjectValueTilemapCollider : public ObjectValueBase
{
public:
    ObjectValueTilemapCollider();
    ObjectValueTilemapCollider(const QJsonObject & obj);
    ObjectValueTilemapCollider(const ObjectValueTilemapCollider &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueTilemapCollider>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    QString tilemapName;
    unsigned int tileSize;
    sf::Vector2f offset;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUETILEMAPCOLLIDER_H
