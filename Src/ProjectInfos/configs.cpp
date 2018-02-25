#include "configs.h"
#include "projectinfos.h"
#include <algorithm>

Configs Configs::m_instance;

Configs::Configs()
    : m_projectLoadedHolder(Event<ProjectLoadedEvent>::connect([this](const auto & e){onProjectLoaded(e);}))
{
    load();
}

Configs & Configs::instance()
{
    return m_instance;
}

void Configs::save()
{

}

void Configs::load()
{

}

void Configs::onProjectLoaded(ProjectLoadedEvent)
{
    m_datas.lastProjects.erase(std::remove_if(m_datas.lastProjects.begin(), m_datas.lastProjects.end(),
                                              [](const auto & v){return v == ProjectInfos::instance().projectDirectory();})
                               , m_datas.lastProjects.end());

    m_datas.lastProjects.insert(m_datas.lastProjects.begin(), ProjectInfos::instance().projectDirectory());
}
