#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include "valuerendererbase.h"
#include "Scene/scenedata.h"
#include <memory>
#include <unordered_map>

class RenderSystem
{

public:
    RenderSystem(SceneData & data);
    void update();

    void draw(sf::RenderTarget &target) const;
    void drawGizmos(sf::RenderTarget &target) const;

private:
    void updateLayers();
    void updateLayer(SceneLayer* layer, std::unordered_map<SceneNode*, std::vector<std::unique_ptr<ValueRendererBase>>> & data);
    void updateNode(SceneNode* node, std::vector<std::unique_ptr<ValueRendererBase>> & data);

    SceneData & m_data;
    std::unordered_map<SceneLayer*, std::unordered_map<SceneNode*, std::vector<std::unique_ptr<ValueRendererBase>>>> m_renderables;
};

#endif // RENDERSYSTEM_H
