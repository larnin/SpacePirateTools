#ifndef LINEWIDGET_H
#define LINEWIDGET_H

#include <QFrame>

enum class LineOrientation
{
    Horizontal,
    Vertical,
};

class LineWidget : public QFrame
{
public:
    inline LineWidget(LineOrientation orientation, QWidget * parent = nullptr)
        : QFrame(parent)
    {
        if(orientation == LineOrientation::Horizontal)
            setFrameShape(QFrame::HLine);
        else setFrameShape(QFrame::VLine);
        setFrameShadow(QFrame::Sunken);
    }
};

#endif // LINEWIDGET_H
