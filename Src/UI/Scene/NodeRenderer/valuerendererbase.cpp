#include "valuerendererbase.h"

ValueRendererBase::ValueRendererBase(SceneNode *node, ObjectValueBase *value)
    : m_node(node)
    , m_value(value)
{

}

sf::Transform ValueRendererBase::getTransform() const
{
    return m_node->getSFMLLocalTransform();
}
