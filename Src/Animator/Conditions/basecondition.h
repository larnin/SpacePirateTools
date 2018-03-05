#ifndef BASECONDITION_H
#define BASECONDITION_H

#include <QWidget>
#include <QJsonObject>
#include <memory>

enum class ConditionType
{

};

class BaseCondition
{
public:
    BaseCondition(ConditionType type);

    virtual void draw(QWidget * parent) = 0;

    QJsonObject save() const;

    static std::unique_ptr<BaseCondition> load(const QJsonObject & obj);

protected:
    virtual void onSave(QJsonObject & ob) const = 0;

    ConditionType m_conditionType;
};

#endif // BASECONDITION_H
