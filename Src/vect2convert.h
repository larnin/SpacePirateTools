#ifndef VECT2CONVERT_H
#define VECT2CONVERT_H

#include <SFML/System/Vector2.hpp>
#include <cmath>

inline float norm(const sf::Vector2f & vect)
{
    return sqrt(vect.x*vect.x +vect.y*vect.y);
}

inline sf::Vector2f normalize(const sf::Vector2f & vect)
{
    return vect/norm(vect);
}

inline float dot(const sf::Vector2f & a, const sf::Vector2f & b)
{
    return a.x*b.x + a.y*b.y;
}

inline float angle(const sf::Vector2f & vect)
{
    return atan2(vect.y,vect.x);
}

inline float angle(const sf::Vector2f &vect1, const sf::Vector2f & vect2)
{
    return std::acos(dot(normalize(vect1), normalize(vect2)));
}

inline float signedAngle(const sf::Vector2f &vect1, const sf::Vector2f & vect2)
{
    return angle(vect2) - angle(vect1);
}

inline float normSqr(const sf::Vector2f & vect)
{
    return vect.x*vect.x + vect.y*vect.y;
}

inline sf::Vector2f toVect(float norm, float angle)
{
    return sf::Vector2f(cos(angle)*norm, sin(angle)*norm);
}

inline sf::Vector2f rotate(const sf::Vector2f & vect, float rotateAngle)
{
    return toVect(norm(vect), angle(vect) + rotateAngle);
}

inline sf::Vector2f ortho(const sf::Vector2f & v)
{
    return sf::Vector2f(v.y, -v.x);
}

inline bool isLeft(const sf::Vector2f & p1, const sf::Vector2f & p2, const sf::Vector2f & pos)
{
    return dot(p2 - p1, ortho(pos - p2)) > 0;
}

inline bool isRight(const sf::Vector2f &p1, const sf::Vector2f &p2, const sf::Vector2f & pos)
{
    return dot(p2 - p1, ortho(pos - p2)) < 0;
}

constexpr float radToDeg = 180.0f / 3.14159f;
inline float toDeg(float a)
{
    return a * radToDeg;
}

inline float toRad(float a)
{
    return a / radToDeg;
}

#endif // VECT2CONVERT_H
