#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include "Object/objectproperty.h"
#include <QWidget>

class PropertyWidget : public QWidget
{
public:
    PropertyWidget(ObjectProperty & obj, QWidget * parent = nullptr);

private:
    ObjectProperty & m_property;
};

#endif // PROPERTYWIDGET_H
