#include "animatortransition.h"

AnimatorTransition::AnimatorTransition(unsigned int _previousState, unsigned int _nextState)
    : previousState(_previousState)
    , nextState(_nextState)
{

}

AnimatorTransition::AnimatorTransition(const QJsonObject & obj)
{
    previousState = obj["previous"].toInt();
    nextState = obj["next"].toInt();
    condition = obj["condition"].toString();
}

QJsonObject AnimatorTransition::save() const
{
    QJsonObject obj;
    obj.insert("previous", int(previousState));
    obj.insert("next", int(nextState));
    obj.insert("condition", condition);

    return obj;
}