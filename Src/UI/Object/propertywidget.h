#ifndef PROPERTYWIDGET_H
#define PROPERTYWIDGET_H

#include "Object/objectproperty.h"
#include <QWidget>
#include <QComboBox>
#include <QHBoxLayout>
#include <QCheckBox>
#include <QPushButton>

class PropertyWidget : public QWidget
{
    struct ValueInfo
    {
        QWidget * parent;
        QPushButton * button;
        QHBoxLayout * layout;
    };

    Q_OBJECT
public:
    PropertyWidget(ObjectProperty & obj, bool forceEdition, QWidget * parent = nullptr);

signals:
    void removeRequested();

public slots:
    void onVisibilityChange();
private:
    void set(ObjectValueBase & value);

    ObjectProperty & m_property;
    QComboBox * m_inspectorVisibility;
    QComboBox * m_sceneVisibility;
    ValueInfo m_value;
    bool m_forceEdition;
};

#endif // PROPERTYWIDGET_H
