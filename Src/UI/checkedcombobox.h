#ifndef CHECKEDCOMBOBOX_H
#define CHECKEDCOMBOBOX_H

#include <QWidget>
#include <QComboBox>
#include <QStandardItemModel>
#include <QLineEdit>
#include <QEvent>
#include <QStyledItemDelegate>
#include <QListView>

/**
 * @brief QComboBox with support of checkboxes
 * http://stackoverflow.com/questions/8422760/combobox-of-checkboxes
 * https://gist.github.com/mistic100/c3b7f3eabc65309687153fe3e0a9a720
 */
class CheckedComboBox : public QComboBox
{
    Q_OBJECT

public:
    class CheckedComboBoxStyledItemDelegate : public QStyledItemDelegate
    {
    public:
        CheckedComboBoxStyledItemDelegate(QObject* parent = nullptr) : QStyledItemDelegate(parent) {}

        void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    };

    /**
     * @brief Additional value to Qt::CheckState when some checkboxes are Qt::PartiallyChecked
     */
    static const int StateUnknown = 3;

    CheckedComboBox(QWidget* parent = nullptr);
    ~CheckedComboBox() { delete m_model; }

    void setAllCheckedText(const QString &text);
    void setNoneCheckedText(const QString &text);
    void setUnknownlyCheckedText(const QString &text);

    /**
     * @brief Adds a item to the checklist (setChecklist must have been called)
     * @return the new QStandardItem
     */
    QStandardItem* addCheckItem(const QString &label, const QVariant &data, const Qt::CheckState checkState);
    QStandardItem* addCheckItem(const QString &label, const Qt::CheckState checkState = Qt::CheckState::Unchecked);

    /**
     * @brief Computes the global state of the checklist :
     *      - if there is no item: StateUnknown
     *      - if there is at least one item partially checked: StateUnknown
     *      - if all items are checked: Qt::Checked
     *      - if no item is checked: Qt::Unchecked
     *      - else: Qt::PartiallyChecked
     */
    int globalCheckState() const;
    Qt::CheckState checkState(int index) const;
    unsigned int checkStateBitSet() const;

protected:
    bool eventFilter(QObject* object, QEvent* event);

private:
    void updateText();

signals:
    void globalCheckStateChanged(int);

private slots:
    void onModelDataChanged();
    void onItemPressed(const QModelIndex &index);


private:
    QStandardItemModel* m_model;
    /**
     * @brief Text displayed when no item is checked
     */
    QString m_noneCheckedText = "Nothing";
    /**
     * @brief Text displayed when all items are checked
     */
    QString m_allCheckedText = "Everything";
    /**
     * @brief Text displayed when some items are partially checked
     */
    QString m_unknownlyCheckedText = "Unknown";
};

#endif // CHECKEDCOMBOBOX_H
