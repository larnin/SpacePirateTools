#ifndef TILESETLAYER_H
#define TILESETLAYER_H

#include "layerbase.h"
#include "matrix.h"
#include "Tileset/tilecollider.h"
#include "ressource.h"
#include <QJsonObject>

struct TileInfos
{
    unsigned int id = 0;
    TileCollider collider;
};

class TilesetLayer : public LayerBase
{
public:
    TilesetLayer(const QString & name, const QJsonObject & obj);
    TilesetLayer(const QString & name, const sf::Vector2u &size);

    void setSize(const sf::Vector2u & size) override;
    inline sf::Vector2u size() const { return m_tiles.getSize(); }

    inline TileInfos & operator()(const sf::Vector2u & pos) {return m_tiles(pos);}
    inline const TileInfos & operator()(const sf::Vector2u & pos)const {return m_tiles(pos);}

    void setTextureName(const QString & name);
    inline QString textureName() const { return m_textureName; }

    QString brushName;

protected:
    void onSave(QJsonObject & obj) const override;
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    QString m_textureName;
    Texture m_texture;
    Matrix<TileInfos> m_tiles;
};

#endif // TILESETLAYER_H
