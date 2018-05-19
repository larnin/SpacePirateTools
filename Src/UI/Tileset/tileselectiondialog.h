#ifndef TILESELECTIONDIALOG_H
#define TILESELECTIONDIALOG_H

#include "tileselectionwidget.h"
#include "ressource.h"
#include <QDialog>

class TileSelectionDialog : public QDialog
{
public:
    TileSelectionDialog(Texture texture, unsigned int delta, unsigned int size, QWidget * parent = nullptr);

    inline unsigned int get() const { return m_value; }

    static unsigned int getTileID(Texture texture, unsigned int delta, unsigned int size, QWidget* parent, bool *ok = nullptr);

public slots:
    void onTileSelect(unsigned int value);

private:
    TileSelectionWidget * m_tileWidget;
    unsigned int m_value;
};

#endif // TILESELECTIONDIALOG_H
