#include "scenedata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

SceneData::SceneData(const QString & fileName)
    : color(sf::Color::Black)
    , m_size(10, 10)
{
    load(fileName);
}

void SceneData::save(const QString & fileName) const
{
    QJsonObject obj;

    obj.insert("sx", int(m_size.x));
    obj.insert("sy", int(m_size.y));
    obj.insert("r", int(color.r));
    obj.insert("g", int(color.g));
    obj.insert("b", int(color.b));

    QJsonArray layers;
    for(const auto & l : m_layers)
        layers.append(l->save());
    obj.insert("layers", layers);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void SceneData::load(const QString & fileName)
{
    QFile file(fileName);
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

    m_size = sf::Vector2u(obj["sx"].toInt(), obj["sy"].toInt());

    color = sf::Color(obj["r"].toInt(), obj["g"].toInt(), obj["b"].toInt());

    auto it = obj.find("layers");
    if(it != obj.end() && it->isArray())
    {
        for(const auto & v : it->toArray())
            m_layers.emplace_back(LayerBase::loadLayer(v.toObject()));
    }
}

void SceneData::setSize(const sf::Vector2u & size)
{
    m_size = size;
    for(auto & l : m_layers)
        l->setSize(m_size);
}

void SceneData::addLayer(LayerType type, const QString & name, const sf::Vector2u & size)
{
    m_layers.emplace_back(LayerBase::createLayer(type, name, size));
}

void SceneData::delLayer(unsigned int index)
{
    m_layers.erase(m_layers.begin() + index);
}
