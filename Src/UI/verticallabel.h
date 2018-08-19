#ifndef VERTIcALLABEL_H
#define VERTIcALLABEL_H

#include <QLabel>

class VerticalLabel : public QLabel
{
    Q_OBJECT

public:
    explicit VerticalLabel(QWidget *parent = nullptr);
    explicit VerticalLabel(const QString &text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent*);
    QSize sizeHint() const ;
    QSize minimumSizeHint() const;
};

#endif // VERTIALLABEL_H
