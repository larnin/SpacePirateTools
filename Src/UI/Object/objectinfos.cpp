#include "objectinfos.h"

ObjectInfos::ObjectInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName)
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

}

void ObjectInfos::addPropertyWidget(ObjectProperty & p)
{

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
