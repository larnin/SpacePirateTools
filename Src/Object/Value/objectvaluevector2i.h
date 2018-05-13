#ifndef OBJECTVALUEVECTOR2I_H
#define OBJECTVALUEVECTOR2I_H

#include "objectvaluebase.h"
#include <SFML/System/Vector2.hpp>

class ObjectValueVector2i : public ObjectValueBase
{
public:
    ObjectValueVector2i();
    ObjectValueVector2i(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::Vector2i value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEVECTOR2I_H
