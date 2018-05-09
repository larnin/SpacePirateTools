#ifndef OBJECTVALUEBASE_H
#define OBJECTVALUEBASE_H

#include <QString>
#include <QWidget>
#include <QJsonObject>
#include <memory>

enum class ValueType
{
    Transform,
    Box2DCollider,
    CircleCollider,
    ConvexeCollider,
    Rigidbody,
    Animator,
    Animation,
    Object,
    Renderer,
    Script,
    Float,
    Int,
    Vector2f,
    Vector2i,
    Color,
    Max = Color
};

QString valueTypeToString(ValueType type);

class ObjectValueBase
{
public:
    ObjectValueBase(ValueType type);
    virtual QString toString() const = 0;
    virtual QWidget* createUi() = 0;

    QJsonObject save() const;
    inline ValueType type() const { return m_valueType; }

    static std::unique_ptr<ObjectValueBase> createValue(ValueType type);
    static std::unique_ptr<ObjectValueBase> loadValue(const QJsonObject & obj);

protected:
    virtual void onSave(QJsonObject & obj) const = 0;

private:
    ValueType m_valueType;
};

#endif // OBJECTVALUEBASE_H
