#ifndef PROJECTINFOS_H
#define PROJECTINFOS_H

#include "filelist.h"
#include "assettype.h"
#include <QString>
#include <vector>

class ProjectInfos
{
public:
    ProjectInfos();

    void loadProject(const QString & projectDirectory);

    inline bool projectLoaded() const { return m_projectLoaded; }
    std::vector<QString> fileInfos(AssetType type) const;

    static ProjectInfos & instance();

private:
    static ProjectInfos m_instance;

    bool m_projectLoaded;
    QString m_projectDirectory;
    FileList m_fileList;
};

#endif // PROJECTINFOS_H
