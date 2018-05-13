#include "scriptvaluewidget.h"
#include <QLabel>
#include <QHBoxLayout>

ScriptValueWidget::ScriptValueWidget(ObjectValueScript &script, QWidget *parent)
    : QWidget(parent)
    , m_script(script)
{
    m_scriptName = new QLineEdit();
    m_scriptName->setText(m_script.scriptName);

    QHBoxLayout * scriptNameLayout = new QHBoxLayout;
    scriptNameLayout->addWidget(new QLabel("Nom du script : "));
    scriptNameLayout->addWidget(m_scriptName);

    setLayout(scriptNameLayout);

    connect(m_scriptName, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void ScriptValueWidget::onValueChanged()
{
    m_script.scriptName = m_scriptName->text();
}
