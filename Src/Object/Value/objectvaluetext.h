#ifndef OBJECTVALUETEXT_H
#define OBJECTVALUETEXT_H

#include "objectvaluebase.h"
#include <QString>

class ObjectValueText : public ObjectValueBase
{
public:
    ObjectValueText();
    ObjectValueText(const QJsonObject & obj);
    ObjectValueText(const ObjectValueText &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueText>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    QString text;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUETEXT_H
