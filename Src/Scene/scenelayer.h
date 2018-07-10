#ifndef SCENELAYER_H
#define SCENELAYER_H

#include "scenenode.h"
#include <QString>
#include <QJsonObject>
#include <vector>
#include <memory>

class SceneLayer : private std::vector<std::unique_ptr<SceneNode>>
{
public:
    SceneLayer(const QString & _name);
    SceneLayer(const QJsonObject & obj);
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

    QJsonObject save() const;
    unsigned int indexOf(SceneNode * node) const;

    QString name;
    bool hidden = false;
    bool showGizmos = false;

private:
    void load(const QJsonObject & obj);
};

#endif // SCENELAYER_H
