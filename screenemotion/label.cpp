#include "label.h"
#include <QMouseEvent>
#include <QDebug>
#include "global.h"

Label::Label(QWidget *parent, int r):QLabel(parent),radius(r),
p1(radius,radius), p2(radius,SCREEN_HEIGHT-radius), p3(SCREEN_WIDTH-radius,radius),p4(SCREEN_WIDTH-radius,SCREEN_HEIGHT-radius)
{
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setMouseTracking(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,QColor(0,0,0));
    setPalette(pal);
    setScaledContents(true);
}

void Label::mousePressEvent(QMouseEvent *e)
{
#ifdef DEBUG
    qDebug()<<e->pos();
#endif
    int last = posList.count();
    if(last > 0)
    {
        if(((posList[last - 1] - e->pos())/radius).isNull())
            return;
    }
    posList.append(e->pos());
    static const int diameter = radius*2;
    if(posList.count()>3)
    {
        QPoint pot1((posList[last - 3] - p1)/diameter);
        QPoint pot2((posList[last - 2] - p2)/diameter);
        QPoint pot3((posList[last - 1] - p3)/diameter);
        QPoint pot4((posList[last]       - p4)/diameter);
//        qDebug()<<pot<<pot2;
        if(pot1.isNull() && pot2.isNull() && pot3.isNull() && pot4.isNull())
        {
            emit gestureActivated();
            posList.clear();
        }
        else
        {
            posList.removeFirst();
        }
    }
}

