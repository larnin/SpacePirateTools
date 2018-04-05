#ifndef CENTRALTILESETWINDOW_H
#define CENTRALTILESETWINDOW_H

#include "tilesetinfos.h"
#include "BrushsWindow/brushwindowbase.h"
#include "ressource.h"
#include <QWidget>
#include <QVBoxLayout>

class CentralTilesetWindow : public QWidget
{
public:
    CentralTilesetWindow(TilesetInfos * infos, QWidget * parent = nullptr);

    void setTexture(const QString & textureName);
    void setDeltaTile(unsigned int delta);
    void setBrushWindow(BrushWindowBase * window);

private:
    TilesetInfos * m_infos;
    BrushWindowBase *m_brushWindow;
    QVBoxLayout *m_layout;
    Texture m_texture;
    unsigned int m_delta;
};

#endif // CENTRALTILESETWINDOW_H
