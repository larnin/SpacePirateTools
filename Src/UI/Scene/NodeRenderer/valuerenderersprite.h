#ifndef VALUERENDERERSPRITE_H
#define VALUERENDERERSPRITE_H

#include "valuerendererbase.h"
#include "ressource.h"
#include "Object/Value/objectvaluespriterenderer.h"
#include <QString>

class ValueRendererSprite : public ValueRendererBase
{
public:
    ValueRendererSprite(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &target) const override;
    void drawGizmos(sf::RenderTarget &) const override;
    void update() override;

private:
    Texture m_texture;
    ObjectValueSpriteRenderer* m_spriteRenderer;
    QString m_textureName;
};

#endif // VALUERENDERERSPRITE_H
