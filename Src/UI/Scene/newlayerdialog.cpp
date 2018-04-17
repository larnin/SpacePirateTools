#include "newlayerdialog.h"
#include "enumiterators.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

NewLayerDialog::NewLayerDialog(QWidget *parent)
    : QDialog(parent)
{
    m_name = new QLineEdit();
    QHBoxLayout* nameLayout = new QHBoxLayout();
    nameLayout->addWidget(new QLabel("Nom : "));
    nameLayout->addWidget(m_name, 1);

    m_type = new QComboBox();
    for(auto v : LayerType::Max)
        m_type->addItem(layerTypeToString(v));
    QHBoxLayout* typeLayout = new QHBoxLayout();
    typeLayout->addWidget(new QLabel("Type : "));
    typeLayout->addWidget(m_type, 1);

    QPushButton* acceptButton = new QPushButton("Valider");
    QPushButton* abortButton = new QPushButton("Annuler");

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(acceptButton);
    buttonsLayout->addWidget(abortButton);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Choisissez le type et le nom du nouveau layer."));
    layout->addSpacing(10);
    layout->addLayout(nameLayout);
    layout->addLayout(typeLayout);
    layout->addSpacing(10);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(acceptButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(abortButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

NewLayerDialogReturn NewLayerDialog::get()
{
    return NewLayerDialogReturn{static_cast<LayerType>(m_type->currentIndex()), m_name->text()};
}

NewLayerDialogReturn NewLayerDialog::getLayerInfos(QWidget* parent, bool *ok)
{
    NewLayerDialog dialog(parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}
