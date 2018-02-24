#ifndef FILELIST_H
#define FILELIST_H

#include <vector>
#include <map>
#include <QString>

class FileList
{
public:
    FileList() = default;
    FileList(const QString & directory);

    std::vector<QString> keys() const;
    const std::vector<QString> &files(const QString & key) const;

private:
    void createListFile(const QString &directory);

    std::map<QString, std::vector<QString>> m_files;
};

#endif // FILELIST_H
