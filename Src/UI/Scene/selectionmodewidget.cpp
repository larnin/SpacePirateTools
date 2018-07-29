#include "selectionmodewidget.h"
#include <QHBoxLayout>

SelectionModeWidget::SelectionModeWidget(QWidget *parent)
    : QWidget(parent)
{

    m_moveWidget = new QRadioButton("Move");
    m_scaleWidget = new QRadioButton("Scale");
    m_rotateWidget = new QRadioButton("Rotate");
    m_moveWidget->setChecked(true);

    QHBoxLayout * layout = new QHBoxLayout();
    layout->addWidget(m_moveWidget);
    layout->addWidget(m_scaleWidget);
    layout->addWidget(m_rotateWidget);
    layout->setMargin(2);

    setLayout(layout);
    setStyleSheet("background-color:white;");

    connect(m_moveWidget, SIGNAL(clicked(bool)), this, SLOT(onButtonCheck()));
    connect(m_scaleWidget, SIGNAL(clicked(bool)), this, SLOT(onButtonCheck()));
    connect(m_rotateWidget, SIGNAL(clicked(bool)), this, SLOT(onButtonCheck()));
}

void SelectionModeWidget::onButtonCheck()
{
    if(m_moveWidget->isChecked())
        emit selectionStateChanged(SelectionState::Move);
    else if(m_scaleWidget->isChecked())
        emit selectionStateChanged(SelectionState::Scale);
    else if(m_rotateWidget->isChecked())
        emit selectionStateChanged(SelectionState::Rotate);
}

void SelectionModeWidget::onChangeSelectionState(SelectionState state)
{
    m_moveWidget->blockSignals(true);
    m_scaleWidget->blockSignals(true);
    m_rotateWidget->blockSignals(true);

    m_moveWidget->setChecked(false);
    m_scaleWidget->setChecked(false);
    m_rotateWidget->setChecked(false);

    if(state == SelectionState::Move)
        m_moveWidget->setChecked(true);
    else if(state == SelectionState::Rotate)
        m_rotateWidget->setChecked(true);
    else if(state == SelectionState::Scale)
        m_scaleWidget->setChecked(true);

    m_moveWidget->blockSignals(false);
    m_scaleWidget->blockSignals(false);
    m_rotateWidget->blockSignals(false);
}
