#ifndef DOCK_H
#define DOCK_H

#include <QDockWidget>

template <typename T>
class Dock : public QDockWidget
{
public:
    Dock(const QString & title, bool deleteOnClose = true, QWidget * parent = nullptr)
        : QDockWidget(title, parent)
    {
        setAttribute(Qt::WA_DeleteOnClose, deleteOnClose);
        m_widget = new T();

        setWidget(m_widget);
    }

private:
    T * m_widget;
};

#endif // DOCK_H
