#ifndef VALUERENDERERBOX2DCOLLIDER_H
#define VALUERENDERERBOX2DCOLLIDER_H

#include "valuerendererbase.h"
#include "Object/Value/objectvaluebox2dcollider.h"

class ValueRendererBox2DCollider : public ValueRendererBase
{
public:
    ValueRendererBox2DCollider(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &) const override;
    void drawGizmos(sf::RenderTarget & target) const override;
    void update() override;

private:
    ObjectValueBox2DCollider * m_collider;
};

#endif // VALUERENDERERBOX2DCOLLIDER_H
