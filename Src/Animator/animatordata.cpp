#include "animatordata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonArray>

AnimatorData::AnimatorData(const QString & fileName)
    : startIndex(0)
{
    load(fileName);
}

void AnimatorData::save(const QString & fileName) const
{
    QJsonObject obj;
    obj.insert("start", int(startIndex));

    QJsonArray statesArray;
    for(const auto & s : states)
        statesArray.append(s.save());
    obj.insert("states", statesArray);

    QJsonArray transitionsArray;
    for(const auto & t : transitions)
        transitionsArray.append(t.save());
    obj.insert("transitions", transitionsArray);

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly))
        return;
    file.write(QJsonDocument(obj).toJson(QJsonDocument::Compact));
    file.close();
}

void AnimatorData::load(const QString & fileName)
{
    states.clear();
    transitions.clear();

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

    startIndex = obj["start"].toInt();

    auto statesIt = obj.find("states");
    if(statesIt != obj.end() && statesIt->isArray())
    {
        const auto & statesArray = statesIt->toArray();
        for(const auto & v : statesArray)
            states.push_back(AnimatorState(v.toObject()));
    }

    auto transitionsIt = obj.find("transitions");
    if(transitionsIt != obj.end() && transitionsIt->isArray())
    {
        const auto & transitionsArray = transitionsIt->toArray();
        for(const auto & v : transitionsArray)
        {
            try
            {
                AnimatorTransition t(v.toObject());
                transitions.push_back(std::move(t));
            }
            catch(const std::exception &) {}
        }
    }

}
