#ifndef ANIMATORINFOS_H
#define ANIMATORINFOS_H

#include "Animator/animatordata.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>

class AnimatorInfos : public QWidget
{
    Q_OBJECT
public:
    AnimatorInfos(const QString &assetName, QWidget * parent = nullptr);
    inline const AnimatorData & getAnimatorData() const { return m_datas;}
public slots:

private:
    void initializeWidgets();

    AnimatorData m_datas;

    QListWidget* m_states;

    QGroupBox* m_stateGroup;
    QLineEdit* m_stateName;
    QComboBox* m_animation;
    QCheckBox* xFlipped;
    QCheckBox* yFlipped;

    QListWidget* m_transitions;

    QComboBox* m_conditionType;
    QFrame* m_conditionHolder;
};

#endif // ANIMATORINFOS_H
