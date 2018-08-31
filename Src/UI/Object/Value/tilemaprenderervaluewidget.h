#ifndef TILEMAPRENDERERVALUEWIDGET_H
#define TILEMAPRENDERERVALUEWIDGET_H

#include "Object/Value/objectvaluetilemaprenderer.h"
#include <QWidget>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QSpinBox>

class TilemapRendererValueWidget : public QWidget
{
    Q_OBJECT
public:
    TilemapRendererValueWidget(ObjectValueTilemapRenderer & tilemap, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    void updateTilemapWidget();
    void updateTextureWidget();

    ObjectValueTilemapRenderer & m_data;

    QComboBox * m_tilemap;
    QComboBox * m_texture;

    QDoubleSpinBox * m_offsetX;
    QDoubleSpinBox * m_offsetY;

    QSpinBox * m_size;
    QSpinBox * m_delta;
};

#endif // TILEMAPRENDERERVALUEWIDGET_H
