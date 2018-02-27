#include "configs.h"
#include "projectinfos.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <algorithm>

const QString configsFilename("configs.json");

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
    QJsonObject obj;

    QJsonArray projects;
    for(const auto & p : m_datas.lastProjects)
        projects.append(p);

    obj.insert("LastProjects", projects);

    QFile file(configsFilename);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void Configs::load()
{
    m_datas = ConfigsDatas();

    QFile file(configsFilename);
    if(!file.exists())
        return;
    if(!file.open(QIODevice::ReadOnly))
        return;

    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &error));
    file.close();
    if(error.error != QJsonParseError::NoError)
        return;
    if(!doc.isObject())
        return;

    QJsonObject obj(doc.object());
    auto projects = obj.find("LastProjects");
    if(projects != obj.end() && projects->isArray())
        for(const auto & item : projects->toArray())
            m_datas.lastProjects.push_back(item.toString());
}

void Configs::onProjectLoaded(ProjectLoadedEvent)
{
    m_datas.lastProjects.erase(std::remove_if(m_datas.lastProjects.begin(), m_datas.lastProjects.end(),
                                              [](const auto & v){return v == ProjectInfos::instance().projectDirectory();})
                               , m_datas.lastProjects.end());

    m_datas.lastProjects.insert(m_datas.lastProjects.begin(), ProjectInfos::instance().projectDirectory());
}
