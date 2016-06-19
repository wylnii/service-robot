#include "netspeed.h"
#include <QFile>
#include <QThread>

NetSpeed::NetSpeed(QObject *parent) : QObject(parent)
{
    lastData = 0;
    curData = 0;
    file = new QFile(this);
    file->setFileName("/proc/net/dev");
    timer.setInterval(1000);
    connect(&timer, &QTimer::timeout, this, &NetSpeed::detectSpeed);
    timer.start();
    m_thread = new QThread(this);
    m_thread->start();
    moveToThread(m_thread);
}

NetSpeed::~NetSpeed()
{
    timer.stop();
    m_thread->wait(1000);
//    delete file;
}

qint64 NetSpeed::currentSpeed()
{
    return speed;
}

void NetSpeed::detectSpeed()
{
    if(file->open(QFile::ReadOnly))
    {
        QString data = file->readAll();
        file->close();
        data = data.mid(data.lastIndexOf("eth0"));
        QStringList list = data.split(QRegExp("\\s"),QString::SkipEmptyParts);
        lastData = curData;
        curData = list[1].toInt();
        speed = curData - lastData;
        emit getSpeed(speed);
//        qDebug()<<speed;
    }
}

