#include "projectinfos.h"
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <algorithm>

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

bool ProjectInfos::fileExist(const QString & name, AssetType type) const
{
    auto list = fileInfos(type);
    return std::find_if(list.begin(), list.end(), [name](const auto & value){return value == name;}) != list.end();
}

QString ProjectInfos::fullFileName(const QString & name, AssetType type) const
{
    return projectDirectory() + "/" + assetTypeToString(type) + "/" + name;
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

    QJsonArray colliders;
    for(const auto & c : m_options.colliderLayers)
    {
        QJsonObject cObj;
        cObj.insert("r", c.color.r);
        cObj.insert("g", c.color.g);
        cObj.insert("b", c.color.b);
        cObj.insert("name", c.name);
        QJsonArray collisions;
        for(const auto i : c.layerCollisions)
            collisions.append(int(i));
        cObj.insert("l", collisions);
        colliders.append(cObj);
    }
    obj.insert("colliders", colliders);

    QFile file(m_projectDirectory + "/" + optionFilename);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void ProjectInfos::load()
{
    m_options = ProjectOptions();

    QFile file(m_projectDirectory + "/" + optionFilename);
    if(!file.exists() || !file.open(QIODevice::ReadOnly))
    {
        validData();
        return;
    }

    QJsonParseError error;
    QJsonDocument doc(QJsonDocument::fromJson(file.readAll(), &error));
    file.close();
    if(error.error != QJsonParseError::NoError || !doc.isObject())
    {
        validData();
        return;
    }

    QJsonObject obj(doc.object());

    for(const auto & c : obj["colliders"].toArray())
    {
        auto cObj = c.toObject();
        ColliderLayer layer;
        layer.color.r = cObj["r"].toInt();
        layer.color.g = cObj["g"].toInt();
        layer.color.b = cObj["b"].toInt();
        layer.name = cObj["name"].toString();
        for(const auto & v : cObj["l"].toArray())
            layer.layerCollisions.push_back(v.toInt());
        m_options.colliderLayers.push_back(layer);
    }

    validData();
}

void ProjectInfos::validData()
{
    if(m_options.colliderLayers.empty())
        m_options.colliderLayers.push_back({"Default", sf::Color::Red, {}});
}

void ProjectInfos::onSave(const SaveEvent &)
{
    save();
}
