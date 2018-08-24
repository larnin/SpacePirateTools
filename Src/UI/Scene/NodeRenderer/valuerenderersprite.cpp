#include "valuerenderersprite.h"
#include "Object/Value/objectvalueasset.h"
#include "ProjectInfos/projectinfos.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/RenderStates.hpp>

ValueRendererSprite::ValueRendererSprite(SceneNode * node, ObjectValueBase * value)
    : ValueRendererBase(node, value)
    , m_spriteRenderer(dynamic_cast<ObjectValueSpriteRenderer*>(value))
{

}


void ValueRendererSprite::draw(sf::RenderTarget & target) const
{
    if(m_textureName.isEmpty() || !m_texture.isValid())
        return;

    sf::Sprite s(*m_texture, m_spriteRenderer->textureRect);
    s.setPosition(m_spriteRenderer->offset);
    target.draw(s, getTransform());
}

void ValueRendererSprite::drawGizmos(sf::RenderTarget &) const
{

}

void ValueRendererSprite::update()
{
    if(m_spriteRenderer->textureName != m_textureName)
    {
        m_textureName = m_spriteRenderer->textureName;
        if(m_spriteRenderer->textureName.isEmpty())
            m_texture.clear();
        else m_texture.load(ProjectInfos::instance().fullFileName(m_textureName, AssetType::Image).toStdString());
    }
}
