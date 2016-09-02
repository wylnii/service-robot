#include "ffmpeg_sh.h"
#include <QApplication>

FFmpeg_sh::FFmpeg_sh(QObject *parent) : QObject(parent)
{
//    setvbuf(stdout, (char *)NULL, _IONBF, 0);
    hasfather=false;
    ipAddr = loadHistory("IP");
    device = loadHistory("Device");
    feed = loadHistory("Feed");

    process = new QProcess();
    timer = new QTimer(this);
    timer->setTimerType(Qt::VeryCoarseTimer);
    connect(timer,&QTimer::timeout,this,&FFmpeg_sh::readMsg);
    //    connect(process,SIGNAL(readyReadStandardError()),this,SLOT(readMsg()));
}

FFmpeg_sh::~FFmpeg_sh()
{
    timer->stop();
    process->kill();
}

int FFmpeg_sh::processState()
{
    if(hasfather)
        return (int)hasfather;
    else
        return process->state();
}

void FFmpeg_sh::rtsp_send(QString rtsp_ip, QString port, QString feed, QString Resolution, QString fps, QString bitrate, QString device)
{
    if(process->state() != 0)
    {
        emit errMsg("video already started");
        return;
    }

    if(! mutex.tryLock(1))
    return;

    short err_code = -1;

    qDebug()<<"rtsp_send thread:"<<QThread::currentThread();
    QString cmd;
    cmd = QString("/ffmpeg-x264-arm/bin/ffmpeg -f video4linux2 -s %1 -r %2  -i %7  -pix_fmt yuv422p -s %1 -r %2 -vcodec libx264 -b:v %3 -preset:v ultrafast -tune:v zerolatency -f rtsp rtsp://%4%5/%6.sdp")
            .arg(Resolution,fps,bitrate,rtsp_ip,port,feed,device);
//    cmd = "ping baidu.com";
    qDebug()<<"cmd:"<<cmd;

    process = new QProcess();
    process->start(cmd);
    process->setReadChannel(QProcess::StandardError);
    emit errMsg("Starting video...");
    if(process->waitForStarted())
    {
        QString msg;
        while(process->bytesAvailable()<1800 &&  process->waitForReadyRead(4000));

        msg = process->readAll();
        qDebug()<<msg;

        if(msg.count("libx264")>1)
        {
            qDebug()<<"cmd run successfully!";
            QApplication::processEvents();

            while(process->bytesAvailable()<440 &&  process->waitForReadyRead(10000));

            msg = process->readAll();
            qDebug()<<msg;
            if(msg.contains(QRegExp("frame=.+fps=.+time=")))
            {
                hasfather=true;
                emit errMsg("Video start working!");
                timer->start(3000);
                err_code = 0;
            }
            else if(msg.contains("Network is unreachable"))
            {
                emit errMsg("<font color = 'red'>Video start failed! : <b>Network is unreachable</b></font>");
                err_code = 1;
            }
            else if(msg.contains("No route to host"))
            {
                emit errMsg("<font color = 'red'>Video start failed! : <b>No route to host</b></font>");
                err_code = 6;
            }
            else if(msg.isEmpty())
            {
                emit errMsg("<font color = 'red'>Video start failed! : <b>IP or Server may be error</b></font>");
                err_code = 2;
            }
            else
            {
                err_code = -2;
            }
        }
        else if(msg.contains("No such file or directory"))
        {
            emit errMsg("<font color = 'red'>Video start failed! : <b>No such device</b></font>");
            err_code = 3;
        }
        else if(msg.contains("Not a video capture device"))
        {
            emit errMsg("<font color = 'red'>Video start failed! : <b>Not a video capture device</b></font>");
            err_code = 4;
        }
        else if(msg.contains("Device or resource busy"))
        {
            emit errMsg("<font color = 'red'>Video start failed! : <b>Device  busy</b></font>");
            hasfather = 1;
            err_code = 5;

            QProcess p,p1;
            p.setStandardOutputProcess(&p1);
            p.start("ps -w");
            p1.start(QLatin1String("grep ")+cmd.left(20));
            if(p.waitForStarted() && p1.waitForStarted())
            {
                if(p.waitForFinished() && p1.waitForFinished())
                {
                    QString ret = p1.readLine();

                    qDebug()<<ret;
                    p.start(QString("kill -s 9 ").append(ret.split(' ',QString::SkipEmptyParts).at(0)));
                    p.waitForReadyRead();
                    if(p.readAll().isEmpty() && p.readAllStandardError().isEmpty())
                        qDebug()<<"kill succeed";
                }
            }
        }
        else
        {
            err_code = -3;
        }
    }
    else
    {
        qDebug()<<process->errorString();
        err_code = -1;
        emit errMsg(QString("<font color = 'red'>Video start failed!  : <b>%1</b></font>").arg(process->errorString()));
    }

    if(err_code < -1)
    {
        emit errMsg(QString("<font color = 'red'>Video start failed!  : <b>err_code %1</b></font>").arg(err_code));
    }
    if(err_code != 0)
    {
        if(process->state() != 0)
            process->kill();
        qDebug()<<"##ERROR\terr_code :"<<err_code;
    }
    mutex.unlock();
}

void FFmpeg_sh::stopProcess()
{
    if(! mutex.tryLock(1))
    return;

    emit errMsg("Video stopping...");
    process->waitForFinished(1000);
    if(process->state() != 0)
        process->kill();
    emit errMsg("Video stoped");
    hasfather = 0;
    mutex.unlock();
}

void FFmpeg_sh::readMsg()
{
    if(hasfather)
    {
        retMsg = process->readAll();
        QRegExp reg("frame=[^r]+bitrate=[^r\\s]+");
        if(reg.indexIn(retMsg) != -1)
        {
//            emit errMsg(retMsg = reg.cap(0),1);
            fprintf(stderr, "\033[32m%s\033[0m", retMsg.append('\r').toLatin1().constData());
        }
    }
    else
        timer->stop();
}
