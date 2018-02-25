#ifndef OPENRESSOURCEEVENT_H
#define OPENRESSOURCEEVENT_H

#include <QString>
#include "ProjectInfos/assettype.h"

struct OpenRessourceEvent
{
    AssetType assetType;
    QString ressourceDirName;
};

#endif // OPENRESSOURCEEVENT_H
