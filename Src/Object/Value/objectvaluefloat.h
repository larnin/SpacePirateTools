#ifndef OBJECTVALUEFLOAT_H
#define OBJECTVALUEFLOAT_H

#include "objectvaluebase.h"

class ObjectValueFloat : public ObjectValueBase
{
public:
    ObjectValueFloat();
    ObjectValueFloat(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    float value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEFLOAT_H
