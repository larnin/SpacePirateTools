#include "tilecollider.h"
#include "enumclasshash.h"
#include "enumiterators.h"
#include <unordered_map>
#include <functional>
#include <cassert>

QString tileColliderTypeToString(TileColliderType type)
{
    switch(type)
    {
    case TileColliderType::Empty:
        return "Empty";
    case TileColliderType::Full:
        return "Full";
    case TileColliderType::Triangle:
        return "Triangle";
    case TileColliderType::Half:
        return "Half";
    case TileColliderType::Quarter:
        return "Quarter";
    case TileColliderType::ThreeQuarter:
        return "Tree quarter";
    case TileColliderType::CentredHalf:
        return "Centred half";
    case TileColliderType::Cross:
        return "Cross";
    case TileColliderType::TShape:
        return "T shape";
    case TileColliderType::CentredCorner:
        return "Centred corner";
    default:
        break;
    }
    assert(false);
    return "";
}

TileColliderType tileColliderTypeFromString(const QString & s)
{
    for(auto t : TileColliderType::Max)
        if(tileColliderTypeToString(t) == s)
            return t;
    assert(false);
    return TileColliderType::Max;
}

TileCollider::TileCollider(unsigned int value)
{
    fromInt(value);
}

unsigned int TileCollider::toInt() const
{
    int value(0);
    if(xFlipped)
        value += 1<<0;
    if(yFlipped)
        value += 1<<1;
    value += static_cast<unsigned int>(rotation) << 2;
    value += static_cast<unsigned int>(type) << 4;
    value += collisionLayer << 16;

    return value;
}

void TileCollider::fromInt(unsigned int value)
{
    xFlipped = (value & 0b1) > 0;
    yFlipped = (value & 0b10) > 0;
    rotation = static_cast<TileColliderRotation>((value & 0b1100) >> 2);
    type = static_cast<TileColliderType>((value & 0xFFF0) >> 4);
    collisionLayer = (value & 0xFFFF0000) >> 16;
}

sf::VertexArray TileCollider::drawShape(const sf::Color & color, const sf::Vector2f & offset, float scale) const
{
    std::unordered_map<TileColliderType, std::function<sf::VertexArray()>, EnumClassHash> funcs{
        {TileColliderType::Full, &drawFull},
        {TileColliderType::Triangle, &drawTriangle},
        {TileColliderType::Half, &drawHalf},
        {TileColliderType::Quarter, &drawQuarter},
        {TileColliderType::ThreeQuarter, &drawThreeQuarter},
        {TileColliderType::CentredHalf, &drawCentredHalf},
        {TileColliderType::Cross, &drawCross},
        {TileColliderType::TShape, &drawTShape},
        {TileColliderType::CentredCorner, &drawCentredCorner}
    };

    auto it = funcs.find(type);
    if(it == funcs.end())
        return sf::VertexArray();

    sf::VertexArray array = it->second();

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
    {
        for(unsigned int j(0) ; j < static_cast<unsigned int>(rotation) ; j++)
        {
            float temp = array[i].position.x;
            array[i].position.x = -array[i].position.y;
            array[i].position.y = temp;
        }

        if(xFlipped)
            array[i].position.x *= -1;
        if(yFlipped)
            array[i].position.y *= -1;

        array[i].position *= scale;
        array[i].position += offset;
        array[i].color = color;
    }
    return array;
}

void TileCollider::drawShape(const sf::Color & color, const sf::Vector2f & offset, float scale, sf::VertexArray & outarray) const
{
    assert(outarray.getPrimitiveType() == sf::Lines);

    auto array = drawShape(color, offset, scale);

    for(unsigned int i(0) ; i < array.getVertexCount() ; i++)
        outarray.append(array[i]);
}

