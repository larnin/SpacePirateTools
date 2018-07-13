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
    , m_inspectorVisibility(nullptr)
    , m_sceneVisibility(nullptr)
    , m_addElementButton(nullptr)
    , m_valuesLayout(nullptr)
    , m_forceEdition(forceEdition)
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
        m_addElementButton->setEnabled(!obj.fixedSize);

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
    if(forceEdition)
        onFixedSizeChange();

    QVBoxLayout * boxLayout = new QVBoxLayout();
    if(forceEdition || !obj.fixedSize)
        boxLayout->addLayout(fullVisibilityLayout);
    boxLayout->addLayout(m_valuesLayout);
    if(obj.values[0]->type() != ValueType::Transform && forceEdition)
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
}

void PropertyWidget::onVisibilityChange()
{
    m_property.inspectorVisibility = static_cast<InspectorVisibility>(m_inspectorVisibility->currentIndex());
    m_property.sceneVisibility = static_cast<SceneVisibility>(m_sceneVisibility->currentIndex());
}
#include <iostream>
void PropertyWidget::onDelete(QWidget * button)
{
    if(m_property.values.size() <= 1)
        return;

    auto it = std::find_if(m_values.begin(), m_values.end(), [button](const auto & v){return v.button == button;});
    if(it == m_values.end())
        return;
    unsigned id = std::distance(m_values.begin(), it);

    m_valuesLayout->removeWidget(m_values[id].parent);
    delete m_values[id].parent;

    m_values.erase(it);
    m_property.values.erase(m_property.values.begin() + id);
}

void PropertyWidget::onAddElement()
{
    m_property.values.push_back(ObjectValueBase::createValue(m_property.values[0]->type()));

    add(*(m_property.values.back()));
    onFixedSizeChange();
}

void PropertyWidget::onFixedSizeChange()
{
    if(m_fixedSize != nullptr)
        m_property.fixedSize = m_fixedSize->isChecked();

    if(m_property.fixedSize)
    {
        for(auto & v : m_values)
        {
            if(v.button != nullptr)
            {
                v.layout->removeWidget(v.button);
                delete v.button;
                v.button = nullptr;
            }
        }
    }
    else
    {
        for(auto & v : m_values)
        {
            if(v.button == nullptr)
            {
                v.button = new QPushButton("X");
                v.button->setFixedWidth(30);
                v.layout->addWidget(v.button);
                connect(v.button, &QPushButton::clicked, this, [this, button = v.button](bool){onDelete(button);});
            }
        }
    }

    if(m_addElementButton != nullptr)
        m_addElementButton->setEnabled(!m_property.fixedSize);
}

void PropertyWidget::add(ObjectValueBase & value)
{
    ValueInfo v;
    v.button = nullptr;
    v.parent = new QWidget();
    v.layout = new QHBoxLayout();

    if(m_forceEdition || m_property.inspectorVisibility == InspectorVisibility::Visible)
        v.layout->addWidget(value.createUi());
    else if(m_property.inspectorVisibility == InspectorVisibility::AsString)
        v.layout->addWidget(new QLabel(value.toString()));

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(v.layout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->setMargin(0);
    v.parent->setLayout(layout);

    m_valuesLayout->addWidget(v.parent);
    m_values.push_back(v);
}
