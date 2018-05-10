#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include "Object/objectproperty.h"
#include <QWidget>

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    PropertyWidget(ObjectProperty & obj, bool forceEdition, QWidget * parent = nullptr);

signals:
    void removeRequested();

private:
    ObjectProperty & m_property;
};

#endif // PROPERTYWIDGET_H
