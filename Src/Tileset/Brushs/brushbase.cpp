#include "brushbase.h"
#include "brushrandom.h"
#include "brushpatern.h"
#include <cassert>

QString brushTypeToString(BrushType type)
{
    switch(type)
    {
    case BrushType::Random:
        return "Random";
    case BrushType::Horizontal:
        return "Horisontal";
    case BrushType::Vertical:
        return "Vertical";
    case BrushType::Square:
        return "Rectangle";
    case BrushType::Full:
        return "Complet";
    case BrushType::Pattern:
        return "Pattern";
    }
    return "";
}


BrushType brushTypeFromString(const QString & s)
{
    for(unsigned int i(0) ; i < static_cast<unsigned int>(BrushType::Max) ; i++)
        if(brushTypeToString(static_cast<BrushType>(i)) == s)
            return static_cast<BrushType>(i);
    assert(false);

    return BrushType::Pattern;
}

BrushBase::BrushBase(BrushType type, const QString & _name)
    : name(_name)
    , m_brushType(type)
{

}

QJsonObject BrushBase::save() const
{
    QJsonObject obj;
    obj.insert("brushType", static_cast<int>(m_brushType));
    obj.insert("name", name);

    onSave(obj);

    return obj;
}

std::unique_ptr<BrushBase> BrushBase::loadBrush(const QJsonObject & obj)
{
    BrushType type = static_cast<BrushType>(obj["brushType"].toInt());
    QString name(obj["name"].toString());

    switch(type)
    {
    case BrushType::Random:
        return std::make_unique<BrushRandom>(obj, name);
    case BrushType::Pattern:
        return std::make_unique<BrushPatern>(obj, name);
    default:
        break;
    }

    assert(false);

    return std::unique_ptr<BrushBase>();
}


std::unique_ptr<BrushBase> BrushBase::createBrush(BrushType type, const QString & name)
{
    switch(type)
    {
    case BrushType::Random:
        return std::make_unique<BrushRandom>(name);
    case BrushType::Pattern:
        return std::make_unique<BrushPatern>(name, sf::Vector2u(1, 1));

    default:
        break;
    }

    assert(false);

    return std::unique_ptr<BrushBase>();
}
