#ifndef KEYIN_H
#define KEYIN_H

#include <QObject>
class QSocketNotifier;

const int num_of_btns = 8;

class KeyInput : public QObject
{
    Q_OBJECT
public:
    explicit KeyInput(QObject *parent = 0);
    ~KeyInput();
signals:
    void keyChanged(int status);
    void keyPressed(uchar key, bool status);//1 press; 0 release;

public slots:
    void readData(int socket);

private:
    QSocketNotifier *notifier;
    int fd;
    char buttons[num_of_btns] = {'0', '0', '0', '0', '0', '0', '0', '0'};
    int pressed_btns;
};

#endif // KEYIN_H
