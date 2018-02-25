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
    Unknow = Max+1,
};

QString assetTypeToString(AssetType type);
QString assetTypeExtension(AssetType type);
AssetType stringToAssetType(const QString & s);

#endif // ASSETTYPE_H
