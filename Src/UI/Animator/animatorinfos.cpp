#include "animatorinfos.h"
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

AnimatorInfos::AnimatorInfos(const QString & assetName, QWidget *parent)
    : QWidget(parent)
    , m_datas(assetName)
{
    initializeWidgets();
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

    xFlipped = new QCheckBox("X");
    yFlipped = new QCheckBox("Y");
    QHBoxLayout* flipLayout = new QHBoxLayout();
    flipLayout->addWidget(new QLabel("Symetrie :"));
    flipLayout->addWidget(xFlipped);
    flipLayout->addSpacing(10);
    flipLayout->addWidget(yFlipped);

    m_stateGroup = new QGroupBox("Etat");
    QVBoxLayout* stateLayout = new QVBoxLayout();
    stateLayout->addLayout(stateNameLayout);
    stateLayout->addLayout(animationLayout);
    stateLayout->addLayout(flipLayout);
    m_stateGroup->setLayout(stateLayout);

    m_transitions = new QListWidget();

    m_conditionType = new QComboBox();
    QHBoxLayout* conditionTypeLayout = new QHBoxLayout();
    conditionTypeLayout->addWidget(new QLabel("Condition type :"));
    conditionTypeLayout->addWidget(m_conditionType, 1);

    m_conditionHolder = new QFrame();
    m_conditionHolder->setFrameShape(QFrame::StyledPanel);

    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("States"));
    layout->addWidget(m_states);
    layout->addWidget(m_stateGroup);
    layout->addSpacing(5);
    layout->addWidget(new QLabel("Transitions"));
    layout->addWidget(m_transitions);
    layout->addLayout(conditionTypeLayout);
    layout->addWidget(m_conditionHolder, 1);

    setLayout(layout);
}
