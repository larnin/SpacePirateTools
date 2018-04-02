#include "brushcreatedialog.h"
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

BrushCreateDialog::BrushCreateDialog(QWidget *parent)
    : QDialog(parent)
{
    m_name = new QLineEdit();
    m_type = new QComboBox();

    QPushButton* okButton = new QPushButton("Ok");
    QPushButton* cancelButton = new QPushButton("Annuler");
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addWidget(okButton, 0, Qt::AlignRight);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Entrez le nom du nouveau pinceau"));
    layout->addWidget(m_name);
    layout->addSpacing(5);
    layout->addWidget(new QLabel("Choisissez le type de pinceau"));
    layout->addWidget(m_type);
    layout->addSpacing(5);
    layout->addLayout(buttonsLayout);

    setLayout(layout);

    connect(okButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));

    setTypeTexts();
}

void BrushCreateDialog::setTypeTexts()
{
    m_type->clear();

    for(unsigned int i(0) ; i <= static_cast<unsigned int>(BrushType::Max) ; i++)
        m_type->addItem(brushTypeToString(static_cast<BrushType>(i)));
}

BrushCreateInfos BrushCreateDialog::get() const
{
    return {static_cast<BrushType>(m_type->currentIndex()), m_name->text()};
}

BrushCreateInfos BrushCreateDialog::getBrush(QWidget *parent, bool *ok)
{
    BrushCreateDialog dialog(parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}
