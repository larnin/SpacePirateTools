#include "objectinfos.h"
#include "UI/linewidget.h"
#include "propertywidget.h"
#include "addpropertydialog.h"
#include <QLabel>
#include <QPushButton>
#include <algorithm>

ObjectInfos::ObjectInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_assetName(assetName)
    , m_datas(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
{
    initializeWidgets();
}

ObjectInfos::~ObjectInfos()
{
    m_datas.save(m_assetName);
}

void ObjectInfos::initializeWidgets()
{
    m_propertiesLayout = new QVBoxLayout();
    for(auto & p : m_datas)
        addPropertyWidget(*p);

    QPushButton * addButton = new QPushButton("Ajouter une propriétée");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(m_propertiesLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(addButton);
    layout->addStretch(1);
    setLayout(layout);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(onAddClicked()));
}

void ObjectInfos::addPropertyWidget(ObjectProperty & p)
{
    auto widget = new PropertyWidget(p, true);
    m_widgets.push_back(widget);
    m_propertiesLayout->addWidget(widget);
    connect(widget, &PropertyWidget::removeRequested, this, [this, widget](){onRemove(widget);});
}

void ObjectInfos::removePropertyWidget(unsigned int index)
{
    m_propertiesLayout->removeWidget(m_widgets[index]);
    delete m_widgets[index];

    m_widgets.erase(m_widgets.begin() + index);
}

void ObjectInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void ObjectInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
}

void ObjectInfos::onAddClicked()
{
    bool ok = false;
    auto p = AddPropertyDialog::getProperty(this, &ok);
    if(!ok)
        return;

    addPropertyWidget(*p);
    m_datas.push_back(std::move(p));
}

void ObjectInfos::onRemove(QWidget* widget)
{
    auto it = std::find(m_widgets.begin(), m_widgets.end(), widget);
    if(it == m_widgets.end())
        return;

    auto index = std::distance(m_widgets.begin(), it);

    removePropertyWidget(index);
    m_datas.erase(m_datas.begin() + index);
}
