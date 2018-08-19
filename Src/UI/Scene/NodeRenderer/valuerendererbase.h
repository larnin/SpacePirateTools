#ifndef VALUERENDERERBASE_H
#define VALUERENDERERBASE_H

#include "Scene/scenenode.h"
#include "Object/Value/objectvaluebase.h"
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Transform.hpp>

class ValueRendererBase
{
public:
    ValueRendererBase(SceneNode * node, ObjectValueBase * value);
    virtual ~ValueRendererBase() = default;

    virtual void draw(sf::RenderTarget & target) const = 0;
    virtual void drawGizmos(sf::RenderTarget & target) const = 0;
    virtual void update() = 0;

    SceneNode* getNode() const {return m_node;}
    ObjectValueBase* getValue() const {return m_value;}

    sf::Transform getTransform() const;

protected:
    SceneNode * m_node;
    ObjectValueBase * m_value;
};

#endif // VALUERENDERERBASE_H
