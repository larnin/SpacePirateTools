#ifndef TEXTVALUEWIDGET_H
#define TEXTVALUEWIDGET_H

#include "Object/Value/objectvaluetext.h"
#include <QWidget>
#include <QTextEdit>

class TextValueWidget : public QWidget
{
    Q_OBJECT
public:
    TextValueWidget(ObjectValueText & text, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueText & m_text;
    QTextEdit * m_value;
};

#endif // TEXTVALUEWIDGET_H
