#include "addpropertydialog.h"
#include "enumiterators.h"
#include "Object/Value/objectvaluebase.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>

AddPropertyDialog::AddPropertyDialog(QWidget * parent)
    : QDialog(parent)
{
    setWindowTitle("Ajouter une propriétée");

    m_name = new QLineEdit("Property");
    m_valueType = new QComboBox();

    for(auto type : ValueType::Max)
        m_valueType->addItem(valueTypeToString(type));

    QPushButton* validButton = new QPushButton("Valider");
    QPushButton* cancelButton = new QPushButton("Annuler");

    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(validButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Nom de la propriétée"));
    layout->addWidget(m_name);
    layout->addSpacing(10);
    layout->addWidget(new QLabel("Type de la valeur de la propriétée"));
    layout->addWidget(m_valueType);
    layout->addLayout(buttonsLayout);
    setLayout(layout);

    setFixedSize(250, 150);

    connect(validButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

std::unique_ptr<ObjectProperty> AddPropertyDialog::get() const
{
    auto p = std::make_unique<ObjectProperty>();
    p->name = m_name->text();
    p->values.push_back(ObjectValueBase::createValue(static_cast<ValueType>(m_valueType->currentIndex())));
    p->inspectorVisibility = InspectorVisibility::Visible;
    p->sceneVisibility = SceneVisibility::All;

    return std::move(p);
}

std::unique_ptr<ObjectProperty> AddPropertyDialog::getProperty(QWidget* parent, bool *ok)
{
    AddPropertyDialog dialog(parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}
