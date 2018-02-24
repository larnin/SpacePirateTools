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
    }

    assert(false && "Unknow assetType");
    return "";
}
