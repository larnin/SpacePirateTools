#include "propertywidget.h"
#include "UI/linewidget.h"
#include "enumiterators.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGroupBox>
#include <QLabel>
#include <QPushButton>
#include <cassert>

PropertyWidget::PropertyWidget(ObjectProperty &obj, bool forceEdition, QWidget *parent)
    : QWidget(parent)
    , m_property(obj)
{
    QVBoxLayout * fullVisibilityLayout;
    if(forceEdition)
    {
        m_inspectorVisibility = new QComboBox();
        for(auto v : InspectorVisibility::Max)
            m_inspectorVisibility->addItem(inspectorVisibilityToString(v));
        m_inspectorVisibility->setCurrentIndex(static_cast<int>(obj.inspectorVisibility));

        m_sceneVisibility = new QComboBox();
        for(auto v : SceneVisibility::Max)
            m_sceneVisibility->addItem(sceneVisibilityToString(v));
        m_sceneVisibility->setCurrentIndex(static_cast<int>(obj.sceneVisibility));


        QHBoxLayout * visibilityLayout = new QHBoxLayout();
        visibilityLayout->addWidget(new QLabel("Visibilitée : "));
        visibilityLayout->addWidget(new QLabel("Inspector "));
        visibilityLayout->addWidget(m_inspectorVisibility, 1);
        visibilityLayout->addSpacing(10);
        visibilityLayout->addWidget(new QLabel("Scene "));
        visibilityLayout->addWidget(m_sceneVisibility, 1);

        m_fixedSize = new QCheckBox(" ");
        m_fixedSize->setChecked(obj.fixedSize);
        m_addElementButton = new QPushButton("Ajouter une valeur");
        m_addElementButton->setEnabled(!m_fixedSize);

        QHBoxLayout * sizeLayout = new QHBoxLayout();
        sizeLayout->addWidget(new QLabel("Taille fixe : "));
        sizeLayout->addWidget(m_fixedSize);
        sizeLayout->addSpacing(10);
        sizeLayout->addWidget(m_addElementButton);

        fullVisibilityLayout = new QVBoxLayout();
        fullVisibilityLayout->addLayout(visibilityLayout);
        fullVisibilityLayout->addLayout(sizeLayout);
        fullVisibilityLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    }
    else if(!obj.fixedSize)
    {
        fullVisibilityLayout = new QVBoxLayout();
        m_addElementButton = new QPushButton("Ajouter une valeur");
        fullVisibilityLayout->addWidget(m_addElementButton);
    }

    assert(!obj.values.empty());

    QGroupBox * box = new QGroupBox(obj.name + " - " + valueTypeToString(obj.values[0]->type()));
    m_valuesLayout = new QVBoxLayout();
    for(auto & v : obj.values)
        add(*v);
    onFixedSizeChange();

    QVBoxLayout * boxLayout = new QVBoxLayout();
    if(forceEdition || !obj.fixedSize)
        boxLayout->addLayout(fullVisibilityLayout);
    boxLayout->addLayout(m_valuesLayout);
    if(obj.values[0]->type() != ValueType::Transform && (forceEdition || obj.inspectorVisibility != InspectorVisibility::Hidden))
    {
        QPushButton* removeButton = new QPushButton("Supprimer");
        boxLayout->addWidget(removeButton);
        connect(removeButton, SIGNAL(clicked(bool)), this, SIGNAL(removeRequested()));
    }
    box->setLayout(boxLayout);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(box);
    setLayout(layout);

    if(forceEdition)
    {
        connect(m_inspectorVisibility, SIGNAL(currentIndexChanged(int)), this, SLOT(onVisibilityChange()));
        connect(m_sceneVisibility, SIGNAL(currentIndexChanged(int)), this, SLOT(onVisibilityChange()));
        connect(m_fixedSize, SIGNAL(toggled(bool)), this, SLOT(onFixedSizeChange()));
        connect(m_addElementButton, SIGNAL(clicked(bool)), this, SLOT(onAddElement()));
    }
    else if(!obj.fixedSize)
        connect(m_addElementButton, SIGNAL(clicked(bool)), this, SLOT(onAddElement()));
/*
    QGroupBox * box = new QGroupBox(obj.name + " - " + valueTypeToString(obj.value->type()));
    QVBoxLayout* boxLayout = new QVBoxLayout();
    if(forceEdition)
    {
        boxLayout->addLayout(visibilityLayout);
        boxLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    }
    if(forceEdition || obj.inspectorVisibility == InspectorVisibility::Visible)
        boxLayout->addWidget(obj.value->createUi());
    else if(obj.inspectorVisibility == InspectorVisibility::AsString)
        boxLayout->addWidget(new QLabel(obj.value->toString()));
    if(obj.value->type() != ValueType::Transform && (forceEdition || obj.inspectorVisibility != InspectorVisibility::Hidden))
    {
        QPushButton* removeButton = new QPushButton("Supprimer");
        boxLayout->addWidget(removeButton);
        connect(removeButton, SIGNAL(clicked(bool)), this, SIGNAL(removeRequested()));
    }
    box->setLayout(boxLayout);

    QVBoxLayout* layout = new QVBoxLayout();
    layout->setMargin(0);
    layout->addWidget(box);
    setLayout(layout);

    if(forceEdition)
    {
        connect(m_inspectorVisibility, SIGNAL(currentIndexChanged(int)), this, SLOT(onVisibilityChange()));
        connect(m_sceneVisibility, SIGNAL(currentIndexChanged(int)), this, SLOT(onVisibilityChange()));
    }*/
}

void PropertyWidget::onVisibilityChange()
{
    m_property.inspectorVisibility = static_cast<InspectorVisibility>(m_inspectorVisibility->currentIndex());
    m_property.sceneVisibility = static_cast<SceneVisibility>(m_sceneVisibility->currentIndex());
}

void PropertyWidget::onDelete(QWidget * button)
{

}

void PropertyWidget::onAddElement()
{

}

void PropertyWidget::onFixedSizeChange()
{

}

void PropertyWidget::add(ObjectValueBase & value)
{

}
