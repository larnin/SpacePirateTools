#ifndef TILECOLLIDER_H
#define TILECOLLIDER_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Color.hpp>
#include <QString>

enum class TileColliderType : unsigned int
{
    Empty,
    Full,
    Triangle,
    Half,
    Quarter,
    ThreeQuarter,
    CentredHalf,
    Cross,
    TShape,
    CentredCorner,
    Max = CentredCorner
};

QString tileColliderTypeToString(TileColliderType type);
TileColliderType tileColliderTypeFromString(const QString & s);

enum class TileColliderRotation : unsigned int
{
    R_0,
    R_90,
    R180,
    R270
};

/// int value
/// [0] xFlipped
/// [1] yFlipped
/// [2-3] rotation
/// [4-15] colliderType
/// [16-32] collisionLayer

struct TileCollider
{
    TileCollider(unsigned int value = 0);
    unsigned int toInt() const;
    void fromInt(unsigned int value);

    sf::VertexArray drawShape(const sf::Color & color, const sf::Vector2f & offset, float scale) const;
    void drawShape(const sf::Color & color, const sf::Vector2f & offset, float scale, sf::VertexArray & outarray) const;

    TileColliderType type;
    TileColliderRotation rotation;
    bool xFlipped;
    bool yFlipped;
    int collisionLayer;

private:
    static sf::VertexArray drawFull();
    static sf::VertexArray drawTriangle();
    static sf::VertexArray drawHalf();
    static sf::VertexArray drawQuarter();
    static sf::VertexArray drawThreeQuarter();
    static sf::VertexArray drawCentredHalf();
    static sf::VertexArray drawCross();
    static sf::VertexArray drawTShape();
    static sf::VertexArray drawCentredCorner();
};

#endif // TILECOLLIDER_H
