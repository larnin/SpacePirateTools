#ifndef OBJECTVALUEBASE_H
#define OBJECTVALUEBASE_H

#include <QString>
#include <QWidget>
#include <QJsonObject>
#include <memory>

class ValueRendererBase;
class SceneNode;

enum class ValueType
{
    Transform = -1,
    Box2DCollider,
    CircleCollider,
    ConvexeCollider,
    Rigidbody,
    Animator,
    Animation,
    Object,
    Texture,
    Scene,
    SpriteRenderer,
    Script,
    Float,
    Int,
    Vector2f,
    Vector2i,
    Color,
    Text,
    Camera,
    TilemapCollider,
    TilemapRenderer,
    Max = TilemapRenderer,
};

QString valueTypeToString(ValueType type);

class ObjectValueBase
{
public:
    ObjectValueBase(ValueType type);
    ObjectValueBase(const ObjectValueBase &) = default;
    virtual ~ObjectValueBase() = default;

    virtual QString toString() const = 0;
    virtual QWidget* createUi() = 0;
    virtual std::unique_ptr<ObjectValueBase> clone() const = 0;
    virtual std::unique_ptr<ValueRendererBase> renderer(SceneNode* node) = 0;

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
