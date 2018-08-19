#include "brushtiled.h"
#include "UI/Tileset/BrushsWindow/brushwindowtiled.h"
#include <QJsonArray>
#include <cassert>
#include <algorithm>

BrushTiled::BrushTiled(const QJsonObject & obj, const QString & _name, BrushType type)
    : BrushBase(type, _name)
{
    std::vector<TileFullInfos> tiles;
    auto tIt = obj.find("tiles");
    if(tIt != obj.end() && tIt->isArray())
    {
        for(const auto value : tIt->toArray())
        {
            auto tObj = value.toObject();
            tiles.emplace_back(static_cast<TileShape>(tObj["s"].toInt()), TileCollider(tObj["c"].toInt()), tObj["id"].toInt());
        }
    }

    for(auto shape : getShapes(type))
    {
        auto it = std::find_if(tiles.begin(), tiles.end(), [shape](const auto & t){ return t.shape == shape;});
        if(it == tiles.end())
            m_tiles.emplace_back(shape, TileCollider(0), 0);
        else m_tiles.push_back(*it);
    }
}

BrushTiled::BrushTiled(const QString & _name, BrushType type)
    : BrushBase(type, _name)
{
    for(auto shape : getShapes(type))
        m_tiles.emplace_back(shape, TileCollider(0), 0);
}

void BrushTiled::onSave(QJsonObject & obj) const
{
    QJsonArray array;
    for(const auto & t : m_tiles)
    {
        QJsonObject tObj;
        tObj.insert("id", static_cast<int>(t.id));
        tObj.insert("c", static_cast<int>(t.collider.toInt()));
        tObj.insert("s", static_cast<int>(t.shape));
        array.append(tObj);
    }
    obj.insert("tiles", array);
}

TileFullInfos & BrushTiled::tile(TileShape shape)
{
    auto it = std::find_if(m_tiles.begin(), m_tiles.end(), [shape](const auto & value){ return value.shape == shape;});
    assert(it != m_tiles.end());
    return *it;
}

TileFullInfos const & BrushTiled::tile(TileShape shape) const
{
    auto it = std::find_if(m_tiles.begin(), m_tiles.end(), [shape](const auto & value){ return value.shape == shape;});
    assert(it != m_tiles.end());
    return *it;
}

std::vector<TileShape> BrushTiled::getShapes(BrushType type)
{
    if(type == BrushType::Horizontal)
        return
        {
            TileShape::Full,
            TileShape::Left3,
            TileShape::Horizontal,
            TileShape::Right3,
        };

    if(type == BrushType::Vertical)
        return
        {
            TileShape::Full,
            TileShape::Top3,
            TileShape::Vertical,
            TileShape::Down3,
        };

    if(type == BrushType::Square)
        return
        {
            TileShape::Empty,
            TileShape::Left3,
            TileShape::Horizontal,
            TileShape::Right3,
            TileShape::Top3,
            TileShape::Vertical,
            TileShape::Down3,
            TileShape::Full,
            TileShape::TopLeft,
            TileShape::TopRight,
            TileShape::DownLeft,
            TileShape::DownRight,
            TileShape::Left,
            TileShape::Right,
            TileShape::Top,
            TileShape::Down,
        };

    if(type == BrushType::Full)
        return
        {
            TileShape::Empty,
            TileShape::Full,
            TileShape::Left3,
            TileShape::Right3,
            TileShape::Top3,
            TileShape::Down3,
            TileShape::Horizontal,
            TileShape::Vertical,
            TileShape::TopLeft,
            TileShape::TopRight,
            TileShape::DownLeft,
            TileShape::DownRight,
            TileShape::Left,
            TileShape::Right,
            TileShape::Top,
            TileShape::Down,
            TileShape::QuadCorners,
            TileShape::TopLeftCorners3,
            TileShape::TopRightCorners3,
            TileShape::DownLeftCorners3,
            TileShape::DownRightCorners3,
            TileShape::DiagonalTopLeft,
            TileShape::DiagonalTopRight,
            TileShape::LeftCorners,
            TileShape::RightCorners,
            TileShape::TopCorners,
            TileShape::DownCorners,
            TileShape::TopLeftCorner,
            TileShape::TopRightCorner,
            TileShape::DownLeftCorner,
            TileShape::DownRightCorner,
            TileShape::TopLeftWithCorner,
            TileShape::TopRightWithCorner,
            TileShape::DownLeftWithCorner,
            TileShape::DownRightWithCorner,
            TileShape::LeftCorners2,
            TileShape::RightCorners2,
            TileShape::TopCorners2,
            TileShape::DownCorners2,
            TileShape::LeftCornerTop,
            TileShape::RightCornerTop,
            TileShape::TopCornerTop,
            TileShape::DownCornerTop,
            TileShape::LeftCornerDown,
            TileShape::RightCornerDown,
            TileShape::TopCornerDown,
            TileShape::DownCornerDown,
        };

    assert(false);
    return {};
}

 BrushWindowBase* BrushTiled::getBrushWindows()
 {
     return new BrushWindowTiled(this);
 }
