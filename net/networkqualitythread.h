#ifndef NETWORKQUALITY_H
#define NETWORKQUALITY_H

#include <QThread>
class QProcess;
class QElapsedTimer;
class QMutex;

class NetworkQualityThread : public QThread
{
    Q_OBJECT
public:
    explicit NetworkQualityThread(QObject *parent = 0);
    ~NetworkQualityThread();
    int getNetworkQuality(const QString &pattern = "") ;

private:
    bool stopProcess();
    QProcess *process;
    QElapsedTimer *m_timer;
    bool stop;
    QMutex *mutex;

signals:
    void updateNetworkQuality(int quality);

public slots:

protected:
    void run();
};

#endif // NETWORKQUALITY_H
