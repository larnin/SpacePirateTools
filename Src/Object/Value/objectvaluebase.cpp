#include "objectvaluebase.h"
#include "objectvaluetransform.h"
#include <cassert>

QString valueTypeToString(ValueType type)
{
    switch(type)
    {
    case ValueType::Transform:
        return "Transform";
    case ValueType::Box2DCollider:
        return "Box2DCollider";
    case ValueType::CircleCollider:
        return "CircleCollider";
    case ValueType::ConvexeCollider:
        return "ConvexeCollider";
    case ValueType::Rigidbody:
        return "Rigidbody";
    case ValueType::Animator:
        return "Animator";
    case ValueType::Animation:
        return "Animation";
    case ValueType::Object:
        return "Object";
    case ValueType::Renderer:
        return "Renderer";
    case ValueType::Script:
        return "Script";
    case ValueType::Float:
        return "Float";
    case ValueType::Int:
        return "Int";
    case ValueType::Vector2f:
        return "Vector2f";
    case ValueType::Vector2i:
        return "Vector2i";
    case ValueType::Color:
        return "Color";
    }
    assert(false);
    return "";
}

ObjectValueBase::ObjectValueBase(ValueType type)
    : m_valueType(type)
{

}

QJsonObject ObjectValueBase::save() const
{
    QJsonObject obj;
    obj.insert("type", static_cast<int>(m_valueType));

    onSave(obj);

    return obj;
}

std::unique_ptr<ObjectValueBase> ObjectValueBase::createValue(ValueType type)
{
    switch (type)
    {
    case ValueType::Transform:
        return std::make_unique<ObjectValueTransform>();
    case ValueType::Box2DCollider:
        return {};
    case ValueType::CircleCollider:
        return {};
    case ValueType::ConvexeCollider:
        return {};
    case ValueType::Rigidbody:
        return {};
    case ValueType::Animator:
        return {};
    case ValueType::Animation:
        return {};
    case ValueType::Object:
        return {};
    case ValueType::Renderer:
        return {};
    case ValueType::Script:
        return {};
    case ValueType::Float:
        return {};
    case ValueType::Int:
        return {};
    case ValueType::Vector2f:
        return {};
    case ValueType::Vector2i:
        return {};
    case ValueType::Color:
        return {};
    }

    assert(false);
    return {};
}

std::unique_ptr<ObjectValueBase> ObjectValueBase::loadValue(const QJsonObject & obj)
{
    auto type = static_cast<ValueType>(obj["type"].toInt());

    switch (type)
    {
    case ValueType::Transform:
        return std::make_unique<ObjectValueTransform>(obj);
    case ValueType::Box2DCollider:
        return {};
    case ValueType::CircleCollider:
        return {};
    case ValueType::ConvexeCollider:
        return {};
    case ValueType::Rigidbody:
        return {};
    case ValueType::Animator:
        return {};
    case ValueType::Animation:
        return {};
    case ValueType::Object:
        return {};
    case ValueType::Renderer:
        return {};
    case ValueType::Script:
        return {};
    case ValueType::Float:
        return {};
    case ValueType::Int:
        return {};
    case ValueType::Vector2f:
        return {};
    case ValueType::Vector2i:
        return {};
    case ValueType::Color:
        return {};
    }

    assert(false);
    return {};
}
