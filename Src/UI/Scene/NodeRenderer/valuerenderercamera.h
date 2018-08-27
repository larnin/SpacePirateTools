#ifndef VALUERENDERERCAMERA_H
#define VALUERENDERERCAMERA_H

#include "valuerendererbase.h"
#include "Object/Value/objectvaluecamera.h"

class ValueRendererCamera : public ValueRendererBase
{
public:
    ValueRendererCamera(SceneNode * node, ObjectValueBase * value);

    void draw(sf::RenderTarget &) const override;
    void drawGizmos(sf::RenderTarget & target) const override;
    void update() override;

private:
    ObjectValueCamera * m_camera;
};
#endif // VALUERENDERERCAMERA_H
