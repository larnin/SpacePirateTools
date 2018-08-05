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
    auto assets = getNode()->object.getAllValueOfType<ObjectValueAsset>();
    if(assets.empty())
    {
        m_texture.clear();
        m_textureName.clear();
        return;
    }

    for(const auto & a : assets)
    {
        if(a->getAssetType() != AssetType::Image)
            continue;

        if(a->assetName != m_textureName)
        {
            m_textureName = a->assetName;
            m_texture.load(ProjectInfos::instance().fullFileName(m_textureName, AssetType::Image).toStdString());
        }

        return;
    }

    m_texture.clear();
    m_textureName.clear();
}
