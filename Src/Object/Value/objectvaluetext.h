#ifndef OBJECTVALUETEXT_H
#define OBJECTVALUETEXT_H

#include "objectvaluebase.h"
#include <QString>

class ObjectValueText : public ObjectValueBase
{
public:
    ObjectValueText();
    ObjectValueText(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    QString text;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUETEXT_H
