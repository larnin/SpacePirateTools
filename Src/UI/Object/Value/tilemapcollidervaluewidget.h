#ifndef TILEMAPCOLLIDERVALUEWIDGET_H
#define TILEMAPCOLLIDERVALUEWIDGET_H

#include "Object/Value/objectvaluetilemapcollider.h"
#include <QWidget>
#include <QDoubleSpinBox>
#include <QSpinBox>
#include <QComboBox>

class TilemapColliderValueWidget : public QWidget
{
    Q_OBJECT
public:
    TilemapColliderValueWidget(ObjectValueTilemapCollider & collider, QWidget * parent = nullptr);

public slots:
    void onValueChanged();

private:
    void updateAssetWidget();

    ObjectValueTilemapCollider & m_collider;

    QComboBox * m_asset;
    QSpinBox * m_tileSize;
    QDoubleSpinBox * m_offsetX;
    QDoubleSpinBox * m_offsetY;

};

#endif // TILEMAPCOLLIDERVALUEWIDGET_H
