#ifndef SELECTIONMODEWIDGET_H
#define SELECTIONMODEWIDGET_H

#include <QWidget>
#include <QRadioButton>

enum class SelectionState
{
    Move,
    Scale,
    Rotate,
    Custom
};

class SelectionModeWidget : public QWidget
{
    Q_OBJECT
public:
    SelectionModeWidget(QWidget * parent = nullptr);

public slots:
    void onButtonCheck();
    void onChangeSelectionState(SelectionState state);

signals:
    void selectionStateChanged(SelectionState);

private:
    QRadioButton * m_moveWidget;
    QRadioButton * m_scaleWidget;
    QRadioButton * m_rotateWidget;

};

#endif // SELECTIONMODEWIDGET_H
