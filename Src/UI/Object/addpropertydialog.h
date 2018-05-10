#ifndef ADDPROPERTYDIALOG_H
#define ADDPROPERTYDIALOG_H

#include "Object/objectproperty.h"
#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <memory>

class AddPropertyDialog : public QDialog
{
public:
    AddPropertyDialog(QWidget * parent = nullptr);

    std::unique_ptr<ObjectProperty> get() const;

    static std::unique_ptr<ObjectProperty> getProperty(QWidget* parent, bool *ok = nullptr);

private:
    QLineEdit* m_name;
    QComboBox* m_valueType;
};

#endif // ADDPROPERTYDIALOG_H
