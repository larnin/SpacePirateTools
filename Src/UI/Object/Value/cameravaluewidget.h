#ifndef CAMERAVALUEWIDGET_H
#define CAMERAVALUEWIDGET_H

#include "Object/Value/objectvaluecamera.h"
#include "UI/checkedcombobox.h"
#include <QWidget>
#include <QLineEdit>
#include <QCheckBox>
#include <QDoubleSpinBox>
#include <QLabel>

class CameraValueWidget : public QWidget
{
    Q_OBJECT
public:
    CameraValueWidget(ObjectValueCamera & camera, QWidget *parent = nullptr);

public slots:
    void onValueChanged();

private:
    void updateLayers();
    void updateLayersOutScene();
    void updateValueLabel();

    ObjectValueCamera & m_camera;

    CheckedComboBox * m_layers;
    QLineEdit * m_layerOutScene;
    QCheckBox * m_fixedSize;
    QLabel * m_valueLabel;
    QDoubleSpinBox * m_value;
};

#endif // CAMERAVALUEWIDGET_H
