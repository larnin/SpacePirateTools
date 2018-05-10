#include "propertywidget.h"
#include <QVBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>

PropertyWidget::PropertyWidget(ObjectProperty &obj, bool forceEdition, QWidget *parent)
    : QWidget(parent)
    , m_property(obj)
{
    QGroupBox * box = new QGroupBox(obj.name);
    QVBoxLayout* boxLayout = new QVBoxLayout();
    if(forceEdition || obj.inspectorVisibility == InspectorVisibility::Visible)
        boxLayout->addWidget(obj.value->createUi());
    else if(obj.inspectorVisibility == InspectorVisibility::AsString)
        boxLayout->addWidget(new QLabel(obj.value->toString()));
    if(forceEdition || obj.inspectorVisibility != InspectorVisibility::Hidden)
    {
        QPushButton* removeButton = new QPushButton("Supprimer");
        boxLayout->addWidget(removeButton);
        connect(removeButton, SIGNAL(clicked(bool)), this, SLOT(removeRequested()));
    }
    box->setLayout(boxLayout);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(box);
    setLayout(layout);
}
