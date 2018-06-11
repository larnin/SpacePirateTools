#include "scenelayer.h"

#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonArray>

SceneLayer::SceneLayer(const QJsonObject & obj)
{
    load(obj);
}

QJsonObject SceneLayer::save() const
{

}

void SceneLayer::load(const QJsonObject & obj)
{



}
