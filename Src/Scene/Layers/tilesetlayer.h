#ifndef TILESETLAYER_H
#define TILESETLAYER_H

#include "layerbase.h"
#include "matrix.h"
#include "Tileset/tilecollider.h"
#include "ressource.h"
#include <SFML/Graphics/VertexArray.hpp>
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
    QWidget * getToolWindow(CentralSceneWindow * window) override;
    inline sf::Vector2u size() const { return m_tiles.getSize(); }

    inline TileInfos getTile(const sf::Vector2u & pos) const {return m_tiles(pos);}
    void setTile(const sf::Vector2u & pos, const TileInfos & tile);

    void setTextureName(const QString & name);
    inline QString textureName() const { return m_textureName; }
    inline Texture texture() const { return m_texture; }

    QString brushName;

protected:
    void onSave(QJsonObject & obj) const override;
    void draw(sf::RenderTarget &target, sf::RenderStates) const override;

private:
    void updateRender();
    void updateTileRender();
    void updateGizmoRender();
    unsigned int renderableTileCount() const;
    void drawQuad(sf::Vertex* quad, const sf::FloatRect &rect, const sf::FloatRect &texRect) const;

    QString m_textureName;
    Texture m_texture;
    Matrix<TileInfos> m_tiles;
    sf::VertexArray m_tileArray;
    sf::VertexArray m_gizmoArray;
};

#endif // TILESETLAYER_H
