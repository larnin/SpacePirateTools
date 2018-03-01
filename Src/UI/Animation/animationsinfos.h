#ifndef ANIMATIONSINFOS_H
#define ANIMATIONSINFOS_H

#include "Animation/animationdata.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/renamedfileevent.h"
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGroupBox>

class CentralAnimationWidget;

class AnimationsInfos : public QWidget
{
    friend class CentralAnimationWidget;
public:
    AnimationsInfos( const QString & assetName, QWidget * parent = nullptr);

private:
    inline void setCentralAnimationWidget(CentralAnimationWidget * w){ m_centralWidget = w; }

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);

    void initializeWidgets();

    CentralAnimationWidget * m_centralWidget;

    AnimationData m_datas;
    QString m_assetName;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;

    QComboBox* m_texture;
    QListWidget* m_frameList;

    QDoubleSpinBox* m_time;

    QSpinBox* m_offsetX;
    QSpinBox* m_offsety;

    QSpinBox* m_rectLeft;
    QSpinBox* m_rectTop;
    QSpinBox* m_rectWidth;
    QSpinBox* m_rectHeight;

    QGroupBox* m_frameDatasBox;

};

#endif // ANIMATIONSINFOS_H
