#ifndef BRUSHPATERN_H
#define BRUSHPATERN_H

#include "brushbase.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

class BrushPatern : public BrushBase
{
public:
    BrushPatern(const QJsonObject & obj, const QString & _name);
    BrushPatern(const QString & _name, const sf::Vector2u &size, TileFullInfos defaultTile = {TileCollider(0), 0});

    inline sf::Vector2u getSize() const { return m_size; }
    void setSize(const sf::Vector2u & size, TileFullInfos defaultTile = {TileCollider(0), 0});

    TileFullInfos & operator[](const sf::Vector2u & pos);
    TileFullInfos const & operator [](const sf::Vector2u & pos) const;

    BrushWindowBase* getBrushWindows() override;

protected:
    void onSave(QJsonObject & obj) const override;

private:
    unsigned int posToIndex(const sf::Vector2u & pos) const;

    std::vector<TileFullInfos> m_tiles;
    sf::Vector2u m_size;
};

#endif // BRUSHPATERN_H
