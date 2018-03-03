#ifndef ANIMATIONSINFOS_H
#define ANIMATIONSINFOS_H

#include "Animation/animationdata.h"
#include "Events/Event.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include <QWidget>
#include <QString>
#include <QListWidget>
#include <QSpinBox>
#include <QDoubleSpinBox>
#include <QComboBox>
#include <QGroupBox>
#include <QPushButton>

class CentralAnimationWidget;

class AnimationsInfos : public QWidget
{
    Q_OBJECT

    friend class CentralAnimationWidget;
public:
    AnimationsInfos( const QString & assetName, QWidget * parent = nullptr);

    inline const AnimationData & getAnimationData() const { return m_datas;}
    inline int getCurrentFrameIndex() const {return m_currentFrameIndex;}
    void setFrame(unsigned int index, const Frame & value);

public slots:
    void onFrameSelected(int index);
    void onFrameValueChanged();
    void onRightClick(QPoint point);
    void onImageSelected(int index);
    void onColorButtonClicked();

private:
    inline void setCentralAnimationWidget(CentralAnimationWidget * w){ m_centralWidget = w; }

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    void initializeWidgets();

    void blockFrameSignals(bool blocked);

    void updateFrameList();
    void updateFrameData();
    void updateDatas();
    void updateImageList();
    void updateButtonColor();

    CentralAnimationWidget * m_centralWidget;

    AnimationData m_datas;
    QString m_assetName;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;

    QPushButton* m_colorButton;

    QComboBox* m_texture;
    QListWidget* m_frameList;

    QDoubleSpinBox* m_time;

    QSpinBox* m_offsetX;
    QSpinBox* m_offsety;

    QSpinBox* m_rectLeft;
    QSpinBox* m_rectTop;
    QSpinBox* m_rectWidth;
    QSpinBox* m_rectHeight;

    QGroupBox* m_frameDatasBox;

    int m_currentFrameIndex;

};

#endif // ANIMATIONSINFOS_H
