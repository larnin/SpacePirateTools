#ifndef ANIMATORINFOS_H
#define ANIMATORINFOS_H

#include "Animator/animatordata.h"
#include "Events/Args/saveevent.h"
#include "Events/Args/renamedfileevent.h"
#include "Events/Args/removedfileevent.h"
#include "Events/Args/addedfileevent.h"
#include "Events/Event.h"
#include <QWidget>
#include <QListWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGroupBox>
#include <vector>

class AnimatorInfos : public QWidget
{
    Q_OBJECT

    struct TransitionInfos
    {
        unsigned int index;
        bool from; //true = other state previous, false = next
    };

public:
    AnimatorInfos(const QString &assetName, QWidget * parent = nullptr);
    ~AnimatorInfos();

    inline const AnimatorData & getAnimatorData() const { return m_datas;}
    inline int getSelectedStateID() const { return m_currentStateIndex;}
    inline int getSelectedTransitionID() const { return m_currentTransitionIndex;}

    void addState();
    void addTransition(unsigned int previous, unsigned int next);
    void selectState(unsigned int index);
    void selectTransition(unsigned int index);

public slots:
    void onRightClickStates(QPoint point);
    void onRightClickTransitions(QPoint point);
    void onStateSelected(int index);
    void onTransitionSelected(int index);
    void onStateValueChanged();
    void onConditionChanged();

private:
    void initializeWidgets();

    void updateAnimationList();

    void updateStateList();
    void updateStateData();
    void updateTransitionList();
    void updateTransitionInfos();

    void blockStateSignals(bool block);

    void onSave(const SaveEvent &);
    void onRename(const RenamedFileEvent & e);
    void onRemove(const RemovedFileEvent &);
    void onAdd(const AddedFileEvent &);

    void removeState(unsigned int index);
    void duplicateState(unsigned int index);

    AnimatorData m_datas;
    QString m_assetName;

    QListWidget* m_states;

    QGroupBox* m_stateGroup;
    QLineEdit* m_stateName;
    QComboBox* m_animation;
    QCheckBox* m_xFlipped;
    QCheckBox* m_yFlipped;

    QListWidget* m_transitions;

    QGroupBox* m_transitionGroup;
    QLineEdit* m_condition;

    EventHolder<SaveEvent> saveHolder;
    EventHolder<RenamedFileEvent> renameHolder;
    EventHolder<RemovedFileEvent> removedHolder;
    EventHolder<AddedFileEvent> addedHolder;

    int m_currentStateIndex;
    int m_currentTransitionIndex;

    std::vector<QString> m_animations;
    std::vector<TransitionInfos> m_transitionsInfos;
};

#endif // ANIMATORINFOS_H
