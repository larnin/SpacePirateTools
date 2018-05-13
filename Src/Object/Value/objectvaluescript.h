#ifndef OBJECTVALUESCRIPT_H
#define OBJECTVALUESCRIPT_H

#include "objectvaluebase.h"
#include <QString>

class ObjectValueScript : public ObjectValueBase
{
public:
    ObjectValueScript();
    ObjectValueScript(const QJsonObject & obj);

    QString toString() const override;
    QWidget* createUi() override;

    QString scriptName;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUESCRIPT_H
