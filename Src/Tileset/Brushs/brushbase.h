#ifndef BRUSHBASE_H
#define BRUSHBASE_H

#include "Tileset/tilecollider.h"
#include "Tileset/tileshape.h"
#include "UI/Tileset/BrushsWindow/brushwindowbase.h"
#include "Scene/Tools/basetilesetscenetool.h"
#include "Scene/Layers/tilesetlayer.h"
#include <QJsonObject>
#include <memory>

enum class BrushType
{
    Random,
    Horizontal,
    Vertical,
    Square,
    Full,
    Pattern,
    Max = Pattern,
};

QString brushTypeToString(BrushType type);
BrushType brushTypeFromString(const QString & s);

struct TileFullInfos
{
    inline TileFullInfos(TileShape _shape, TileCollider _collider, unsigned int _id)
        : shape(_shape), collider(_collider), id(_id) { }
    inline TileFullInfos(TileCollider _collider, unsigned int _id)
        : shape(TileShape::Empty), collider(_collider), id(_id) { }

    TileShape shape;
    TileCollider collider;
    unsigned int id;
};

class BrushBase
{
public:
    QJsonObject save() const;
    virtual ~BrushBase() = default;

    static std::unique_ptr<BrushBase> loadBrush(const QJsonObject & obj);
    static std::unique_ptr<BrushBase> createBrush(BrushType type, const QString & name);

    inline BrushType getBrushType() const {return m_brushType;}
    virtual BrushWindowBase* getBrushWindows() = 0;
    virtual std::unique_ptr<BaseSceneTool> getSceneTool(TilesetLayer & layer) const = 0;

    QString name;

protected:
    BrushBase(BrushType type, const QString & _name);

    virtual void onSave(QJsonObject & obj) const = 0;

private:
    BrushType m_brushType;
};

#endif // BRUSHBASE_H
