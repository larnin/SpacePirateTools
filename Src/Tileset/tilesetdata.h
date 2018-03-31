#ifndef TILESETDATA_H
#define TILESETDATA_H

#include "Brushs/brushbase.h"
#include <QString>
#include <memory>
#include <vector>

class TilesetData
{
public:
    TilesetData() = default;
    TilesetData(const QString & fileName);
    void save(const QString & fileName);

    QString imageName;
    unsigned int delta;
    std::vector<std::unique_ptr<BrushBase>> brushs;

private:
    void load(const QString & fileName);
};

#endif // TILESETDATA_H
