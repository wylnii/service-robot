#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class Label : public QLabel
{
    Q_OBJECT
public:
    Label(QWidget *parent = 0, int r = 80);

signals:
    void gestureActivated(int type = 0);

private:
    QList<QPoint> posList;
    const int radius;
    const QPoint p1,p2,p3,p4;

protected:
    void mousePressEvent(QMouseEvent *e);
};

#endif // LABEL_H
