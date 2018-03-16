#ifndef ANIMATORDATA_H
#define ANIMATORDATA_H

#include "animatorstate.h"
#include "animatortransition.h"
#include <QString>
#include <vector>

class AnimatorData
{
public:
    AnimatorData() = default;
    AnimatorData(const QString & fileName);

    void save(const QString & fileName) const;

    std::vector<AnimatorState> states;
    std::vector<AnimatorTransition> transitions;
    unsigned int startIndex;

private:
    void load(const QString & fileName);
};

#endif // ANIMATORDATA_H
