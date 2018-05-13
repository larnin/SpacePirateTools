#ifndef OBJECTVALUESPRITERENDERER_H
#define OBJECTVALUESPRITERENDERER_H

#include "objectvaluebase.h"
#include "SFML/Graphics/Rect.hpp"

class ObjectValueSpriteRenderer : public ObjectValueBase
{
public:
    ObjectValueSpriteRenderer();
    ObjectValueSpriteRenderer(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::IntRect textureRect;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUESPRITERENDERER_H
