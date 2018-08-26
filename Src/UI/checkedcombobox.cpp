#include "checkedcombobox.h"
#include <cassert>

CheckedComboBox::CheckedComboBox(QWidget* parent) : QComboBox(parent)
{
    m_model = new QStandardItemModel();
    setModel(m_model);

    setEditable(true);
    lineEdit()->setReadOnly(true);
    lineEdit()->installEventFilter(this);
    setItemDelegate(new CheckedComboBoxStyledItemDelegate(this));

    connect(lineEdit(), &QLineEdit::selectionChanged, lineEdit(), &QLineEdit::deselect);
    connect(view(), SIGNAL(pressed(QModelIndex)), this, SLOT(onItemPressed(QModelIndex)));
    connect(m_model, SIGNAL(dataChanged(QModelIndex, QModelIndex, QVector<int>)), this, SLOT(onModelDataChanged()));
}

void CheckedComboBox::setAllCheckedText(const QString &text)
{
    m_allCheckedText = text;
    updateText();
}

void CheckedComboBox::setNoneCheckedText(const QString &text)
{
    m_noneCheckedText = text;
    updateText();
}

void CheckedComboBox::setUnknownlyCheckedText(const QString &text)
{
    m_unknownlyCheckedText = text;
    updateText();
}

QStandardItem* CheckedComboBox::addCheckItem(const QString &label, const QVariant &data, const Qt::CheckState checkState)
{
    QStandardItem* item = new QStandardItem(label);
    item->setCheckState(checkState);
    item->setData(data);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);

    m_model->appendRow(item);

    updateText();

    return item;
}

QStandardItem* CheckedComboBox::addCheckItem(const QString &label, const Qt::CheckState checkState)
{
    return addCheckItem(label, {}, checkState);
}

int CheckedComboBox::globalCheckState() const
{
    int nbRows = m_model->rowCount(), nbChecked = 0, nbUnchecked = 0;

    if (nbRows == 0)
    {
        return StateUnknown;
    }

    for (int i = 0; i < nbRows; i++)
    {
        if (m_model->item(i)->checkState() == Qt::Checked)
        {
            nbChecked++;
        }
        else if (m_model->item(i)->checkState() == Qt::Unchecked)
        {
            nbUnchecked++;
        }
        else
        {
            return StateUnknown;
        }
    }

    return nbChecked == nbRows ? Qt::Checked : nbUnchecked == nbRows ? Qt::Unchecked : Qt::PartiallyChecked;
}

Qt::CheckState CheckedComboBox::checkState(int index) const
{
    assert(index < m_model->rowCount() && index >= 0 && "Out of range index");

    return m_model->item(index)->checkState();
}

unsigned int CheckedComboBox::checkStateBitSet() const
{
    unsigned int field(0);

    for(int i(m_model->rowCount()-1) ; i >= 0 ; i--)
    {
        field <<= 1;
        if(m_model->item(i)->checkState() == Qt::CheckState::Checked)
            field++;
    }
    return field;
}

bool CheckedComboBox::eventFilter(QObject* object, QEvent* event)
{
    if (object == lineEdit() && event->type() == QEvent::MouseButtonPress)
    {
        showPopup();
        return true;
    }

    return false;
}

void CheckedComboBox::updateText()
{
    QString text;

    switch (globalCheckState())
    {
    case Qt::Checked:
        text = m_allCheckedText;
        break;

    case Qt::Unchecked:
        text = m_noneCheckedText;
        break;

    case Qt::PartiallyChecked:
        for (int i = 0; i < m_model->rowCount(); i++)
        {
            if (m_model->item(i)->checkState() == Qt::Checked)
            {
                if (!text.isEmpty())
                {
                    text+= ", ";
                }

                text+= m_model->item(i)->text();
            }
        }
        break;

    default:
        text = m_unknownlyCheckedText;
    }

    lineEdit()->setText(text);
}

void CheckedComboBox::onModelDataChanged()
{
    updateText();
    emit globalCheckStateChanged(globalCheckState());
}

void CheckedComboBox::onItemPressed(const QModelIndex &index)
{
    QStandardItem* item = m_model->itemFromIndex(index);

    if (item->checkState() == Qt::Checked)
    {
        item->setCheckState(Qt::Unchecked);
    }
    else
    {
        item->setCheckState(Qt::Checked);
    }
}

void CheckedComboBox::CheckedComboBoxStyledItemDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    QStyleOptionViewItem & refToNonConstOption = const_cast<QStyleOptionViewItem &>(option);
    refToNonConstOption.showDecorationSelected = false;
    QStyledItemDelegate::paint(painter, refToNonConstOption, index);
}
