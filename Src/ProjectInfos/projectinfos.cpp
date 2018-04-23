#include "projectinfos.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>

const QString optionFilename = "options.json";

ProjectInfos ProjectInfos::m_instance;

ProjectInfos::ProjectInfos()
    : m_projectLoaded(false)
    , m_saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
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

    load();
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

void ProjectInfos::save()
{
    if(!m_projectLoaded)
        return;

    QJsonObject obj;
    obj.insert("tilesize", int(m_options.tileSize));
    obj.insert("delta", int(m_options.delta));

    QFile file(m_projectDirectory + "/" + optionFilename);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void ProjectInfos::load()
{
    QFile file(m_projectDirectory + "/" + optionFilename);
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

    m_options.tileSize = obj["tilesize"].toInt();
    m_options.delta = obj["delta"].toInt();
}

void ProjectInfos::onSave(const SaveEvent &)
{
    save();
}
