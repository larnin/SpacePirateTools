#ifndef OPENRESSOURCEEVENT_H
#define OPENRESSOURCEEVENT_H

#include "ProjectInfos/assettype.h"
#include <QString>

struct OpenRessourceEvent
{
    AssetType assetType;
    QString ressourceDirName;
};

#endif // OPENRESSOURCEEVENT_H
