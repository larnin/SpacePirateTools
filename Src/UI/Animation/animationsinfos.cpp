#include "animationsinfos.h"
#include "UI/linewidget.h"
#include "ProjectInfos/projectinfos.h"
#include "ProjectInfos/configs.h"
#include "UI/Animation/centralanimationwidget.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QIcon>
#include <QPixmap>
#include <QColorDialog>

AnimationsInfos::AnimationsInfos(const QString &assetName, QWidget *parent)
    : QWidget(parent)
    , m_centralWidget(nullptr)
    , m_datas(assetName)
    , m_assetName(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , m_currentFrameIndex(-1)
{
    initializeWidgets();
    updateFrameList();
    updateImageList();
}

AnimationsInfos::~AnimationsInfos()
{
    m_datas.save(m_assetName);
}

void AnimationsInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void AnimationsInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
    updateImageList();
}

void AnimationsInfos::onRemove(const RemovedFileEvent &)
{
    updateImageList();
}

void AnimationsInfos:: onAdd(const AddedFileEvent &)
{
    updateImageList();
}

void AnimationsInfos::initializeWidgets()
{
    m_colorButton = new QPushButton("");
    m_colorButton->setFixedSize(30, 30);
    updateButtonColor();
    QHBoxLayout* colorLayout = new QHBoxLayout();
    colorLayout->addWidget(new QLabel("Couleur de fond :"));
    colorLayout->addWidget(m_colorButton);

    m_texture = new QComboBox();
    QHBoxLayout* textureLayout = new QHBoxLayout();
    textureLayout->addWidget(new QLabel("Texture :"));
    textureLayout->addWidget(m_texture, 1);

    m_loopCheckbox = new QCheckBox(" Boucle");

    m_frameList = new QListWidget();

    m_time = new QDoubleSpinBox();
    m_time->setRange(0.001, 1000);
    m_time->setDecimals(3);
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

    m_preview = new AnimationPreview(this);
    m_preview->setFixedSize(100, 100);
    QGroupBox* previewBox = new QGroupBox("Preview");
    QHBoxLayout* previewLayout = new QHBoxLayout();
    previewLayout->addWidget(m_preview);
    previewBox->setLayout(previewLayout);
    previewBox->setFixedSize(previewBox->minimumSizeHint());

    QVBoxLayout* principalLayout = new QVBoxLayout();
    principalLayout->addLayout(colorLayout);
    principalLayout->addWidget(new LineWidget(LineOrientation::Horizontal));
    principalLayout->addLayout(textureLayout);
    principalLayout->addSpacing(5);
    principalLayout->addWidget(m_loopCheckbox);
    principalLayout->addWidget(new QLabel("Frames"));
    principalLayout->addWidget(m_frameList);
    principalLayout->addWidget(m_frameDatasBox);
    principalLayout->addWidget(previewBox, 0, Qt::AlignHCenter);

    setLayout(principalLayout);

    connect(m_colorButton, SIGNAL(clicked(bool)), this, SLOT(onColorButtonClicked()));

    connect(m_texture, SIGNAL(currentIndexChanged(int)), this, SLOT(onImageSelected(int)));

    connect(m_loopCheckbox, SIGNAL(clicked(bool)), this, SLOT(onLoopChecked(bool)));

    connect(m_frameList, SIGNAL(currentRowChanged(int)), this, SLOT(onFrameSelected(int)));

    connect(m_time, SIGNAL(valueChanged(double)), this, SLOT(onFrameValueChanged()));
    connect(m_offsetX, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));
    connect(m_offsety, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));
    connect(m_rectLeft, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));
    connect(m_rectTop, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));
    connect(m_rectWidth, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));
    connect(m_rectHeight, SIGNAL(valueChanged(int)), this, SLOT(onFrameValueChanged()));

    m_frameList->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_frameList, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClick(QPoint)));
}

void AnimationsInfos::onFrameSelected(int index)
{
    m_currentFrameIndex = index;

    updateFrameData();
}

void AnimationsInfos::onLoopChecked(bool value)
{
    m_datas.loop = value;
}

void AnimationsInfos::onFrameValueChanged()
{
    updateDatas();
    updateFrameList();
}

void AnimationsInfos::onImageSelected(int index)
{
    if(index <= 0)
        m_datas.imageName = "";
    else m_datas.imageName = m_texture->currentText();
    m_centralWidget->updateTexture(m_datas.imageName);
    m_preview->updateTexture(m_datas.imageName);
}

void AnimationsInfos::onColorButtonClicked()
{
    auto c(Configs::instance().animationBackgroundColor);
    auto color = QColorDialog::getColor(QColor(c.r, c.g, c.b), this, "Changer la couleur de fond");
    if(!color.isValid())
        return;

    Configs::instance().animationBackgroundColor = sf::Color(color.red(), color.green(), color.blue());

    updateButtonColor();
}

