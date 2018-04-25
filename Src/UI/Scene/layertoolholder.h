#ifndef LAYERTOOLHOLDER_H
#define LAYERTOOLHOLDER_H

#include <QWidget>
#include <QVBoxLayout>

class LayerToolHolder : public QWidget
{
public:
    LayerToolHolder(QWidget * parent = nullptr);

    void setWidget(QWidget *widget);

private:
    QVBoxLayout * m_layout;
    QWidget * m_currentWidget;
};

#endif // LAYERTOOLHOLDER_H
