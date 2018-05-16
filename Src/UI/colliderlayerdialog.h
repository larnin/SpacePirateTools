#ifndef COLLIDERLAYERDIALOG_H
#define COLLIDERLAYERDIALOG_H

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
#include <QDialog>
#include <QListWidget>
#include <QPushButton>
#include <QSpinBox>
#include <QLineEdit>
#include <QGridLayout>

class ColliderLayerDialog : public QDialog
{
    Q_OBJECT
public:
    ColliderLayerDialog(bool haveValidButton, QWidget * parent = nullptr);

    unsigned int get() const;

    static unsigned int getNewLayerID(bool showButtons, QWidget* parent, bool *ok = nullptr);

public slots:
    void onCheck(unsigned int x, unsigned int y, Qt::CheckState state);
    void onRightClickLayerList(QPoint point);

private:
    void updateLayerList();
    QIcon makeIcon(const sf::Color & color);
    void setPoints();

    QListWidget * m_layerList;
    QGridLayout * m_pointsLayout;

    std::vector<QWidget*> m_xLabels;
    std::vector<QWidget*> m_yLabels;
    std::vector<std::pair<sf::Vector2u, QWidget*>> m_checkboxs;
};

#endif // COLLIDERLAYERDIALOG_H
