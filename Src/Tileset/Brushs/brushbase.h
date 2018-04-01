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
    Pattern,
    Max = Pattern,
};

QString brushTypeToString(BrushType type);
BrushType brushTypeFromString(const QString & s);

class BrushBase
{
public:
    QJsonObject save() const;

    static std::unique_ptr<BrushBase> loadBrush(const QJsonObject & obj);
    static std::unique_ptr<BrushBase> createBrush(BrushType type, const QString & name);

    inline BrushType getBrushType() const {return m_brushType;}

    QString name;

protected:
    BrushBase(BrushType type, const QString & _name);

    virtual void onSave(QJsonObject & obj) const = 0;

private:
    BrushType m_brushType;
};

#endif // BRUSHBASE_H
