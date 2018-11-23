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

        fullVisibilityLayout = new QVBoxLayout();
        fullVisibilityLayout->addLayout(visibilityLayout);
        fullVisibilityLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    }

    QGroupBox * box = new QGroupBox(obj.name + " - " + valueTypeToString(obj.value->type()));
    set(*obj.value);

    QVBoxLayout * boxLayout = new QVBoxLayout();
    if(forceEdition)
        boxLayout->addLayout(fullVisibilityLayout);
    boxLayout->addWidget(m_value.parent);
    if(obj.value->type() != ValueType::Transform && forceEdition)
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
    }
}

void PropertyWidget::onVisibilityChange()
{
    m_property.inspectorVisibility = static_cast<InspectorVisibility>(m_inspectorVisibility->currentIndex());
    m_property.sceneVisibility = static_cast<SceneVisibility>(m_sceneVisibility->currentIndex());
}

void PropertyWidget::set(ObjectValueBase & value)
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

    m_value = v;
}
