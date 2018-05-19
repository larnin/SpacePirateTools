#include "tileselectiondialog.h"
#include "UI/linewidget.h"
#include <QVBoxLayout>
#include <QLabel>

TileSelectionDialog::TileSelectionDialog(Texture texture, unsigned int delta, unsigned int size, QWidget *parent)
    : QDialog(parent)
    , m_value(0)
{
    m_tileWidget = new TileSelectionWidget(texture, delta, size);

    setMinimumSize(400, 400);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Selectionnez une tile"));
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(m_tileWidget, 1);

    setLayout(layout);

    connect(m_tileWidget, &TileSelectionWidget::onTileSelect, this, onTileSelect);
}

unsigned int TileSelectionDialog::getTileID(Texture texture, unsigned int delta, unsigned int size, QWidget* parent, bool *ok)
{
    TileSelectionDialog dialog(texture, delta, size, parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}

void TileSelectionDialog::onTileSelect(unsigned int value)
{
    m_value = value;

    accept();
}
