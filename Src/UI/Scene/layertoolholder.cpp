#include "layertoolholder.h"
#include <QLabel>

const QString labelText("No layer selected");

LayerToolHolder::LayerToolHolder(QWidget *parent)
    : QWidget(parent)
{
    m_layout = new QVBoxLayout();
    m_currentWidget = new QLabel(labelText);
    m_layout->addWidget(m_currentWidget);

    setLayout(m_layout);
    setMinimumWidth(200);
}

void LayerToolHolder::setWidget(QWidget *widget)
{
    m_layout->removeWidget(m_currentWidget);
    delete m_currentWidget;

    if(widget == nullptr)
        m_currentWidget = new QLabel(labelText);
    else m_currentWidget = widget;
    m_layout->addWidget(m_currentWidget);
}
