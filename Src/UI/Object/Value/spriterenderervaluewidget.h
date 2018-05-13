#ifndef SPRITERENDERERVALUEWIDGET_H
#define SPRITERENDERERVALUEWIDGET_H

#include "Object/Value/objectvaluespriterenderer.h"
#include <QWidget>
#include <QSpinBox>

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
};

#endif // SPRITERENDERERVALUEWIDGET_H
