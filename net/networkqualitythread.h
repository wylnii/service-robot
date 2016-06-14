#ifndef NETWORKQUALITY_H
#define NETWORKQUALITY_H

#include <QThread>
#include <QtCore>
#include "SSDB/ssdb_client_.h"

class NetworkQualityThread : public QThread
{
    Q_OBJECT
public:
    explicit NetworkQualityThread(QObject *parent = 0);
    ~NetworkQualityThread();
    int getNetworkQuality(const QString &pattern = "") ;

private:
    QProcess *process;
    QElapsedTimer *m_timer;
    bool stop;

signals:
    void updateNetworkQuality(int quality);

public slots:

protected:
    void run();
};

#endif // NETWORKQUALITY_H
