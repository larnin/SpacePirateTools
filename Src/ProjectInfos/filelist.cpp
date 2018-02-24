#include "filelist.h"
#include <QDir>
#include <QDebug>

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
    auto value = m_files.find(key);
    if(value == m_files.end())
        return std::vector<QString>();
    return value->second;
}

std::vector<QString> fileList(const QDir & directory)
{
    std::vector<QString> files;
    for(const auto & e : directory.entryInfoList(QDir::Files))
        files.push_back(e.fileName());
    return files;
}

void FileList::createListFile(const QString &directory)
{
    m_files.clear();

    QDir dir(directory);
    if(!dir.exists())
    {
        qDebug() << "The path `" << directory << "` doesn't exist";
        return;
    }

    for(const auto & e : dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot))
        m_files.emplace(e.baseName(), fileList(e.absoluteDir()));
}
