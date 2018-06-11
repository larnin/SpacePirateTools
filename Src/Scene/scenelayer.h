#ifndef SCENELAYER_H
#define SCENELAYER_H

#include "scenenode.h"
#include <QString>
#include <QJsonObject>
#include <vector>

class SceneLayer : private std::vector<SceneNode>
{
public:
    SceneLayer() = default;
    SceneLayer(const QJsonObject & obj);
    using std::vector<SceneNode>::push_back;
    using std::vector<SceneNode>::pop_back;
    using std::vector<SceneNode>::begin;
    using std::vector<SceneNode>::end;
    using std::vector<SceneNode>::front;
    using std::vector<SceneNode>::back;
    using std::vector<SceneNode>::insert;
    using std::vector<SceneNode>::erase;
    using std::vector<SceneNode>::emplace_back;
    using std::vector<SceneNode>::clear;
    using std::vector<SceneNode>::operator [];
    using std::vector<SceneNode>::size;
    using std::vector<SceneNode>::empty;

    QJsonObject save() const;

private:
    void load(const QJsonObject & obj);
};

#endif // SCENELAYER_H
