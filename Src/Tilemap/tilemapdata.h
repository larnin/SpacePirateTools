#ifndef TILEMAPDATA_H
#define TILEMAPDATA_H

#include "matrix.h"
#include "tileinfos.h"
#include <QString>

class TilemapData
{
public:
    TilemapData(const sf::Vector2u & size, const TileInfos & defaultTile = {});
    TilemapData(const QString & fileName);

    void save(const QString & fileName) const;

    QString textureName;
    QString brushName;
    Matrix<TileInfos> tiles;
    unsigned int tileSize;
    unsigned int tileDelta;

private:
    void load(const QString & fileName);
};

#endif // TILEMAPDATA_H
