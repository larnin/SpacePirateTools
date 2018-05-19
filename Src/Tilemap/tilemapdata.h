#ifndef TILEMAPDATA_H
#define TILEMAPDATA_H

#include "ressource.h"
#include "matrix.h"
#include "Tileset/tilecollider.h"
#include <QString>

struct TileInfos
{
    unsigned int id = 0;
    TileCollider collider;
};

class TilemapData
{
public:
    TilemapData(const sf::Vector2u & size, const TileInfos & defaultTile = {});
    TilemapData(const QString & fileName);

    void save(const QString & fileName) const;

    QString textureName;
    Matrix<TileInfos> tiles;
    sf::Vector2u tileSize;

private:
    void load(const QString & fileName);
};

#endif // TILEMAPDATA_H
