#ifndef OBJECTVALUECAMERA_H
#define OBJECTVALUECAMERA_H

#include "objectvaluebase.h"

class ObjectValueCamera : public ObjectValueBase
{
public:
    ObjectValueCamera();
    ObjectValueCamera(const QJsonObject & obj);
    ObjectValueCamera(const ObjectValueCamera &) = default;

    std::unique_ptr<ObjectValueBase> clone() const override { return std::make_unique<ObjectValueCamera>(*this); }

    std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) override;

    QString toString() const override;
    QWidget* createUi() override;

    unsigned int layerMask;
    bool fixedSize;
    //if fixedSize, value is the size of the camera
    //else, value is the zoom of the camera
    float value;


protected:
    void onSave(QJsonObject & obj) const override;
};

#endif // OBJECTVALUECAMERA_H
