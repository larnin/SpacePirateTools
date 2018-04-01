#ifndef BRUSHRANDOM_H
#define BRUSHRANDOM_H

#include "brushbase.h"
#include "Tileset/tilecollider.h"
#include <vector>

struct TileRandomInfo
{
    unsigned int id;
    float probability;
};

class BrushRandom : public BrushBase, private std::vector<TileRandomInfo>
{
public:
    BrushRandom(const QJsonObject & obj, const QString & _name);
    BrushRandom(const QString & _name);

    using std::vector<TileRandomInfo>::push_back;
    using std::vector<TileRandomInfo>::pop_back;
    using std::vector<TileRandomInfo>::begin;
    using std::vector<TileRandomInfo>::end;
    using std::vector<TileRandomInfo>::front;
    using std::vector<TileRandomInfo>::back;
    using std::vector<TileRandomInfo>::insert;
    using std::vector<TileRandomInfo>::erase;
    using std::vector<TileRandomInfo>::emplace_back;
    using std::vector<TileRandomInfo>::clear;
    using std::vector<TileRandomInfo>::operator [];
    using std::vector<TileRandomInfo>::size;
    using std::vector<TileRandomInfo>::empty;

    TileCollider collider;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // BRUSHRANDOM_H
