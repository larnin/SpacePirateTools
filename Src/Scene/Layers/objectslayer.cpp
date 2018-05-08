#include "objectslayer.h"
#include "Scene/Tools/basescenetool.h"

ObjectsLayer::ObjectsLayer(const QString & name, const QJsonObject & obj)
    : LayerBase(LayerType::Objects, name)
{

}

ObjectsLayer::ObjectsLayer(const QString & name, const sf::Vector2u &)
    : LayerBase(LayerType::Objects, name)
{

}

void ObjectsLayer::onSave(QJsonObject & obj) const
{

}

void ObjectsLayer::draw(sf::RenderTarget &target, sf::RenderStates states) const
{

}

void ObjectsLayer::setSize(const sf::Vector2u & size)
{

}

#include <QLabel>
QWidget * ObjectsLayer::getToolWindow(CentralSceneWindow * window)
{
    return new QLabel("Cet outil n'est pas encore disponible");
}

std::unique_ptr<BaseSceneTool> ObjectsLayer::getSelectionTool(CentralSceneWindow *window)
{
    return {};
}
