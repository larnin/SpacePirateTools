#ifndef BRUSHTILED_H
#define BRUSHTILED_H

#include "brushbase.h"
#include <vector>

class BrushTiled : public BrushBase
{
public:
    virtual ~BrushTiled() = default;

    inline std::vector<TileShape> validShapes() const { return getShapes(getBrushType()); }
    TileFullInfos & tile(TileShape shape);
    TileFullInfos const & tile(TileShape shape) const;

protected:
    BrushTiled(const QJsonObject & obj, const QString & _name, BrushType type);
    BrushTiled(const QString & _name, BrushType type);

    void onSave(QJsonObject & obj) const override;

private:
    static std::vector<TileShape> getShapes(BrushType type);

    std::vector<TileFullInfos> m_tiles;
};

#endif // BRUSHTILED_H
