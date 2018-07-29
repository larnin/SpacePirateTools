#ifndef OBJECTVALUESCRIPT_H
#define OBJECTVALUESCRIPT_H

#include "objectvaluebase.h"
#include <QString>

class ObjectValueScript : public ObjectValueBase
{
public:
    ObjectValueScript();
    ObjectValueScript(const QJsonObject & obj);
    ObjectValueScript(const ObjectValueScript &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueScript>(*this); }

    QString toString() const override;
    QWidget* createUi() override;

    QString scriptName;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUESCRIPT_H
