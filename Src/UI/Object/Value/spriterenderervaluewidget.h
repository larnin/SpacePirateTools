#ifndef SPRITERENDERERVALUEWIDGET_H
#define SPRITERENDERERVALUEWIDGET_H

#include "Object/Value/objectvaluespriterenderer.h"
#include <QWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>

class SpriteRendererValueWidget : public QWidget
{
    Q_OBJECT
public:
    SpriteRendererValueWidget(ObjectValueSpriteRenderer & spriteRenderer, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueSpriteRenderer & m_spriteRenderer;

    QSpinBox * m_top;
    QSpinBox * m_left;
    QSpinBox * m_width;
    QSpinBox * m_height;

    QDoubleSpinBox * m_offsetX;
    QDoubleSpinBox * m_offsetY;
};

#endif // SPRITERENDERERVALUEWIDGET_H
