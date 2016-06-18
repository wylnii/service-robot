#include "networkqualitythread.h"
#include "global.h"

NetworkQualityThread::NetworkQualityThread(QObject *parent) : QThread(parent)
{
    stop = true;
    m_timer = new QElapsedTimer;
    process = NULL;
}

NetworkQualityThread::~NetworkQualityThread()
{
    stop = true;
    process->terminate();
    wait(1000);
    delete m_timer;
}

int NetworkQualityThread::getNetworkQuality(const QString &pattern)
{
    static const QString NetworkCMD = loadHistory("SSDB_server").prepend("ping -q -c 4 ");
    if(process == NULL)
    {
        process = new QProcess();
    }
    process->start(NetworkCMD);
    if(process->waitForFinished(8000))
    {
        QByteArray ret = process->readAll();
#ifndef _TEST
        static QRegExp reg("(\\d+)%.+/(\\d+\\.\\d+)/\\d+\\.\\d+");
#else
        static QRegExp reg("(\\d+)%.+/(\\d+\\.\\d+)/\\d+\\.\\d+/");
#endif
        //        qDebug()<<ret;
        if(pattern.length() > 0)
        {
            reg.setPattern(pattern);
        }
        if(reg.indexIn(ret) > 0 && reg.captureCount() > 1)
        {
            float loss = reg.cap(1).toFloat()/100;
            if(loss < 0 || loss >1)
                return -2;
            float quality = reg.cap(2).toFloat();
            if(quality < 0)
                return -2;
            //            qDebug()<<loss<<quality;
            quality = 5000/(quality+50)*(1 - loss);
            return (int)quality;
        }
    }
    else
    {
        process->terminate();
    }
    return -1;
}

void NetworkQualityThread::run()
{
    if(! stop)
        return;
    stop = false;
    process = new QProcess();
    qDebug()<<this<<this->thread()<<currentThread();
    while(! stop)
    {
        int quality = getNetworkQuality();
        emit updateNetworkQuality(quality);
        m_timer->start();
        while(! m_timer->hasExpired(10e3) && ! stop)
        {
            QThread::msleep(50);
        }
    }
    m_timer->invalidate();
}

