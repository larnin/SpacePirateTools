#ifndef VALUERENDERERNONE_H
#define VALUERENDERERNONE_H

#include "valuerendererbase.h"

class ValueRendererNone : public ValueRendererBase
{
public:
    ValueRendererNone(SceneNode * node, ObjectValueBase * value)
        : ValueRendererBase(node, value){}


    void draw(sf::RenderTarget &) const override {}
    void drawGizmos(sf::RenderTarget &) const override{}
};

#endif // VALUERENDERERNONE_H
