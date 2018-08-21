#ifndef VALUERENDERERCONVEXECOLLIDER_H
#define VALUERENDERERCONVEXECOLLIDER_H

#include "valuerendererbase.h"
#include "Object/Value/objectvalueconvexecollider.h"

class ValueRendererConvexeCollider : public ValueRendererBase
{
public:
    ValueRendererConvexeCollider(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &) const override;
    void drawGizmos(sf::RenderTarget & target) const override;
    void update() override;

private:
    ObjectValueConvexeCollider * m_collider;
};

#endif // VALUERENDERERCONVEXECOLLIDER_H
