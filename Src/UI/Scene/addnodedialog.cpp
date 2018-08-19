#include "addnodedialog.h"
#include "ProjectInfos/projectinfos.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>

AddNodeDialog::AddNodeDialog(QWidget *parent)
    : QDialog(parent)
{
    m_nodeName = new QLineEdit();
    m_typeBox = new QComboBox();
    m_assetBox = new QComboBox();
    QHBoxLayout * nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Nom : "));
    nameLayout->addWidget(m_nodeName);
    QHBoxLayout * typeLayout = new QHBoxLayout();
    typeLayout->addWidget(new QLabel("Type d'asset : "));
    typeLayout->addWidget(m_typeBox);
    QHBoxLayout * assetLayout = new QHBoxLayout();
    assetLayout->addWidget(new QLabel("Asset : "));
    assetLayout->addWidget(m_assetBox);

    QPushButton* validButton = new QPushButton("Valider");
    QPushButton* cancelButton = new QPushButton("Annuler");
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(validButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Ajouter un nouveau noeud"));
    layout->addSpacing(10);
    layout->addLayout(nameLayout);
    layout->addLayout(typeLayout);
    layout->addLayout(assetLayout);
    layout->addSpacing(10);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(validButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
    connect(m_typeBox, SIGNAL(currentIndexChanged(int)), this, SLOT(onTypeAssetChanged()));

    updateTypeBox();
    updateAssetBox();
}

void AddNodeDialog::updateAssetBox()
{
    m_assetBox->clear();

    for(const auto & i : ProjectInfos::instance().fileInfos(isPrefabType() ? AssetType::Scene : AssetType::Object))
        m_assetBox->addItem(i);
}
void AddNodeDialog::updateTypeBox()
{
    m_typeBox->clear();
    m_typeBox->addItem("Object");
    m_typeBox->addItem("Prefab");
}

AddNodeDialog::ReturnValue AddNodeDialog::get() const
{
    return {isPrefabType(), m_assetBox->currentText(), m_nodeName->text()};
}

AddNodeDialog::ReturnValue AddNodeDialog::getNewAsset(QWidget* parent, bool *ok)
{
    AddNodeDialog dialog(parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}


bool AddNodeDialog::isPrefabType() const
{
    return m_typeBox->currentIndex() > 0;
}

void AddNodeDialog::onTypeAssetChanged()
{
    updateAssetBox();
}
