#ifndef LAYERBASE_H
#define LAYERBASE_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <QString>
#include <QJsonObject>
#include <QWidget>
#include <memory>

class CentralSceneWindow;

enum class LayerType
{
    Tilemap,
    Objects,
    Max = Objects
};

QString layerTypeToString(LayerType type);

class LayerBase : public sf::Drawable
{
public:
    virtual ~LayerBase() = default;
    inline LayerType getLayerType() const { return m_type; }
    QJsonObject save() const;

    virtual void setSize(const sf::Vector2u & size) = 0;
    virtual QWidget * getToolWindow(CentralSceneWindow * window) = 0;

    static std::unique_ptr<LayerBase> loadLayer(const QJsonObject & obj);
    static std::unique_ptr<LayerBase> createLayer(LayerType type, const QString & name, const sf::Vector2u &size);

    QString name;
    bool hidden;
    bool showGizmos;

protected:
    LayerBase(LayerType type, const QString & _name);

    virtual void onSave(QJsonObject & obj) const = 0;

private:
    LayerType m_type;
};

#endif // LAYERBASE_H
