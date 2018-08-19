#ifndef COPYMAPTOOL_H
#define COPYMAPTOOL_H

#include "basemaptool.h"
#include "Events/Event.h"
#include "Events/Args/editionevents.h"

class CopyMapTool : public BaseMapTool
{
public:
    struct CopyValue
    {
        sf::Vector2u pos;
        TileInfos tile;
    };

    CopyMapTool(TilemapData & data);

    static inline const std::vector<CopyValue> & copyBuffer(){ return m_copyBuffer; }

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;
    void beforeSelectionEnd() override;

private:
    void onCopy(const CopyEvent &);
    void onCut(const CutEvent &);

    EventHolder<CopyEvent> m_copyHolder;
    EventHolder<CutEvent> m_cutHolder;

    bool m_haveSelected;
    bool m_onCopySelection;
    sf::Vector2u m_startPos;
    sf::Vector2u m_endPos;

    static std::vector<CopyValue> m_copyBuffer;
};

#endif // COPYMAPTOOL_H
