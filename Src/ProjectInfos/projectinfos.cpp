#include "projectinfos.h"

ProjectInfos ProjectInfos::m_instance;

ProjectInfos::ProjectInfos()
    : m_projectLoaded(false)
{

}

ProjectInfos & ProjectInfos::instance()
{
    return m_instance;
}

void ProjectInfos::loadProject(const QString & projectDirectory)
{
    m_projectDirectory = projectDirectory;
    m_projectLoaded = true;
    m_fileList = FileList(projectDirectory);
}

std::vector<QString> ProjectInfos::fileInfos(AssetType type) const
{
    if(!m_projectLoaded)
        return {};

    const auto & files = m_fileList.files(assetTypeToString(type));
    if(files.empty())
        return {};

    std::vector<QString> validFiles;
    auto extension = assetTypeExtension(type);
    for(const auto & f : files)
        if(f.endsWith("." + extension))
            validFiles.push_back(f);

    return validFiles;
}

void ProjectInfos::reloadFileList()
{
    m_fileList = FileList(m_projectDirectory);
}
