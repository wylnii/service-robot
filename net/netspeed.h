#ifndef NETSPEED_H
#define NETSPEED_H

#include <QObject>
#include <QTimer>
class QFile;

class NetSpeed : public QObject
{
    Q_OBJECT
public:
    explicit NetSpeed(QObject *parent = 0);
    ~NetSpeed();
    qint64 currentSpeed();

signals:
    void getSpeed(qint64 speed);

public slots:
    void detectSpeed();

private:
    QThread *m_thread;
    QFile *file;
    QTimer timer;
    qint64 lastData;
    qint64 curData;
    qint64 speed;
};

#endif // NETSPEED_H
