#ifndef OBJECTVALUECOLOR_H
#define OBJECTVALUECOLOR_H

#include "objectvaluebase.h"
#include <SFML/Graphics/Color.hpp>

class ObjectValueColor : public ObjectValueBase
{
public:
    ObjectValueColor();
    ObjectValueColor(const QJsonObject & obj);
    ObjectValueColor(const ObjectValueColor &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueColor>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    sf::Color color;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECOLOR_H
