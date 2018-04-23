#ifndef PROJECTINFOS_H
#define PROJECTINFOS_H

#include "filelist.h"
#include "assettype.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include <QString>
#include <vector>

struct ProjectOptions
{
    unsigned int tileSize;
    unsigned int delta;
};

class ProjectInfos
{
public:
    ProjectInfos();

    void loadProject(const QString & projectDirectory);

    inline bool projectLoaded() const { return m_projectLoaded; }
    std::vector<QString> fileInfos(AssetType type) const;
    inline const QString & projectDirectory() const { return m_projectDirectory; }
    void reloadFileList();

    void save();
    inline ProjectOptions & options() {return m_options;}

    static ProjectInfos & instance();

private:
    void load();
    void onSave(const SaveEvent &);

    static ProjectInfos m_instance;

    bool m_projectLoaded;
    QString m_projectDirectory;
    FileList m_fileList;

    ProjectOptions m_options;

    EventHolder<SaveEvent> m_saveHolder;
};

#endif // PROJECTINFOS_H
