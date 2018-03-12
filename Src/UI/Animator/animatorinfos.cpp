#include "animatorinfos.h"
#include "ProjectInfos/projectinfos.h"
#include "ProjectInfos/assettype.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>

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

    connect(m_states, SIGNAL(currentRowChanged(int)), this, SLOT(onStateSelected(int)));
    m_states->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_states, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClickStates(QPoint)));
    connect(m_transitions, SIGNAL(currentRowChanged(int)), this, SLOT(onTransitionSelected(int)));
    m_transitions->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(m_transitions, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(onRightClickTransitions(QPoint)));

    connect(m_stateName, SIGNAL(editingFinished()), this, SLOT(onStateValueChanged()));
    connect(m_animation, SIGNAL(currentIndexChanged(int)), this, SLOT(onStateValueChanged()));
    connect(m_xFlipped, SIGNAL(clicked(bool)), this, SLOT(onStateValueChanged()));
    connect(m_yFlipped, SIGNAL(clicked(bool)), this, SLOT(onStateValueChanged()));

    connect(m_condition, SIGNAL(editingFinished()), this, SLOT(onConditionChanged()));
}

void AnimatorInfos::updateAnimationList()
{
    m_animations = ProjectInfos::instance().fileInfos(AssetType::Animation);

    auto str = m_animation->currentText();

    m_animation->clear();
    for(const QString & s : m_animations)
    {
        auto index = s.lastIndexOf('.');
        m_animation->addItem(index >= 0 ? s.left(index) : s);
    }

    m_animation->setCurrentText(str);
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

    auto it = std::find(m_animations.begin(), m_animations.end(), s.animation);
    if(it == m_animations.end())
        m_animation->setCurrentIndex(-1);
    else m_animation->setCurrentIndex(std::distance(m_animations.begin(), it));

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

void AnimatorInfos::onRightClickStates(QPoint point)
{
    QPoint globalPos(m_states->viewport()->mapToGlobal(point));

    QMenu menu;
    QAction *aDel(nullptr);
    QAction *aDuplicate(nullptr);
    QAction *aAdd(menu.addAction("Ajouter"));

    if(m_currentStateIndex >= 0 && m_currentStateIndex < int(m_datas.states.size()))
    {
        aDel = menu.addAction("Supprimer");
        aDuplicate = menu.addAction("Dupliquer");
    }

    QAction* action = menu.exec(globalPos);
    if(action == nullptr)
        return;

    if(action == aDel)
    {
        auto & s = m_datas.states[m_currentStateIndex].stateName;
        int result = QMessageBox::question(this, "Supprimer state", "Voulez vous suprimer l'etat " + s + " ?");
        if(result == QMessageBox::Yes)
        {
            removeState(m_currentStateIndex);
            updateStateList();
        }
    }

    if(action == aDuplicate)
    {
        duplicateState(m_currentStateIndex);
        updateStateList();
    }

    if(action == aAdd)
        addState();
}

void AnimatorInfos::onRightClickTransitions(QPoint point)
{
    if(m_currentTransitionIndex < 0 || m_currentTransitionIndex >= int(m_datas.transitions.size()))
        return;

    QMenu menu;
    QAction *aDel(menu.addAction("Supprimer"));

    QAction* action = menu.exec(m_transitions->viewport()->mapToGlobal(point));
    if(action == nullptr)
        return;

    if(action == aDel)
    {
        int result = QMessageBox::question(this, "Supprimer transition", "Etes vous sur de vouloir supprimer cette transition ?");
        if(result == QMessageBox::Yes)
        {
            m_datas.transitions.erase(m_datas.transitions.begin() + m_transitionsInfos[m_currentTransitionIndex].index);
            updateTransitionList();
        }
    }
}

void AnimatorInfos::onStateSelected(int index)
{
    m_currentStateIndex = index;
    updateStateData();
    updateTransitionList();
}

void AnimatorInfos::onTransitionSelected(int index)
{
    m_currentTransitionIndex = index;
    updateTransitionInfos();
}

void AnimatorInfos::onStateValueChanged()
{
    if(m_currentStateIndex < 0 || m_currentStateIndex >= m_states->count())
        return;

    AnimatorState & s = m_datas.states[m_currentStateIndex];

    if(m_animation->currentIndex() > 0)
        s.animation = m_animations[m_animation->currentIndex()];
    else s.animation = "";

    s.stateName = m_stateName->text();
    s.xFliped = m_xFlipped->isChecked();
    s.yFliped = m_yFlipped->isChecked();

    updateStateList();
}

void AnimatorInfos::onConditionChanged()
{
    if(m_currentTransitionIndex < 0 || m_currentTransitionIndex >= m_transitions->count())
        return;

    AnimatorTransition & t = m_datas.transitions[m_transitionsInfos[m_currentTransitionIndex].index];

    t.condition = m_condition->text();
}

void AnimatorInfos::removeState(unsigned int index)
{
    if(index >= m_datas.states.size())
        return;

    m_datas.states.erase(m_datas.states.begin() + index);
    m_datas.transitions.erase(std::remove_if(m_datas.transitions.begin(), m_datas.transitions.end(),
                                             [index](const auto & t){return t.previousState == index || t.nextState == index;}), m_datas.transitions.end());

    for(auto & t : m_datas.transitions)
    {
        if(t.previousState > index)
            t.previousState --;
        if(t.nextState > index)
            t.nextState --;
    }
}

void AnimatorInfos::duplicateState(unsigned int index)
{
    if(index >= m_datas.states.size())
        return;

    const AnimatorState & s = m_datas.states[index];

    m_datas.states.push_back(AnimatorState{s.stateName + "copie", s.animation, s.xFliped, s.yFliped});

    unsigned int newIndex = m_datas.states.size() - 1;
    unsigned int size(m_datas.transitions.size());
    for(unsigned int i(0) ; i < size ; i++)
    {
        const AnimatorTransition & t = m_datas.transitions[i];
        if(t.nextState == index)
            m_datas.transitions.push_back(AnimatorTransition{t.previousState, newIndex, t.condition});
        if(t.previousState == index)
            m_datas.transitions.push_back(AnimatorTransition{newIndex, t.nextState, t.condition});
    }
}

void AnimatorInfos::addState()
{

    bool ok = true;
    QString result = QInputDialog::getText(this, "Nouveau state", "Entrez le nom du nouvel etat", QLineEdit::Normal, "", &ok);
    if(!ok || result.isEmpty())
        return;

    m_datas.states.push_back(AnimatorState(result));
    updateStateList();
}

void AnimatorInfos::addTransition(unsigned int previous, unsigned int next)
{
    m_datas.transitions.push_back(AnimatorTransition(previous, next));
    updateTransitionList();
}

void AnimatorInfos::selectState(unsigned int index)
{
    m_states->setCurrentRow(index);
    onStateSelected(index);
}

void AnimatorInfos::selectTransition(unsigned int index)
{
    m_transitions->setCurrentRow(index);
    onTransitionSelected(index);
}
