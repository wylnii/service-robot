#ifndef PASSWORD_WIN_H
#define PASSWORD_WIN_H

#include <QWidget>
#include <QMouseEvent>

namespace Ui {
class password_win;
}

class password_win : public QWidget
{
    Q_OBJECT

public:
    explicit password_win(QWidget *parent = 0);
    ~password_win();
    void clearpassword();
signals:
    void sendtext(QString t);
private slots:
    void textshow(QString t);

private:
    Ui::password_win *ui;
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    QPoint dragPosition;
};

#endif // PASSWORD_WIN_H
