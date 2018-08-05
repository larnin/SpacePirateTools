#include "rendersystem.h"
#include "maperase.h"

RenderSystem::RenderSystem(SceneData &data)
    : m_data(data)
{

}

void RenderSystem::update()
{
    updateLayers();

    for(auto & l : m_renderables)
    {
        updateLayer(l.first, l.second);
        for(auto & n : l.second)
            updateNode(n.first, n.second);
    }
}

void RenderSystem::draw(sf::RenderTarget &target) const
{
    for(const auto & l : m_renderables)
    {
        if(l.first->hidden)
            continue;
        for(const auto & n : l.second)
            for(const auto & v : n.second)
                v->draw(target);
    }
}
void RenderSystem::drawGizmos(sf::RenderTarget &target) const
{
    for(const auto & l : m_renderables)
    {
        if(!l.first->showGizmos)
            continue;
        for(const auto & n : l.second)
            for(const auto & v : n.second)
                v->drawGizmos(target);
    }
}

void RenderSystem::updateLayers()
{
    erase_if(m_renderables, [this](const auto & l)
    {
        auto layer = l.first;
        return std::find_if(m_data.begin(), m_data.end(), [layer](const auto & v) {return v.get() == layer;}) == m_data.end();
    });

    for(const auto & d : m_data)if(std::find_if(m_renderables.begin(), m_renderables.end(), [&d](const auto & l){return l.first == d.get();}) == m_renderables.end())
            m_renderables.emplace(d.get(), std::unordered_map<SceneNode*, std::vector<std::unique_ptr<ValueRendererBase>>>());
}

void RenderSystem::updateLayer(SceneLayer* layer, std::unordered_map<SceneNode*, std::vector<std::unique_ptr<ValueRendererBase>>> & data)
{
    erase_if(data, [layer](const auto & n)
    {
        auto node = n.first;
        return std::find_if(layer->begin(), layer->end(), [node](const auto & v){return v.get() == node;}) == layer->end();
    });

    for(const auto & d : *layer)
        if(std::find_if(data.begin(), data.end(), [&d](const auto & n){return n.first == d.get();}) == data.end())
            data.emplace(d.get(), std::vector<std::unique_ptr<ValueRendererBase>>());
}

void RenderSystem::updateNode(SceneNode* node, std::vector<std::unique_ptr<ValueRendererBase>> & data)
{
    erase_if(data, [node](const auto & vr)
    {
        auto v = vr->getValue();
        for(const auto & p : node->object)
        {
            bool found = std::find_if(p->values.begin(), p->values.end(), [v](const auto & value){return value.get() == v;}) != p->values.end();
            if(found)
                return false;
        }
        return true;
    });

    for(const auto & p : node->object)
        for(const auto & v : p->values)
            if(std::find_if(data.begin(), data.end(), [&v](const auto & d){return d->getValue() == v.get();}) == data.end())
                data.push_back(v->renderer(node));
}
