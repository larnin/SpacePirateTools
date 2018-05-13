#ifndef COLORVALUEWIDGET_H
#define COLORVALUEWIDGET_H

#include "Object/Value/objectvaluecolor.h"
#include <QWidget>
#include <QSpinBox>
#include <QPushButton>

class ColorValueWidget : public QWidget
{
    Q_OBJECT
public:
    ColorValueWidget(ObjectValueColor & color, QWidget * parent = nullptr);

public slots:
    void onClickColor();
    void onValueChange();

private:
    void updateColorButton();

    ObjectValueColor & m_color;

    QSpinBox * m_r;
    QSpinBox * m_g;
    QSpinBox * m_b;
    QSpinBox * m_a;

    QPushButton * m_colorButton;
};

#endif // COLORVALUEWIDGET_H
