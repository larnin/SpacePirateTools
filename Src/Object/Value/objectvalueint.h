#ifndef OBJECTVALUEINT_H
#define OBJECTVALUEINT_H

#include "objectvaluebase.h"

class ObjectValueInt : public ObjectValueBase
{
public:
    ObjectValueInt();
    ObjectValueInt(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    int value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEINT_H
