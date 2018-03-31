#ifndef BRUSHBASE_H
#define BRUSHBASE_H

#include <QJsonObject>
#include <memory>

enum class BrushType
{
    Random,
    Horizontal,
    Vertical,
    Square,
    Full,
    Patern,
};

class BrushBase
{
public:
    QJsonObject save() const;

    static std::unique_ptr<BrushBase> loadBrush(const QJsonObject & obj);

    inline BrushType getBrushType() const {return m_brushType;}

protected:
    BrushBase(BrushType type);

    virtual void onSave(QJsonObject & obj) const = 0;

private:
    BrushType m_brushType;
};

#endif // BRUSHBASE_H
