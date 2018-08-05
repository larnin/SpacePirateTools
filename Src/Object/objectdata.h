#ifndef OBJECTDATA_H
#define OBJECTDATA_H

#include "objectproperty.h"
#include "Value/objectvaluetransform.h"
#include <QString>
#include <QJsonObject>
#include <memory>
#include <vector>

class ObjectData : private std::vector<std::unique_ptr<ObjectProperty>>
{
public:
    ObjectData();
    ObjectData(const QString & fileName);
    ObjectData(const QJsonObject & obj);
    ObjectData(const ObjectData & data);
    ObjectData & operator=(const ObjectData & data) = delete;
    ObjectData(ObjectData &&) = default;
    ObjectData & operator =(ObjectData &&) = default;

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
    QJsonObject save() const;

    ObjectValueTransform & transform();
    ObjectValueTransform const & transform() const;

    template <typename T>
    T* getFirstValueOfType()
    {
        static_assert(std::is_base_of<ObjectValueBase, T>::value, "T is not an ObjectProperty");

        for(const auto & p : *this)
        {
            for(const auto & v : p->values)
            {
                auto ptr = dynamic_cast<T*>(v.get());
                if(ptr != nullptr)
                    return ptr;
            }
        }
        return nullptr;
    }

    template <typename T>
    std::vector<T*> getAllValueOfType()
    {
        static_assert(std::is_base_of<ObjectValueBase, T>::value, "T is not an ObjectProperty");

        std::vector<T*> properties;

        for(const auto & p : *this)
        {
            for(const auto & v : p->values)
            {
                auto ptr = dynamic_cast<T*>(v.get());
                if(ptr != nullptr)
                    properties.push_back(ptr);
            }
        }
        return properties;
    }

    ObjectValueBase* getFirstValueOfType(ValueType type);
    std::vector<ObjectValueBase*> getAllValueOfType(ValueType type);

private:
    void load(const QJsonObject & obj);
    std::unique_ptr<ObjectProperty> createDefaultTransform();
    void checkObjectIntegrity();
};

#endif // OBJECTDATA_H
