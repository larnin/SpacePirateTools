#ifndef ANIMATORTRANSITION_H
#define ANIMATORTRANSITION_H

#include "Conditions/basecondition.h"
#include <QJsonObject>
#include <QString>

struct AnimatorTransition
{
    AnimatorTransition(unsigned int _previousState, unsigned int _nextState);
    AnimatorTransition(const QJsonObject & obj);

    QJsonObject save() const;

    unsigned int previousState;
    unsigned int nextState;
    QString condition;
};

#endif // ANIMATORTRANSITION_H