sf::VertexArray TileCollider::drawFull()
{
    sf::VertexArray array(sf::Lines, 8);

    array[0].position = sf::Vector2f(-0.5f, -0.5f);
    array[1].position = sf::Vector2f( 0.5f, -0.5f);
    array[2].position = sf::Vector2f( 0.5f, -0.5f);
    array[3].position = sf::Vector2f( 0.5f,  0.5f);
    array[4].position = sf::Vector2f( 0.5f,  0.5f);
    array[5].position = sf::Vector2f(-0.5f,  0.5f);
    array[6].position = sf::Vector2f(-0.5f,  0.5f);
    array[7].position = sf::Vector2f(-0.5f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawTriangle()
{
    sf::VertexArray array(sf::Lines, 6);

    array[0].position = sf::Vector2f(-0.5f, -0.5f);
    array[1].position = sf::Vector2f( 0.5f, -0.5f);
    array[2].position = sf::Vector2f( 0.5f, -0.5f);
    array[3].position = sf::Vector2f( 0.5f,  0.5f);
    array[4].position = sf::Vector2f( 0.5f,  0.5f);
    array[5].position = sf::Vector2f(-0.5f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawHalf()
{
    sf::VertexArray array(sf::Lines, 8);

    array[0].position = sf::Vector2f(-0.5f, -0.5f);
    array[1].position = sf::Vector2f( 0.0f, -0.5f);
    array[2].position = sf::Vector2f( 0.0f, -0.5f);
    array[3].position = sf::Vector2f( 0.0f,  0.5f);
    array[4].position = sf::Vector2f( 0.0f,  0.5f);
    array[5].position = sf::Vector2f(-0.5f,  0.5f);
    array[6].position = sf::Vector2f(-0.5f,  0.5f);
    array[7].position = sf::Vector2f(-0.5f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawQuarter()
{
    sf::VertexArray array(sf::Lines, 8);

    array[0].position = sf::Vector2f(-0.5f, -0.5f);
    array[1].position = sf::Vector2f( 0.0f, -0.5f);
    array[2].position = sf::Vector2f( 0.0f, -0.5f);
    array[3].position = sf::Vector2f( 0.0f,  0.0f);
    array[4].position = sf::Vector2f( 0.0f,  0.0f);
    array[5].position = sf::Vector2f(-0.5f,  0.0f);
    array[6].position = sf::Vector2f(-0.5f,  0.0f);
    array[7].position = sf::Vector2f(-0.5f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawThreeQuarter()
{
    sf::VertexArray array(sf::Lines, 12);

    array[0].position = sf::Vector2f(-0.5f, -0.5f);
    array[1].position = sf::Vector2f( 0.0f, -0.5f);
    array[2].position = sf::Vector2f( 0.0f, -0.5f);
    array[3].position = sf::Vector2f( 0.0f,  0.0f);
    array[4].position = sf::Vector2f( 0.0f,  0.0f);
    array[5].position = sf::Vector2f( 0.5f,  0.0f);
    array[6].position = sf::Vector2f( 0.5f,  0.0f);
    array[7].position = sf::Vector2f( 0.5f,  0.5f);
    array[8].position = sf::Vector2f( 0.5f,  0.5f);
    array[9].position = sf::Vector2f(-0.5f,  0.5f);
    array[10].position = sf::Vector2f(-0.5f,  0.5f);
    array[11].position = sf::Vector2f(-0.5f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawCentredHalf()
{
    sf::VertexArray array(sf::Lines, 8);

    array[0].position = sf::Vector2f(-0.25f, -0.5f);
    array[1].position = sf::Vector2f( 0.25f, -0.5f);
    array[2].position = sf::Vector2f( 0.25f, -0.5f);
    array[3].position = sf::Vector2f( 0.25f,  0.5f);
    array[4].position = sf::Vector2f( 0.25f,  0.5f);
    array[5].position = sf::Vector2f(-0.25f,  0.5f);
    array[6].position = sf::Vector2f(-0.25f,  0.5f);
    array[7].position = sf::Vector2f(-0.25f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawCross()
{
    sf::VertexArray array(sf::Lines, 24);

    array[0].position = sf::Vector2f(-0.25f, -0.5f);
    array[1].position = sf::Vector2f( 0.25f, -0.5f);
    array[2].position = sf::Vector2f( 0.25f, -0.5f);
    array[3].position = sf::Vector2f( 0.25f, -0.25f);
    array[4].position = sf::Vector2f( 0.25f, -0.25f);
    array[5].position = sf::Vector2f( 0.5f, -0.25f);
    array[6].position = sf::Vector2f( 0.5f, -0.25f);
    array[7].position = sf::Vector2f( 0.5f,  0.25f);
    array[8].position = sf::Vector2f( 0.5f,  0.25f);
    array[9].position = sf::Vector2f( 0.25f, 0.25f);
    array[10].position = sf::Vector2f( 0.25f, 0.25f);
    array[11].position = sf::Vector2f( 0.25f,  0.5f);
    array[12].position = sf::Vector2f( 0.25f,  0.5f);
    array[13].position = sf::Vector2f(-0.25f,  0.5f);
    array[14].position = sf::Vector2f(-0.25f,  0.5f);
    array[15].position = sf::Vector2f(-0.25f,  0.25f);
    array[16].position = sf::Vector2f(-0.25f,  0.25f);
    array[17].position = sf::Vector2f(-0.5f,  0.25f);
    array[18].position = sf::Vector2f(-0.5f,  0.25f);
    array[19].position = sf::Vector2f(-0.5f, -0.25f);
    array[20].position = sf::Vector2f(-0.5f, -0.25f);
    array[21].position = sf::Vector2f(-0.25f, -0.25f);
    array[22].position = sf::Vector2f(-0.25f, -0.25f);
    array[23].position = sf::Vector2f(-0.25f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawTShape()
{
    sf::VertexArray array(sf::Lines, 16);

    array[0].position = sf::Vector2f(-0.25f, -0.5f);
    array[1].position = sf::Vector2f( 0.25f, -0.5f);
    array[2].position = sf::Vector2f( 0.25f, -0.5f);
    array[3].position = sf::Vector2f( 0.25f, -0.25f);
    array[4].position = sf::Vector2f( 0.25f, -0.25f);
    array[5].position = sf::Vector2f( 0.5f, -0.25f);
    array[6].position = sf::Vector2f( 0.5f, -0.25f);
    array[7].position = sf::Vector2f( 0.5f,  0.25f);
    array[8].position = sf::Vector2f( 0.5f,  0.25f);
    array[9].position = sf::Vector2f( 0.25f, 0.25f);
    array[10].position = sf::Vector2f( 0.25f, 0.25f);
    array[11].position = sf::Vector2f( 0.25f,  0.5f);
    array[12].position = sf::Vector2f( 0.25f,  0.5f);
    array[13].position = sf::Vector2f(-0.25f,  0.5f);
    array[14].position = sf::Vector2f(-0.25f,  0.5f);
    array[15].position = sf::Vector2f(-0.25f, -0.5f);

    return array;
}

sf::VertexArray TileCollider::drawCentredCorner()
{
    sf::VertexArray array(sf::Lines, 12);

    array[0].position = sf::Vector2f(-0.25f, -0.5f);
    array[1].position = sf::Vector2f( 0.25f, -0.5f);
    array[2].position = sf::Vector2f( 0.25f, -0.5f);
    array[3].position = sf::Vector2f( 0.25f,  -0.25f);
    array[4].position = sf::Vector2f( 0.25f,  -0.25f);
    array[5].position = sf::Vector2f( 0.5f,  -0.25f);
    array[6].position = sf::Vector2f( 0.5f,  -0.25f);
    array[7].position = sf::Vector2f( 0.5f,  0.25f);
    array[8].position = sf::Vector2f( 0.5f,  0.25f);
    array[9].position = sf::Vector2f(-0.25f,  0.25f);
    array[10].position = sf::Vector2f(-0.25f,  0.25f);
    array[11].position = sf::Vector2f(-0.25f, -0.5f);

    return array;
}
