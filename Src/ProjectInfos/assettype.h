#ifndef ASSETTYPE_H
#define ASSETTYPE_H

#include <QString>

enum class AssetType
{
    Image,
    Tileset,
    Tilemap,
    Animation,
    Animator,
    Scene,
    Object,
    Max = Object,
    Unknow = Max+1,
};

QString assetTypeToString(AssetType type);
QString assetTypeExtension(AssetType type);
AssetType stringToAssetType(const QString & s);
AssetType extensionToAssetType(const QString & s);
bool assetCanBeCreated(AssetType type);
bool assetCanBeOpened(AssetType type);

#endif // ASSETTYPE_H
