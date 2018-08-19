#include "filelist.h"
#include <QDir>

FileList::FileList(const QString &directory)
{
    createListFile(directory);
}

std::vector<QString> FileList::keys() const
{
    std::vector<QString> k;
    for(const auto & entry : m_files)
        k.push_back(entry.first);
    return k;
}

const std::vector<QString> & FileList::files(const QString & key) const
{
    static const std::vector<QString> defaultValue;
    auto value = m_files.find(key);
    if(value == m_files.end())
        return defaultValue;
    return value->second;
}

namespace
{
std::vector<QString> fileList(const QDir & directory)
{
    std::vector<QString> files;
    for(const auto & e : directory.entryInfoList(QDir::Files))
        files.push_back(e.fileName());
    return files;
}
}

void FileList::createListFile(const QString &directory)
{
    m_files.clear();

    QDir dir(directory);
    if(!dir.exists())
        return;

    for(const auto & e : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
        m_files.emplace(e.baseName(), fileList(e.absoluteFilePath()));
}
