#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "objectproperty.h"
#include <QString>
#include <memory>
#include <vector>

class ObjectData : private std::vector<ObjectProperty>
{
public:
    ObjectData() = default;
    ObjectData(const QString & fileName);

    using std::vector<ObjectProperty>::push_back;
    using std::vector<ObjectProperty>::pop_back;
    using std::vector<ObjectProperty>::begin;
    using std::vector<ObjectProperty>::end;
    using std::vector<ObjectProperty>::front;
    using std::vector<ObjectProperty>::back;
    using std::vector<ObjectProperty>::insert;
    using std::vector<ObjectProperty>::erase;
    using std::vector<ObjectProperty>::emplace_back;
    using std::vector<ObjectProperty>::clear;
    using std::vector<ObjectProperty>::operator [];
    using std::vector<ObjectProperty>::size;
    using std::vector<ObjectProperty>::empty;

    void save(const QString & fileName) const;

private:
    void load(const QString & fileName);

};

#endif // OBJECTDATA_H
