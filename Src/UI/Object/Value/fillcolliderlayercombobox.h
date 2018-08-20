#ifndef FILLCOLLIDERLAYERCOMBOBOX_H
#define FILLCOLLIDERLAYERCOMBOBOX_H

#include "ProjectInfos/projectinfos.h"
#include <QComboBox>

inline void fillColliderLayerComboBox(QComboBox * box)
{
    box->clear();

    for(const auto & v : ProjectInfos::instance().options().colliderLayers)
        box->addItem(v.name);
}

#endif // FILLCOLLIDERLAYERCOMBOBOX_H
