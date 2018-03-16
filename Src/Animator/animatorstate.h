#ifndef ANIMATORSTATE_H
#define ANIMATORSTATE_H

#include <QString>
#include <QJsonObject>
#include <SFML/Graphics/Rect.hpp>

struct AnimatorState
{
    AnimatorState();
    AnimatorState(const QJsonObject & obj);
    AnimatorState(const QString & _stateName, const QString & _animation = "", bool _xFliped = false, bool _yfliped = false);
    QString stateName;
    QString animation;
    bool xFliped;
    bool yFliped;
    sf::IntRect rect;

    QJsonObject save() const;

};

#endif // ANIMATORSTATE_H
