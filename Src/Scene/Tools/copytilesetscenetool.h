#ifndef COPYTILESETSCENETOOL_H
#define COPYTILESETSCENETOOL_H

#include "basetilesetscenetool.h"
#include "Events/Event.h"
#include "Events/Args/editionevents.h"

class CopyTilesetSceneTool : public BaseTilesetSceneTool
{
    struct CopyValue
    {
        sf::Vector2u pos;
        TileInfos tile;
    };

public:
    CopyTilesetSceneTool(TilesetLayer & layer);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;
    void beforeSelectionEnd() override;

private:
    void onCopy(const CopyEvent &);
    void onCut(const CutEvent &);
    void onPaste(const PasteEvent &);

    EventHolder<CopyEvent> m_copyHolder;
    EventHolder<CutEvent> m_cutHolder;
    EventHolder<PasteEvent> m_pasteHolder;

    bool m_haveSelected;
    bool m_onSelection;
    sf::Vector2u m_startPos;
    sf::Vector2u m_endPos;

    static std::vector<CopyValue> m_copyBuffer;
};

#endif // COPYTILESETSCENETOOL_H
