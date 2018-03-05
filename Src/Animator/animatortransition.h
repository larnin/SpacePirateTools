#ifndef ANIMATORTRANSITION_H
#define ANIMATORTRANSITION_H

#include "Conditions/basecondition.h"
#include <QJsonObject>
#include <memory>

struct AnimatorTransition
{
public:
    AnimatorTransition(unsigned int _previousState, unsigned int _nextState);
    AnimatorTransition(const QJsonObject & obj);
    AnimatorTransition(AnimatorTransition &&) noexcept = default;
    AnimatorTransition & operator = (AnimatorTransition &&) noexcept = default;

    QJsonObject save() const;

    unsigned int previousState;
    unsigned int nextState;

    std::unique_ptr<BaseCondition> condition;
};

#endif // ANIMATORTRANSITION_H
