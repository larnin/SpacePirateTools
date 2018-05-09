#include "objectinfos.h"
#include "UI/linewidget.h"
#include "propertywidget.h"
#include <QLabel>
#include <QPushButton>

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
    {
        m_widgets.push_back(new PropertyWidget(p));
        m_propertiesLayout->addWidget(m_widgets.back());
    }

    QPushButton * addButton = new QPushButton("Ajouter une propriétée");

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(m_propertiesLayout);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(addButton);
    layout->addStretch(1);
    setLayout(layout);

    connect(addButton, SIGNAL(clicked(bool)), this, SLOT(onAddClicked()));
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

}
