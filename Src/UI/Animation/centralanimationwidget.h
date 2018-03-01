#ifndef CENTRALANIMATIONWIDGET_H
#define CENTRALANIMATIONWIDGET_H

#include "UI/qsfmlcanvas.h"
#include "animationsinfos.h"
#include <QString>

class CentralAnimationWidget : public QSFMLCanvas
{
public:
    CentralAnimationWidget(AnimationsInfos* infos, QWidget * parent = nullptr);

protected:
    void OnUpdate() override;

private:
    AnimationsInfos * m_animationInfos;
};

#endif // CENTRALANIMATIONWIDGET_H
