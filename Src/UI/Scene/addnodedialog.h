#ifndef ADDNODEDIALOG_H
#define ADDNODEDIALOG_H

#include <QDialog>
#include <QComboBox>
#include <QLineEdit>
#include <QString>

class AddNodeDialog : public QDialog
{
    Q_OBJECT
public:

    struct ReturnValue
    {
        bool isPrefab;
        QString assetName;
        QString name;
    };

    AddNodeDialog(QWidget * parent = nullptr);

ReturnValue get() const;

static ReturnValue getNewAsset(QWidget* parent, bool *ok = nullptr);

public slots:
    void onTypeAssetChanged();

private:
    bool isPrefabType() const;
    void updateAssetBox();
    void updateTypeBox();

    QLineEdit* m_nodeName;
    QComboBox* m_typeBox;
    QComboBox* m_assetBox;
};

#endif // ADDNODEDIALOG_H
