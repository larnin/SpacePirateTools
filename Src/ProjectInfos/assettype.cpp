#include "assettype.h"
#include "enumiterators.h"
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
    case AssetType::Object:
        return "Object";
    case AssetType::Prefab:
        return "Prefab";
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
    case AssetType::Object:
        return "object";
    case AssetType::Prefab:
        return "prfb";
    default:
        break;
    }

    assert(false && "Unknow assetType");
    return "";
}

AssetType stringToAssetType(const QString & s)
{
    auto str = s.toLower().trimmed();
    for(auto t : AssetType::Max)
        if(str == assetTypeToString(t).toLower().trimmed())
            return t;
    return AssetType::Unknow;
}

AssetType extensionToAssetType(const QString & s)
{
    auto str = s.toLower().trimmed();
    for(auto t : AssetType::Max)
        if(str == assetTypeExtension(t).toLower().trimmed())
            return t;
    return AssetType::Unknow;
}

bool assetCanBeCreated(AssetType type)
{
    switch(type)
    {
    case AssetType::Image:
        return false;
    default:
        return true;
    }
}

bool assetCanBeOpened(AssetType type)
{
    switch(type)
    {
    default:
        return true;
    }
}
