#ifndef PASTEMAPTOOL_H
#define PASTEMAPTOOL_H

#include "basemaptool.h"
#include "copymaptool.h"

class PasteMapTool : public BaseMapTool
{
public:
    PasteMapTool(TilemapData & data, const std::vector<CopyMapTool::CopyValue> & value);

protected:
    void onAddTile(const sf::Vector2u & pos) override;
    void drawCursor(sf::RenderTarget &target, const sf::Vector2u & pos) const override;

private:
    void updateValueSize();

    std::vector<CopyMapTool::CopyValue> m_value;
    sf::Vector2u m_valueSize;
};

#endif // PASTEMAPTOOL_H
