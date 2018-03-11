#ifndef ANIMATORSTATE_H
#define ANIMATORSTATE_H

#include <QString>
#include <QJsonObject>

struct AnimatorState
{
    AnimatorState();
    AnimatorState(const QJsonObject & obj);
    QString stateName;
    QString animation;
    bool xFliped;
    bool yFliped;

    QJsonObject save() const;

};

#endif // ANIMATORSTATE_H
