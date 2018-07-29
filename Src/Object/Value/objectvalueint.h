#ifndef OBJECTVALUEINT_H
#define OBJECTVALUEINT_H

#include "objectvaluebase.h"

class ObjectValueInt : public ObjectValueBase
{
public:
    ObjectValueInt();
    ObjectValueInt(const QJsonObject & obj);
    ObjectValueInt(const ObjectValueInt &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueInt>(*this); }

    QString toString() const override;
    QWidget* createUi() override;

    int value;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUEINT_H
