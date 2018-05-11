#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include "Object/objectproperty.h"
#include <QWidget>
#include <QComboBox>

class PropertyWidget : public QWidget
{
    Q_OBJECT
public:
    PropertyWidget(ObjectProperty & obj, bool forceEdition, QWidget * parent = nullptr);

signals:
    void removeRequested();

public slots:
    void onVisibilityChange();

private:
    ObjectProperty & m_property;
    QComboBox * m_inspectorVisibility;
    QComboBox * m_sceneVisibility;
};

#endif // PROPERTYWIDGET_H
