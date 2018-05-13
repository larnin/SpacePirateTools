#ifndef OBJECTVALUEVECTOR2F_H
#define OBJECTVALUEVECTOR2F_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueVector2f : public ObjectValueBase
{
public:
    ObjectValueVector2f();
    ObjectValueVector2f(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2f value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEVECTOR2F_H
