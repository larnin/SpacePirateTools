#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "Layers/layerbase.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <QString>
#include <vector>
#include <memory>

class SceneData
{
public:
    SceneData() = default;
    SceneData(const QString & fileName);
    void save(const QString & fileName) const;

    inline sf::Vector2u getSize() const { return m_size; }
    void setSize(const sf::Vector2u & size);

    inline unsigned int layerCount() const {return m_layers.size();}
    inline LayerBase& layer(unsigned int index) { return *m_layers[index];}
    inline const LayerBase& layer(unsigned int index) const {return *m_layers[index];}

    void addLayer(LayerType type, const QString &name, const sf::Vector2u &size);
    void delLayer(unsigned int index);
    inline void swapLayers(unsigned int index1, unsigned int index2){std::swap(m_layers[index1], m_layers[index2]);}

    sf::Color color;

private:
    void load(const QString & fileName);
    sf::Vector2u m_size;
    std::vector<std::unique_ptr<LayerBase>> m_layers;
};

#endif // SCENEDATA_H
