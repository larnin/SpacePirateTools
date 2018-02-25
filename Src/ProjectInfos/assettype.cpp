#include "assettype.h"
#include <cassert>

QString assetTypeToString(AssetType type)
{
    switch(type)
    {
    case AssetType::Animation:
        return "Animation";
    case AssetType::Animator:
        return "Animator";
    case AssetType::Image:
        return "Image";
    case AssetType::Scene:
        return "Scene";
    case AssetType::Tileset:
        return "Tileset";
    default:
        break;
    }

    assert(false && "Unknow assetType");
    return "";
}

QString assetTypeExtension(AssetType type)
{
    switch(type)
    {
    case AssetType::Animation:
        return "anim";
    case AssetType::Animator:
        return "ator";
    case AssetType::Image:
        return "png";
    case AssetType::Scene:
        return "scene";
    case AssetType::Tileset:
        return "tile";
    default:
        break;
    }

    assert(false && "Unknow assetType");
    return "";
}

AssetType stringToAssetType(const QString & s)
{
    auto str = s.toLower().trimmed();
    for(unsigned int i(0) ; i < static_cast<unsigned int>(AssetType::Max) ; i++)
        if(str == assetTypeToString(static_cast<AssetType>(i)))
            return static_cast<AssetType>(i);
    return AssetType::Unknow;
}
