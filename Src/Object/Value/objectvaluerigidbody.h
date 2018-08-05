#ifndef OBJECTVALUERIGIDBODY_H
#define OBJECTVALUERIGIDBODY_H

#include "objectvaluebase.h"

class ObjectValueRigidbody : public ObjectValueBase
{
public:
    ObjectValueRigidbody();
    ObjectValueRigidbody(const QJsonObject & obj);
    ObjectValueRigidbody(const ObjectValueRigidbody &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueRigidbody>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    float mass;

protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUERIGIDBODY_H
