#include "objectvalueasset.h"
#include "UI/Object/Value/assetvaluewidget.h"
#include <cassert>

ObjectValueAsset::ObjectValueAsset(AssetType type)
    : ObjectValueBase(assetToValueType(type))
    , m_type(type)
{

}

ObjectValueAsset::ObjectValueAsset(const QJsonObject & obj)
    : ObjectValueAsset(static_cast<AssetType>(obj["asset"].toInt()))
{
    assetName = obj["name"].toString();
}

QString ObjectValueAsset::toString() const
{
    return "Asset : " + assetName;
}

QWidget* ObjectValueAsset::createUi()
{
    return new AssetValueWidget(*this);
}

void ObjectValueAsset::onSave(QJsonObject & obj) const
{
    obj.insert("asset", static_cast<int>(m_type));
    obj.insert("name", assetName);
}

ValueType ObjectValueAsset::assetToValueType(AssetType type)
{
    switch(type)
    {
    case AssetType::Animation:
        return ValueType::Animation;
    case AssetType::Animator:
        return ValueType::Animator;
    case AssetType::Image:
        return ValueType::Texture;
    case AssetType::Object:
        return ValueType::Object;
    case AssetType::Scene:
        return ValueType::Scene;
    default:
        break;
    }

    assert(false);
    return ValueType::Max;
}

AssetType ObjectValueAsset::valueToAssetType(ValueType type)
{
    switch(type)
    {
    case ValueType::Animation:
        return AssetType::Animation;
    case ValueType::Animator:
        return AssetType::Animator;
    case ValueType::Texture:
        return AssetType::Image;
    case ValueType::Object:
        return AssetType::Object;
    case ValueType::Scene:
        return AssetType::Scene;
    default:
        break;
    }

    assert(false);
    return AssetType::Max;
}
