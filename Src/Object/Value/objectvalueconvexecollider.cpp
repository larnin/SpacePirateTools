#include "objectvalueconvexecollider.h"
#include "UI/Object/Value/convexcollidervaluewidget.h"
#include "UI/Scene/NodeRenderer/valuerenderernone.h"
#include <QJsonArray>

ObjectValueConvexeCollider::ObjectValueConvexeCollider()
    : ObjectValueBase(ValueType::ConvexeCollider)
{

}

ObjectValueConvexeCollider::ObjectValueConvexeCollider(const QJsonObject & obj)
    : ObjectValueConvexeCollider()
{
    for(const auto p : obj["points"].toArray())
    {
        auto pObj = p.toObject();
        points.push_back(sf::Vector2f(pObj["x"].toDouble(), pObj["y"].toDouble()));
    }
}

QString ObjectValueConvexeCollider::toString() const
{
    QString s("Points : " + QString::number(points.size()));

    for(unsigned int i(0) ; i < points.size() ; i++)
        s += "\n[" + QString::number(i + 1) + "] " + QString::number(points[i].x) + " * " + QString::number(points[i].y);

    return s;
}

QWidget* ObjectValueConvexeCollider::createUi()
{
    return new ConvexColliderValueWidget(*this);
}

void ObjectValueConvexeCollider::onSave(QJsonObject & obj) const
{
    QJsonArray array;

    for(const auto & p : points)
    {
        QJsonObject o;
        o.insert("x", p.x);
        o.insert("y", p.y);
        array.append(o);
    }
    obj.insert("points", array);
}

std::unique_ptr<ValueRendererBase> ObjectValueConvexeCollider::renderer(SceneNode* node)
{
    return std::make_unique<ValueRendererNone>(node, this);
}
