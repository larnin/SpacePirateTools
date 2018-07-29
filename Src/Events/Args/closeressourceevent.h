#ifndef CLOSERESSOURCEEVENT_H
#define CLOSERESSOURCEEVENT_H

#include "ProjectInfos/assettype.h"
#include <QString>

struct CloseRessourceEvent
{
    AssetType assetType;
    QString ressourceDirName;
};

#endif // CLOSERESSOURCEEVENT_H
