#include "brushbase.h"

BrushBase::BrushBase(BrushType type)
    : m_brushType(type)
{

}

QJsonObject BrushBase::save() const
{
    QJsonObject obj;
    obj.insert("brushType", static_cast<int>(m_brushType));

    onSave(obj);

    return obj;
}

std::unique_ptr<BrushBase> BrushBase::loadBrush(const QJsonObject & obj)
{
    //todo
    return std::unique_ptr<BrushBase>();
}
