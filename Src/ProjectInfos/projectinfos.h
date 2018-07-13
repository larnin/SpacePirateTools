#ifndef PROJECTINFOS_H
#define PROJECTINFOS_H

#include "filelist.h"
#include "assettype.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include <SFML/Graphics/Color.hpp>
#include <QString>
#include <vector>

enum class LayerCollisionType
{
    None,
    Trigger,
    Collision,
};

/// layerCollisions
/// [0 - 7] layerID
/// [8 - 10] collisionType
struct ColliderLayer
{
    QString name;
    sf::Color color;
    std::vector<unsigned int> layerCollisions;

    inline static LayerCollisionType typeOf(int value){return static_cast<LayerCollisionType>((value & 0xF00) >> 8);}
    inline static unsigned int indexLayer(int value){return value & 0xFF;}
    inline static unsigned int toLayerCollision(LayerCollisionType type, unsigned int index){return (static_cast<unsigned int>(type) << 8) + (index & 0xFF);}
};

struct ProjectOptions
{
    std::vector<ColliderLayer> colliderLayers;
};

class ProjectInfos
{
public:
    ProjectInfos();

    void loadProject(const QString & projectDirectory);

    inline bool projectLoaded() const { return m_projectLoaded; }
    std::vector<QString> fileInfos(AssetType type) const;
    bool fileExist(const QString & name, AssetType type) const;
    inline const QString & projectDirectory() const { return m_projectDirectory; }
    void reloadFileList();

    void save();
    inline ProjectOptions & options() {return m_options;}

    static ProjectInfos & instance();

private:
    void load();
    void onSave(const SaveEvent &);
    void validData();

    static ProjectInfos m_instance;

    bool m_projectLoaded;
    QString m_projectDirectory;
    FileList m_fileList;

    ProjectOptions m_options;

    EventHolder<SaveEvent> m_saveHolder;
};

#endif // PROJECTINFOS_H
