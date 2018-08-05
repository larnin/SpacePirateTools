#ifndef OBJECTVALUESPRITERENDERER_H
#define OBJECTVALUESPRITERENDERER_H

#include "objectvaluebase.h"
#include <SFML/Graphics/Rect.hpp>

class ObjectValueSpriteRenderer : public ObjectValueBase
{
public:
    ObjectValueSpriteRenderer();
    ObjectValueSpriteRenderer(const QJsonObject & obj);
    ObjectValueSpriteRenderer(const ObjectValueSpriteRenderer &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueSpriteRenderer>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::IntRect textureRect;
    sf::Vector2f offset;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUESPRITERENDERER_H
