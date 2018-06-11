#ifndef SCENEDATA_H
#define SCENEDATA_H

#include "scenelayer.h"
#include <QString>
#include <vector>

class SceneData : private std::vector<SceneLayer>
{
public:
    SceneData() = default;
    SceneData(const QString & fileName);
    using std::vector<SceneLayer>::push_back;
    using std::vector<SceneLayer>::pop_back;
    using std::vector<SceneLayer>::begin;
    using std::vector<SceneLayer>::end;
    using std::vector<SceneLayer>::front;
    using std::vector<SceneLayer>::back;
    using std::vector<SceneLayer>::insert;
    using std::vector<SceneLayer>::erase;
    using std::vector<SceneLayer>::emplace_back;
    using std::vector<SceneLayer>::clear;
    using std::vector<SceneLayer>::operator [];
    using std::vector<SceneLayer>::size;
    using std::vector<SceneLayer>::empty;

    void save(const QString & fileName) const;

private:
    void load(const QString & fileName);
};

#endif // SCENEDATA_H
