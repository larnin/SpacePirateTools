#ifndef QSFMLCANVAS_H
#define QSFMLCANVAS_H

#include <QWidget>
#include <QTimer>
#include <SFML/Graphics/RenderWindow.hpp>

class QSFMLCanvas : public QWidget, public sf::RenderWindow
{
    Q_OBJECT
public:
    explicit QSFMLCanvas(unsigned int FrameTime = 20, QWidget *parent = nullptr);

protected:
    virtual void showEvent(QShowEvent*) override;
    virtual QPaintEngine* paintEngine() const override;
    virtual void paintEvent(QPaintEvent*) override;
    virtual void OnUpdate() = 0;
    virtual void resizeEvent(QResizeEvent * event) override;

private:
    QTimer m_timer;
    bool m_initialized;
};

#endif // QSMLCANVAS_H
