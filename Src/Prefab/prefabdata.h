#ifndef PREFABDATA_H
#define PREFABDATA_H

#include "Scene/scenenode.h"
#include <QString>
#include <QJsonArray>
#include <vector>
#include <memory>

class PrefabData : private std::vector<std::unique_ptr<SceneNode>>
{
public:
    PrefabData();
    PrefabData(const QString & fileName);

    using std::vector<std::unique_ptr<SceneNode>>::push_back;
    using std::vector<std::unique_ptr<SceneNode>>::pop_back;
    using std::vector<std::unique_ptr<SceneNode>>::begin;
    using std::vector<std::unique_ptr<SceneNode>>::end;
    using std::vector<std::unique_ptr<SceneNode>>::front;
    using std::vector<std::unique_ptr<SceneNode>>::back;
    using std::vector<std::unique_ptr<SceneNode>>::insert;
    using std::vector<std::unique_ptr<SceneNode>>::erase;
    using std::vector<std::unique_ptr<SceneNode>>::emplace_back;
    using std::vector<std::unique_ptr<SceneNode>>::clear;
    using std::vector<std::unique_ptr<SceneNode>>::operator [];
    using std::vector<std::unique_ptr<SceneNode>>::size;
    using std::vector<std::unique_ptr<SceneNode>>::empty;

    void save(const QString & fileName) const;

private:
    void load(const QString &fileName);
    void loadNodesHierarchy(const QJsonArray & hierarchy);
    QJsonArray saveNodesHierarchy() const;
};

#endif // PREFABDATA_H
