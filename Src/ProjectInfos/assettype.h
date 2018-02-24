#ifndef ASSETTYPE_H
#define ASSETTYPE_H

#include <QString>

enum class AssetType
{
    Image,
    Tileset,
    Animation,
    Animator,
    Scene,
    Max = Scene,
};

QString assetTypeToString(AssetType type);
QString assetTypeExtension(AssetType type);

#endif // ASSETTYPE_H