void AnimationsInfos::blockFrameSignals(bool blocked)
{
    m_time->blockSignals(blocked);
    m_offsetX->blockSignals(blocked);
    m_offsety->blockSignals(blocked);

    m_rectLeft->blockSignals(blocked);
    m_rectTop->blockSignals(blocked);
    m_rectWidth->blockSignals(blocked);
    m_rectHeight->blockSignals(blocked);
}

void AnimationsInfos::updateFrameList()
{
    m_frameList->blockSignals(true);

    m_frameList->clear();
    for(unsigned int i(0) ; i < m_datas.size() ; i++)
    {
        const auto & f(m_datas[i]);

        m_frameList->addItem(QString("Frame") + QString::number(i+1) + " : " + QString::number(f.time) + "s");
    }

    if(m_currentFrameIndex >= 0 && m_currentFrameIndex < int(m_datas.size()))
        m_frameList->setCurrentRow(m_currentFrameIndex);
    else m_currentFrameIndex = -1;

    m_frameList->blockSignals(false);

    updateFrameData();
}

void AnimationsInfos::updateFrameData()
{
    if(m_currentFrameIndex < 0 || m_currentFrameIndex >= int(m_datas.size()))
    {
        m_frameDatasBox->setEnabled(false);
        return;
    }
    m_frameDatasBox->setEnabled(true);

    blockFrameSignals(true);

    const auto & f(m_datas[m_currentFrameIndex]);

    m_time->setValue(f.time);

    m_offsetX->setValue(f.offset.x);
    m_offsety->setValue(f.offset.y);

    m_rectLeft->setValue(f.rect.left);
    m_rectTop->setValue(f.rect.top);
    m_rectWidth->setValue(f.rect.width);
    m_rectHeight->setValue(f.rect.height);

    blockFrameSignals(false);
}

void AnimationsInfos::updateDatas()
{
    if(m_currentFrameIndex < 0 || m_currentFrameIndex >= int(m_datas.size()))
        return;

    auto & f(m_datas[m_currentFrameIndex]);

    f.time = m_time->value();
    f.offset.x = m_offsetX->value();
    f.offset.y = m_offsety->value();
    f.rect.left = m_rectLeft->value();
    f.rect.top = m_rectTop->value();
    f.rect.width = m_rectWidth->value();
    f.rect.height = m_rectHeight->value();
}

void AnimationsInfos::onRightClick(QPoint point)
{
    QPoint globalPos(m_frameList->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aUp(nullptr);
    QAction *aDown(nullptr);
    QAction *aDuplicate(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentFrameIndex >= 0 && m_currentFrameIndex < int(m_datas.size()))
    {
        aDel = menu.addAction("Supprimer");
        aDuplicate = menu.addAction("Dupliquer");
        if(m_currentFrameIndex > 0)
            aUp = menu.addAction("Monter");
        if(m_currentFrameIndex < int(m_datas.size()) - 1)
            aDown = menu.addAction("Descendre");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
    {
        m_datas.erase(m_datas.begin() + m_currentFrameIndex);
        updateFrameList();
    }
    if(action == aUp)
    {
        std::swap(m_datas[m_currentFrameIndex], m_datas[m_currentFrameIndex-1]);
        updateFrameList();
    }
    if(action == aDown)
    {
        std::swap(m_datas[m_currentFrameIndex], m_datas[m_currentFrameIndex+1]);
        updateFrameList();
    }
    if(action == aDuplicate)
    {
        m_datas.insert(m_datas.begin() + m_currentFrameIndex, m_datas[m_currentFrameIndex]);
        updateFrameList();
    }
    if(action == aAdd)
    {
        m_datas.push_back(Frame{sf::IntRect(0, 0, 1,1), sf::Vector2i(0, 0), 1});
        updateFrameList();
    }
}

void AnimationsInfos::updateImageList()
{
    m_texture->blockSignals(true);

    m_texture->clear();

    m_texture->addItem("None");
    for(const auto i : ProjectInfos::instance().fileInfos(AssetType::Image))
        m_texture->addItem(i);

    m_texture->setCurrentText(m_datas.imageName);
    if(m_texture->currentIndex() < 0)
    {
        m_texture->setCurrentIndex(0);
        m_datas.imageName = "";
        m_centralWidget->updateTexture(m_datas.imageName);
        m_preview->updateTexture(m_datas.imageName);
    }

    m_texture->blockSignals(false);
}

void AnimationsInfos::setFrame(unsigned int index, const Frame & value)
{
    if(index >= m_datas.size())
        return;
    m_datas[index] = value;
    updateFrameData();
}

void AnimationsInfos::updateButtonColor()
{
    constexpr int size(30);
    QPixmap map(size, size);
    auto color = Configs::instance().animationBackgroundColor;
    map.fill(QColor(color.r, color.g, color.b));
    m_colorButton->setIcon(QIcon(map));
}
