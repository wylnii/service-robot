#include "usb_wifi.h"
#include <QApplication>
#include <QNetworkInterface>

USB_WiFi::USB_WiFi(QObject  *parent) : QObject(parent)
{
    process = new QProcess;
    connetct_ssid="";
    retry = 0;
}
USB_WiFi::~USB_WiFi()
{
    delete process;
}


bool USB_WiFi::WiFi_exist()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface, list)
    { //遍历每一个网络接口
        if(interface.name() == "wlan0")
            return true;
    }
        return false;
}

QList<QStringList> USB_WiFi::scan_wifi(int update)
{
    QMutexLocker locker(&mutex);

    QElapsedTimer timer;
    timer.start();
    if(update == 1)
        qDebug()<<"update_scan thread:"<<QThread::currentThread();
    else if(update == 0)
        qDebug()<<"scan_wifi thread:"<<QThread::currentThread();
    if(update != 2)
        emit errormsg(QString("scan wifi ...").prepend(update ? "update ":""));
    QApplication::processEvents();
    QStringList header;
    header<<"SSID"<<"Intensity"<<"state";
    QList<QStringList> result;
    result.append(header);
    process = new QProcess();
    process->start("scan-wifi");
    QStringList line;
    if(process->waitForStarted())
    {
        if(process->waitForReadyRead(8000))
        {
            QByteArray ret;
            while (process->bytesAvailable() > 0)
            {
                ret = process->readLine();
                line.append(ret);
                qDebug()<<ret;
            }
            if(process->state() != 0)
                process->kill();
        }
    }
    else
        return result;

    QString info;
    QStringList list;
    if(line.count() > 1)
        for (int i=0;i<line.count()-1;i++)
        {
            info = line[i];
            QString Intensity = "NULL";
            QString SSID = "<hidden>";
            QString state="open";
            Intensity = info.mid(1,4).trimmed();

            int len = 0;
            if(info.right(13).count("(Security)") == 1)
            {
                state="locked";
                len = info.lastIndexOf('(')-7;
                if(len > 0)
                    SSID = info.mid(6,len);
            }
            else
               len = info.lastIndexOf('\n')-6;
            if(len > 0)
                SSID = info.mid(6,len);
            if(SSID == connetct_ssid && ! connetct_ssid.isEmpty())
                state = "connected";
            list.clear();
            list<<SSID<<Intensity<<state;
            result.append(list);
        }
    emit errormsg(QString("scan wifi completed! %1s").arg(timer.elapsed()/1000.0, 0, 'f', 3));
    return result;
}

bool USB_WiFi::connect_wifi(QString ssid,QString state,QString passcode)
{
    QMutexLocker locker(&mutex);

    qDebug()<<"connect_wifi thread:"<<QThread::currentThread();
    qDebug()<<QString("SSID:%1 state: %2").arg(ssid,state);
    QString cmd;
    QString type;

    if(state == "open")
    {
        type = "none";
        cmd = QString("start-wifi %2 %1").arg(ssid,type);
        emit errormsg(QString("connecting open wifi ..."));
        if(! connect_wifi_by_(cmd, ssid, type))
            return false;
    }
    else
    {
        type = "wpa";
        cmd = QString("start-wifi %3 %1 %2").arg(ssid,passcode,type);
        emit errormsg(QString("connecting %1 wifi ...").arg(type));
        if(! connect_wifi_by_(cmd, ssid, type))
        {
            type = "wpa2";
            cmd = QString("start-wifi %3 %1 %2").arg(ssid,passcode,type);
            emit errormsg(QString("connecting %1 wifi ...").arg(type));
            return connect_wifi_by_(cmd, ssid, type);
//            if(! connect_wifi_by_(cmd, ssid, type))
//            {
//                type = "wep";
//                cmd = QString("start-wifi %3 %1 %2").arg(ssid,passcode,type);
//                emit errormsg(QString("connecting %1 wifi ...").arg(type));
//                return connect_wifi_by_(cmd, ssid, type);
//            }
        }
    }
//    update_scan();//when you connect the wifi,you should run this to update the view tablelist;
    return true;
}

bool USB_WiFi::stop_wifi()
{
    QMutexLocker locker(&mutex);

    retry = 0;
    emit errormsg("Disconnect wifi ...");
    process = new QProcess;
    process->start("stop-wifi");
    if(process->waitForStarted())
    {
        QString ret;
        if(process->waitForFinished(), ret = process->readAll(), ret.isEmpty())
        {
            emit errormsg("Disconnect wifi success!");
            connetct_ssid.clear();
            locker.unlock();
            scan_wifi(2);
            return true;
        }
        emit errormsg(QLatin1String("<font color = 'red'>Disconnect wifi failed!</font> : ")+ret);
    }
    return false;
}

bool USB_WiFi::connect_wifi_by_(const QString &cmd, const QString &ssid, const QString &type)
{
    short ip_mark = 0, connect_mark = 0;
    QElapsedTimer t;
    t.start();

    delete process;
    process = new QProcess();
    process->start(cmd);
    if(process->waitForStarted())
    {
//        if(! process->waitForFinished(5000))
//            process->kill();
        QByteArray ret;
        while(ret.count("Sending discover...") < 4 && t.elapsed() < 8000)
        {
            qApp->processEvents();
            process->waitForReadyRead(3000);
            ret.append(process->readAll());
            if(ret.isEmpty())
                return false;
            if(ret.contains("Sending select for"))
                ip_mark=1;//找到IP
            if(ret.contains("adding dns"))
                connect_mark=1;//连接成功
            if(ip_mark && connect_mark) //connected
            {
                emit errormsg(QString("connect %1 success! (%2)").arg(ssid,type));
                connetct_ssid = ssid;
                process->waitForFinished(1000);
                qDebug() << ret;
                if(process->state() != QProcess::NotRunning)
                    process->kill();
                return true;
            }
        }
        qDebug() << ret;
    }
    emit errormsg(QString("<font color = 'red'>connect %1 failed!</font>").arg(ssid));
    connetct_ssid.clear();
    return false;
}
