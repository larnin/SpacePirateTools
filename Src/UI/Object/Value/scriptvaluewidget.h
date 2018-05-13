#ifndef SCRIPTVALUEWIDGET_H
#define SCRIPTVALUEWIDGET_H

#include "Object/Value/objectvaluescript.h"
#include <QWidget>
#include <QLineEdit>

class ScriptValueWidget : public QWidget
{
    Q_OBJECT
public:
    ScriptValueWidget(ObjectValueScript & script, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    ObjectValueScript & m_script;

    QLineEdit * m_scriptName;
};

#endif // SCRIPTVALUEWIDGET_H
