
#include "animatorstate.h"
#include <QJsonValue>

AnimatorState::AnimatorState()
    : xFliped(false)
    , yFliped(false)
{

}

AnimatorState::AnimatorState(const QJsonObject &obj)
{
    stateName = obj["name"].toString();
    animation = obj["animation"].toString();
    xFliped = obj["xFliped"].toBool();
    yFliped = obj["yFliped"].toBool();
}

AnimatorState::AnimatorState(const QString & _stateName, const QString & _animation, bool _xFliped, bool _yfliped)
    : stateName(_stateName)
    , animation(_animation)
    , xFliped(_xFliped)
    , yFliped(_yfliped)
{

}

QJsonObject AnimatorState::save() const
{
    QJsonObject obj;
    obj.insert("name", stateName);
    obj.insert("animation", animation);
    obj.insert("xFliped", xFliped);
    obj.insert("yFliped", yFliped);

    return obj;
}

