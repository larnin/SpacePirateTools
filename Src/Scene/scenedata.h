#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "scenelayer.h"
#include <SFML/Graphics/Color.hpp>
#include <QString>
#include <vector>
#include <memory>

class SceneData : private std::vector<std::unique_ptr<SceneLayer>>
{
public:
    SceneData();
    SceneData(const QString & fileName);
    SceneData(const SceneData &) = delete;
    SceneData & operator=(const SceneData &) = delete;
    ~SceneData();

    using std::vector<std::unique_ptr<SceneLayer>>::push_back;
    using std::vector<std::unique_ptr<SceneLayer>>::pop_back;
    using std::vector<std::unique_ptr<SceneLayer>>::begin;
    using std::vector<std::unique_ptr<SceneLayer>>::end;
    using std::vector<std::unique_ptr<SceneLayer>>::front;
    using std::vector<std::unique_ptr<SceneLayer>>::back;
    using std::vector<std::unique_ptr<SceneLayer>>::insert;
    using std::vector<std::unique_ptr<SceneLayer>>::erase;
    using std::vector<std::unique_ptr<SceneLayer>>::emplace_back;
    using std::vector<std::unique_ptr<SceneLayer>>::clear;
    using std::vector<std::unique_ptr<SceneLayer>>::operator [];
    using std::vector<std::unique_ptr<SceneLayer>>::size;
    using std::vector<std::unique_ptr<SceneLayer>>::empty;

    void save(const QString & fileName) const;

    sf::Color backgroundColor;

    std::vector<std::unique_ptr<SceneNode>> asPrefab();

    static SceneData* currentScene(){return m_currentScene;}

private:
    void load(const QString & fileName);

    void addNodeAndChildrens(SceneNode * node, SceneLayer & layer, std::vector<std::unique_ptr<SceneNode>> & vect);

    static SceneData * m_currentScene;
};

#endif // SCENEDATA_H
