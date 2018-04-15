#ifndef NEWLAYERDIALOG_H
#define NEWLAYERDIALOG_H

#include "Scene/Layers/layerbase.h"
#include <QDialog>
#include <QString>
#include <QLineEdit>
#include <QComboBox>

struct NewLayerDialogReturn
{
    LayerType type;
    QString name;
};

class NewLayerDialog : public QDialog
{
public:
    NewLayerDialog(QWidget * parent = nullptr);

    NewLayerDialogReturn get();

    static NewLayerDialogReturn getLayerInfos(QWidget* parent, bool *ok = nullptr);

private:
    QLineEdit * m_name;
    QComboBox * m_type;
};

#endif // NEWLAYERDIALOG_H
