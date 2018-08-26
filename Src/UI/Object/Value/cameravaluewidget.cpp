#include "cameravaluewidget.h"
#include "Scene/scenedata.h"
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRegExpValidator>
#include <bitset>

CameraValueWidget::CameraValueWidget(ObjectValueCamera & camera, QWidget *parent)
    : QWidget (parent)
    , m_camera(camera)
{
    QHBoxLayout * layerLayout = new QHBoxLayout();
    layerLayout->addWidget(new QLabel("Layers : "));
    if(SceneData::currentScene() != nullptr)
    {
        m_layers = new CheckedComboBox();
        updateLayers();
        layerLayout->addWidget(m_layers, 1);
    }
    else
    {
        m_layerOutScene = new QLineEdit();
        m_layerOutScene->setValidator(new QRegExpValidator(QRegExp("^[01]*$")));
        updateLayersOutScene();
        layerLayout->addWidget(m_layerOutScene, 1);
    }

    m_fixedSize = new QCheckBox("Nombre pixel Fixe");
    m_fixedSize->setChecked(m_camera.fixedSize);

    m_valueLabel = new QLabel();
    updateValueLabel();
    m_value = new QDoubleSpinBox();
    m_value->setRange(0, 10000);
    m_value->setSingleStep(0.1f);
    m_value->setDecimals(2);
    m_value->setValue(camera.value);

    QHBoxLayout * valueLayout = new QHBoxLayout();
    valueLayout->addWidget(m_valueLabel);
    valueLayout->addWidget(m_value, 1);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addLayout(layerLayout);
    layout->addWidget(m_fixedSize);
    layout->addLayout(valueLayout);

    setLayout(layout);

    if(SceneData::currentScene() != nullptr)
    connect(m_layers, SIGNAL(globalCheckStateChanged(int)), this, SLOT(onValueChanged()));
    else connect(m_layerOutScene, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
    connect(m_fixedSize, SIGNAL(toggled(bool)), this, SLOT(onValueChanged()));
    connect(m_value, SIGNAL(editingFinished()), this, SLOT(onValueChanged()));
}

void CameraValueWidget::updateLayers()
{
    m_layers->blockSignals(true);

    m_layers->clear();
    std::bitset<32> set(m_camera.layerMask);

    for(unsigned int i(0) ; i < SceneData::currentScene()->size() && i < 32 ; i++)
    {
        m_layers->addCheckItem((*SceneData::currentScene())[i]->name, set[i] ? Qt::CheckState::Checked : Qt::CheckState::Unchecked);
    }

    m_layers->blockSignals(false);
}

void CameraValueWidget::updateLayersOutScene()
{
    m_layerOutScene->blockSignals(true);

    std::bitset<32> set(m_camera.layerMask);
    m_layerOutScene->setText(QString::fromStdString(set.to_string()));

    m_layerOutScene->blockSignals(false);
}

void CameraValueWidget::updateValueLabel()
{
    if(m_camera.fixedSize)
        m_valueLabel->setText("Vertical Pixels :");
    else m_valueLabel->setText("Zoom : ");
}

#include <iostream>
void CameraValueWidget::onValueChanged()
{
    std::cout << "changed !" << std::endl;

    if(SceneData::currentScene() != nullptr)
        m_camera.layerMask = m_layers->checkStateBitSet();
    else
    {
        std::bitset<32> set(m_layerOutScene->text().toStdString());
        m_camera.layerMask = set.to_ulong();
    }

    m_camera.fixedSize = m_fixedSize->isChecked();
    m_camera.value = m_value->value();

    updateValueLabel();
}
