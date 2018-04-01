#ifndef BRUSHCREATEDIALOG_H
#define BRUSHCREATEDIALOG_H

#include "Tileset/Brushs/brushbase.h"
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QComboBox>

struct BrushCreateInfos
{
    BrushType type;
    QString name;
};

class BrushCreateDialog : public QDialog
{
public:
    BrushCreateDialog(QWidget * parent = nullptr);

    BrushCreateInfos get() const;

    static BrushCreateInfos getBrush(QWidget* parent, bool *ok = nullptr);

private:
    void setTypeTexts();

    QLineEdit* m_name;
    QComboBox* m_type;
};

#endif // BRUSHCREATEDIALOG_H
