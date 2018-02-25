#ifndef CONFIGS_H
#define CONFIGS_H

#include "Events/Event.h"
#include "Events/Args/projectloadedevent.h"
#include <QString>
#include <vector>

struct ConfigsDatas
{
    std::vector<QString> lastProjects;
};

class Configs
{
public:
    Configs();
    void save();

    inline const std::vector<QString> & lastProjects() const {return m_datas.lastProjects;}

    static Configs & instance();

private:
    void load();
    void onProjectLoaded(ProjectLoadedEvent e);

    static Configs m_instance;

    ConfigsDatas m_datas;
    EventHolder<ProjectLoadedEvent> m_projectLoadedHolder;
};

#endif // CONFIGS_H
