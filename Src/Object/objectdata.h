#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "objectproperty.h"
#include <QString>
#include <memory>
#include <vector>

class ObjectData : private std::vector<std::unique_ptr<ObjectProperty>>
{
public:
    ObjectData() = default;
    ObjectData(const QString & fileName);

    using std::vector<std::unique_ptr<ObjectProperty>>::push_back;
    using std::vector<std::unique_ptr<ObjectProperty>>::pop_back;
    using std::vector<std::unique_ptr<ObjectProperty>>::begin;
    using std::vector<std::unique_ptr<ObjectProperty>>::end;
    using std::vector<std::unique_ptr<ObjectProperty>>::front;
    using std::vector<std::unique_ptr<ObjectProperty>>::back;
    using std::vector<std::unique_ptr<ObjectProperty>>::insert;
    using std::vector<std::unique_ptr<ObjectProperty>>::erase;
    using std::vector<std::unique_ptr<ObjectProperty>>::emplace_back;
    using std::vector<std::unique_ptr<ObjectProperty>>::clear;
    using std::vector<std::unique_ptr<ObjectProperty>>::operator [];
    using std::vector<std::unique_ptr<ObjectProperty>>::size;
    using std::vector<std::unique_ptr<ObjectProperty>>::empty;

    void save(const QString & fileName) const;

private:
    void load(const QString & fileName);

};

#endif // OBJECTDATA_H
