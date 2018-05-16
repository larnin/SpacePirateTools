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
public:
    ColliderLayerDialog(QWidget * parent = nullptr);

    unsigned int get() const;

    static unsigned int getNewLayerID(QWidget* parent, bool *ok = nullptr);

private:
    void updateLayerList();
    void updateColorButton(sf::Color color);
    void addPoints(unsigned int index);

    QListWidget * m_layerList;
    QPushButton * m_colorbutton;
    QSpinBox * m_r;
    QSpinBox * m_g;
    QSpinBox * m_b;
    QGridLayout * m_pointsLayout;

    std::vector<QWidget*> m_xLabels;
    std::vector<QWidget*> m_yLabels;
    std::vector<std::pair<sf::Vector2u, QWidget*>> m_checkboxs;
};

#endif // COLLIDERLAYERDIALOG_H
