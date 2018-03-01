#include "animationsinfos.h"
#include "UI/linewidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>

AnimationsInfos::AnimationsInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_centralWidget(nullptr)
    , m_datas(assetName)
    , m_assetName(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
{
    initializeWidgets();
}

void AnimationsInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void AnimationsInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
}

void AnimationsInfos::initializeWidgets()
{
    m_texture = new QComboBox();
    QHBoxLayout* textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture :"));
    textureLayout->addWidget(m_texture, 1);

    m_frameList = new QListWidget();

    m_time = new QDoubleSpinBox();
    m_time->setRange(0.001, 1000);
    QHBoxLayout* timeLayout = new QHBoxLayout();
    timeLayout->addWidget(new QLabel("Temps :"));
    timeLayout->addWidget(m_time, 1);

    m_offsetX = new QSpinBox();
    m_offsetX->setRange(-10000, 10000);
    m_offsety = new QSpinBox();
    m_offsety->setRange(-10000, 10000);
    QHBoxLayout* offsetLayout = new QHBoxLayout();
    offsetLayout->addWidget(new QLabel("X :"));
    offsetLayout->addWidget(m_offsetX, 1);
    offsetLayout->addSpacing(5);
    offsetLayout->addWidget(new QLabel("Y :"));
    offsetLayout->addWidget(m_offsety, 1);

    m_rectLeft = new QSpinBox();
    m_rectLeft->setRange(0, 10000);
    m_rectTop = new QSpinBox();
    m_rectTop->setRange(0, 10000);
    m_rectWidth = new QSpinBox();
    m_rectWidth->setRange(0, 10000);
    m_rectHeight = new QSpinBox();
    m_rectHeight->setRange(0, 10000);
    QHBoxLayout* rectPosLayout = new QHBoxLayout();
    rectPosLayout->addWidget(new QLabel("Gauche :"));
    rectPosLayout->addWidget(m_rectLeft, 1);
    rectPosLayout->addSpacing(5);
    rectPosLayout->addWidget(new QLabel("Haut :"));
    rectPosLayout->addWidget(m_rectTop, 1);
    QHBoxLayout* rectSizeLayout = new QHBoxLayout();
    rectSizeLayout->addWidget(new QLabel("Largeur :"));
    rectSizeLayout->addWidget(m_rectWidth, 1);
    rectSizeLayout->addSpacing(5);
    rectSizeLayout->addWidget(new QLabel("Hauteur :"));
    rectSizeLayout->addWidget(m_rectHeight, 1);

    m_frameDatasBox = new QGroupBox("Frame");
    QVBoxLayout* frameLayout = new QVBoxLayout();
    frameLayout->addLayout(timeLayout);
    frameLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    frameLayout->addWidget(new QLabel("Offset"));
    frameLayout->addLayout(offsetLayout);
    frameLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    frameLayout->addWidget(new QLabel("Rectangle"));
    frameLayout->addLayout(rectPosLayout);
    frameLayout->addLayout(rectSizeLayout);
    m_frameDatasBox->setLayout(frameLayout);

    QVBoxLayout* principalLayout = new QVBoxLayout();
    principalLayout->addLayout(textureLayout);
    principalLayout->addSpacing(5);
    principalLayout->addWidget(new QLabel("Frames"));
    principalLayout->addWidget(m_frameList);
    principalLayout->addWidget(m_frameDatasBox);

    setLayout(principalLayout);
}
