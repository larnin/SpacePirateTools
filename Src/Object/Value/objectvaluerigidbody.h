#ifndef OBJECTVALUERIGIDBODY_H
#define OBJECTVALUERIGIDBODY_H

#include "objectvaluebase.h"

class ObjectValueRigidbody : public ObjectValueBase
{
public:
    ObjectValueRigidbody();
    ObjectValueRigidbody(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    float mass;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUERIGIDBODY_H