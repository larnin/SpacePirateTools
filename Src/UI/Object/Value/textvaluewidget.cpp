#include "textvaluewidget.h"
#include <QHBoxLayout>
#include <QLabel>

TextValueWidget::TextValueWidget(ObjectValueText &text, QWidget *parent)
    : QWidget(parent)
    , m_text(text)
{
    m_value = new QTextEdit();
    m_value->setPlainText(m_text.text);

    QHBoxLayout * textLayout = new QHBoxLayout();
    textLayout->addWidget(new QLabel("Texte : "));
    textLayout->addWidget(m_value);

    setLayout(textLayout);

    connect(m_value, SIGNAL(textChanged()), this, SLOT(onValueChanged()));
}

void TextValueWidget::onValueChanged()
{
    m_text.text = m_value->toPlainText();
}
