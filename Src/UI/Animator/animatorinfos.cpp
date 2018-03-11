#include "animatorinfos.h"
#include "ProjectInfos/projectinfos.h"
#include "ProjectInfos/assettype.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

AnimatorInfos::AnimatorInfos(const QString & assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
    , m_assetName(assetName)
    , saveHolder(Event<SaveEvent>::connect([this](const auto & e){onSave(e);}))
    , renameHolder(Event<RenamedFileEvent>::connect([this](const auto & e){onRename(e);}))
    , removedHolder(Event<RemovedFileEvent>::connect([this](const auto & e){onRemove(e);}))
    , addedHolder(Event<AddedFileEvent>::connect([this](const auto & e){onAdd(e);}))
    , m_currentStateIndex(-1)
    , m_currentTransitionIndex(-1)
{
    initializeWidgets();

    updateAnimationList();
    updateStateList();
}

AnimatorInfos::~AnimatorInfos()
{
    m_datas.save(m_assetName);
}

void AnimatorInfos::initializeWidgets()
{
    m_states = new QListWidget();

    m_stateName = new QLineEdit();
    QHBoxLayout* stateNameLayout = new QHBoxLayout();
    stateNameLayout->addWidget(new QLabel("Name :"));
    stateNameLayout->addWidget(m_stateName, 1);

    m_animation = new QComboBox();
    QHBoxLayout* animationLayout = new QHBoxLayout();
    animationLayout->addWidget(new QLabel("Animation :"));
    animationLayout->addWidget(m_animation, 1);

    m_xFlipped = new QCheckBox("X");
    m_yFlipped = new QCheckBox("Y");
    QHBoxLayout* flipLayout = new QHBoxLayout();
    flipLayout->addWidget(new QLabel("Symetrie :"));
    flipLayout->addWidget(m_xFlipped);
    flipLayout->addSpacing(10);
    flipLayout->addWidget(m_yFlipped);

    m_stateGroup = new QGroupBox("Etat");
    QVBoxLayout* stateLayout = new QVBoxLayout();
    stateLayout->addLayout(stateNameLayout);
    stateLayout->addLayout(animationLayout);
    stateLayout->addLayout(flipLayout);
    m_stateGroup->setLayout(stateLayout);

    m_transitions = new QListWidget();

    m_condition = new QLineEdit();
    QHBoxLayout* conditionLayout = new QHBoxLayout();
    conditionLayout->addWidget(new QLabel("Condition :"));
    conditionLayout->addWidget(m_condition);
    m_transitionGroup = new QGroupBox();
    m_transitionGroup->setLayout(conditionLayout);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("States"));
    layout->addWidget(m_states);
    layout->addWidget(m_stateGroup);
    layout->addSpacing(5);
    layout->addWidget(new QLabel("Transitions"));
    layout->addWidget(m_transitions);
    layout->addWidget(m_transitionGroup);

    setLayout(layout);
}

void AnimatorInfos::updateAnimationList()
{
    m_animations = ProjectInfos::instance().fileInfos(AssetType::Animation);
}

void AnimatorInfos::updateStateList()
{
    m_states->blockSignals(true);
    m_states->clear();

    for(const auto s : m_datas.states)
        m_states->addItem(s.stateName.isEmpty() ? s.animation : s.stateName);

    if(m_currentStateIndex >= 0 && m_currentStateIndex < m_states->count())
        m_states->setCurrentRow(m_currentStateIndex);
    m_states->blockSignals(false);

    updateStateData();
    updateTransitionList();
}

void AnimatorInfos::updateStateData()
{
    if(m_currentStateIndex < 0 || m_currentStateIndex >= m_states->count())
    {
        m_stateGroup->setEnabled(false);
        return;
    }
    m_stateGroup->setEnabled(true);

    blockStateSignals(true);

    const AnimatorState & s = m_datas.states[m_currentStateIndex];

    m_stateName->setText(s.stateName);
    m_animation->setCurrentText(s.animation);
    m_xFlipped->setChecked(s.xFliped);
    m_yFlipped->setChecked(s.yFliped);

    blockStateSignals(false);
}

void AnimatorInfos::updateTransitionList()
{
    m_transitions->blockSignals(true);
    m_transitions->clear();
    m_transitionsInfos.clear();

    if(m_currentStateIndex < 0 || m_currentStateIndex >= m_states->count())
    {
        updateTransitionInfos();
        return;
    }

    for(unsigned int i(0) ; i < m_datas.transitions.size() ; i++)
    {
        const AnimatorTransition & t(m_datas.transitions[i]);

        if(int(t.nextState) == m_currentStateIndex)
        {
            if(int(t.previousState) >= m_states->count())
                continue;
            const auto & state = m_datas.states[t.previousState];

            m_transitions->addItem("From " + state.stateName);
            m_transitionsInfos.push_back({i, true});
        }
    }

    for(unsigned int i(0) ; i < m_datas.transitions.size() ; i++)
    {
        const AnimatorTransition & t(m_datas.transitions[i]);

        if(int(t.previousState) == m_currentStateIndex)
        {
            if(int(t.nextState) >= m_states->count())
                continue;
            const auto & state = m_datas.states[t.nextState];

            m_transitions->addItem("From " + state.stateName);
            m_transitionsInfos.push_back({i, false});
        }
    }

    m_transitions->setCurrentRow(m_currentTransitionIndex);

    m_transitions->blockSignals(false);

    updateTransitionInfos();
}

void AnimatorInfos::updateTransitionInfos()
{
    if(m_currentStateIndex < 0 || m_currentStateIndex >= m_states->count() || m_currentTransitionIndex < 0 || m_currentStateIndex >= m_transitions->count())
    {
        m_transitionGroup->setEnabled(false);
        m_transitionGroup->setTitle("   ");
        return;
    }

    const AnimatorTransition & t = m_datas.transitions[m_currentStateIndex];
    m_transitionGroup->setEnabled(true);

    m_condition->blockSignals(true);

    const TransitionInfos & tI = m_transitionsInfos[m_currentTransitionIndex];
    const AnimatorState & s = m_datas.states[tI.from ? m_datas.transitions[tI.index].previousState : m_datas.transitions[tI.index].nextState];

    m_transitionGroup->setTitle((tI.from ? "From " : "To ") + s.stateName);
    m_condition->setText(t.condition);

    m_condition->blockSignals(false);
}

void AnimatorInfos::blockStateSignals(bool block)
{
    m_stateName->blockSignals(block);
    m_animation->blockSignals(block);
    m_xFlipped->blockSignals(block);
    m_yFlipped->blockSignals(block);
}

void AnimatorInfos::onSave(const SaveEvent &)
{
    m_datas.save(m_assetName);
}

void AnimatorInfos::onRename(const RenamedFileEvent & e)
{
    if(m_assetName == e.oldName)
        m_assetName = e.newName;
    updateAnimationList();
    updateStateList();
}

void AnimatorInfos::onRemove(const RemovedFileEvent &)
{
    updateAnimationList();
    updateStateList();
}

void AnimatorInfos::onAdd(const AddedFileEvent &)
{
    updateAnimationList();
    updateStateList();
}
