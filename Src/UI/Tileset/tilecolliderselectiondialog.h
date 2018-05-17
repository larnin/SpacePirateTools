#ifndef TILECOLLIDERSELECTIONDIALOG_H
#define TILECOLLIDERSELECTIONDIALOG_H

#include "Tileset/tilecollider.h"
#include "tilecolliderselectionwidget.h"
#include <QDialog>
#include <QCheckBox>
#include <QRadioButton>
#include <QComboBox>

class TileColliderSelectionDialog : QDialog
{
    Q_OBJECT
public:
    TileColliderSelectionDialog(QWidget *parent = nullptr);

    inline TileCollider get() const { return m_tileSelect->get(); }

    static TileCollider getTileCollider(QWidget* parent, bool *ok = nullptr);

public slots:
    void onTileColliderSelect(const TileCollider & collider);
    void onCheckItem();
    void onLayerChange(int index);

private:
    void setCollisionLayer();

    TileCollider m_value;

    QCheckBox * m_xFlipped;
    QCheckBox * m_yFlipped;
    QRadioButton * m_rot0;
    QRadioButton * m_rot90;
    QRadioButton * m_rot180;
    QRadioButton * m_rot270;

    QComboBox * m_collisionLayer;

    TileColliderSelectionWidget * m_tileSelect;
};

#endif // TILECOLLIDERSELECTIONDIALOG_H
