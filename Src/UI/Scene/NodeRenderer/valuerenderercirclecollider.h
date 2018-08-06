#ifndef VALUERENDERERCIRCLECOLLIDER_H
#define VALUERENDERERCIRCLECOLLIDER_H

#include "valuerendererbase.h"
#include "Object/Value/objectvaluecirclecollider.h"

class ValueRendererCircleCollider : public ValueRendererBase
{
public:
    ValueRendererCircleCollider(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &) const override;
    void drawGizmos(sf::RenderTarget & target) const override;
    void update() override;

private:
    ObjectValueCircleCollider * m_collider;
};

#endif // VALUERENDERERCIRCLECOLLIDER_H
