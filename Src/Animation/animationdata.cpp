#include "animationdata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

AnimationData::AnimationData(const QString & fileName)
{
    load(fileName);
}

void AnimationData::save(const QString & fileName) const
{
     QJsonObject obj;
     obj.insert("image", imageName);

     QJsonArray frames;
     for(const auto & f : *this)
     {
         QJsonObject frame;
         frame.insert("left", f.rect.left);
         frame.insert("top", f.rect.top);
         frame.insert("width", f.rect.width);
         frame.insert("height", f.rect.height);
         frame.insert("x", f.offset.x);
         frame.insert("y", f.offset.y);
         frame.insert("time", f.time);
         frames.append(frame);;
     }
     obj.insert("frames", frames);

     QFile file(fileName);
     if(!file.open(QIODevice::WriteOnly))
         return;
     file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
     file.close();
}

void AnimationData::load(const QString & fileName)
{
    clear();

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

    imageName = obj["image"].toString();

    auto frames = obj.find("frames");
    if(frames == obj.end() || !frames->isArray())
        return;

    for(const auto & fObj : frames->toArray())
    {
        if(!fObj.isObject())
            continue;
        auto frame = fObj.toObject();
        Frame f;
        f.offset.x = frame["x"].toInt();
        f.offset.y = frame["y"].toInt();
        f.rect.left = frame["left"].toInt();
        f.rect.top = frame["top"].toInt();
        f.rect.width = frame["width"].toInt();
        f.rect.height = frame["height"].toInt();
        f.time = frame["time"].toDouble();

        push_back(f);
    }
}
