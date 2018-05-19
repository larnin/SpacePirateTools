#ifndef CENTRALTILEMAPWIDGET_H
#define CENTRALTILEMAPWIDGET_H

#include "tilemapinfos.h"
#include "UI/qsfmlcanvas.h"

class CentralTilemapWidget : public QSFMLCanvas
{
    Q_OBJECT
public:
    CentralTilemapWidget(TilemapInfos * tilemap, QWidget * parent = nullptr);

protected:
    void OnUpdate() override;

private:
    TilemapInfos * m_infos;
};

#endif // CENTRALTILEMAPWIDGET_H
