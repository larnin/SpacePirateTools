#include "tilecolliderselectiondialog.h"
#include "UI/linewidget.h"
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QGroupBox>


TileColliderSelectionDialog::TileColliderSelectionDialog(QWidget *parent)
    : QDialog(parent)
{
    setMinimumSize(399, 400);

    m_xFlipped = new QCheckBox("X");
    m_yFlipped = new QCheckBox("Y");

    QHBoxLayout * flipLayout = new QHBoxLayout();
    flipLayout->addWidget(new QLabel("Flip : "));
    flipLayout->addWidget(m_xFlipped);
    flipLayout->addSpacing(10);
    flipLayout->addWidget(m_yFlipped);

    m_rot0 = new QRadioButton("0");
    m_rot0->setChecked(true);
    m_rot90 = new QRadioButton("90");
    m_rot180 = new QRadioButton("180");
    m_rot270 = new QRadioButton("270");

    QGroupBox* radioGroup = new QGroupBox("Rotation");
    QHBoxLayout* radioLayout = new QHBoxLayout();
    radioLayout->addWidget(m_rot0);
    radioLayout->addWidget(m_rot90);
    radioLayout->addWidget(m_rot180);
    radioLayout->addWidget(m_rot270);
    radioGroup->setLayout(radioLayout);

    m_tileSelect = new TileColliderSelectionWidget();

    QPushButton* validButton = new QPushButton("Valider");
    QPushButton* cancelButton = new QPushButton("Annuler");
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->addStretch(1);
    buttonsLayout->addWidget(validButton);
    buttonsLayout->addWidget(cancelButton);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Slectionnez le collider"));
    layout->addSpacing(10);
    layout->addLayout(flipLayout);
    layout->addSpacing(5);
    layout->addWidget(radioGroup);
    layout->addWidget(new LineWidget(LineOrientation::Horizontal));
    layout->addWidget(m_tileSelect, 1);
    layout->addLayout(buttonsLayout);
    setLayout(layout);

    connect(m_tileSelect, SIGNAL(onTileColliderSelect(TileCollider)), this, SLOT(onTileColliderSelect(TileCollider)));

    connect(m_xFlipped, SIGNAL(released()), this, SLOT(onCheckItem()));
    connect(m_yFlipped, SIGNAL(released()), this, SLOT(onCheckItem()));

    connect(m_rot0, SIGNAL(clicked(bool)), this, SLOT(onCheckItem()));
    connect(m_rot90, SIGNAL(clicked(bool)), this, SLOT(onCheckItem()));
    connect(m_rot180, SIGNAL(clicked(bool)), this, SLOT(onCheckItem()));
    connect(m_rot270, SIGNAL(clicked(bool)), this, SLOT(onCheckItem()));

    connect(validButton, SIGNAL(clicked(bool)), this, SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked(bool)), this, SLOT(reject()));
}

void TileColliderSelectionDialog::onTileColliderSelect(const TileCollider & collider)
{
    m_value = collider;
}

void TileColliderSelectionDialog::onCheckItem()
{
    m_tileSelect->setXFlipped(m_xFlipped->isChecked());
    m_tileSelect->setYFlipped(m_yFlipped->isChecked());
    TileColliderRotation rot(m_rot0->isChecked() ? TileColliderRotation::R_0
                          : (m_rot90->isChecked() ? TileColliderRotation::R_90
                          : (m_rot180->isChecked() ? TileColliderRotation::R180
                          : TileColliderRotation::R270)));
    m_tileSelect->setColliderRotation(rot);
}

TileCollider TileColliderSelectionDialog::getTileCollider(QWidget* parent, bool *ok)
{
    TileColliderSelectionDialog dialog(parent);
    auto value = dialog.exec();
    if(ok != nullptr)
        (*ok) = value == QDialog::Accepted;
    return dialog.get();
}
