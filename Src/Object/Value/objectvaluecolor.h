#ifndef OBJECTVALUECOLOR_H
#define OBJECTVALUECOLOR_H

#include "objectvaluebase.h"
#include <SFML/Graphics/Color.hpp>

class ObjectValueColor : public ObjectValueBase
{
public:
    ObjectValueColor();
    ObjectValueColor(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    sf::Color color;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECOLOR_H
