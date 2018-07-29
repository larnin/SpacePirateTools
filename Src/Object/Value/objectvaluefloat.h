#ifndef OBJECTVALUEFLOAT_H
#define OBJECTVALUEFLOAT_H

#include "objectvaluebase.h"

class ObjectValueFloat : public ObjectValueBase
{
public:
    ObjectValueFloat();
    ObjectValueFloat(const QJsonObject & obj);
    ObjectValueFloat(const ObjectValueFloat &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueFloat>(*this); }

    QString toString() const override;
    QWidget* createUi() override;

    float value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEFLOAT_H
