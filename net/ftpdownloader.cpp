#include "ftpdownloader.h"
#include <QDebug>
#include <QThread>
#include <QFileInfo>
#include <QDir>

const QString PREFIX = "/video/";

FTPDownloader::FTPDownloader(QObject *parent) : QObject(parent)
{
    process = new QProcess(this);
    process->setProgram("wget");
    process->setReadChannel(QProcess::StandardError);
    connect(process,&QProcess::readyRead,this,&FTPDownloader::readMsg);
    connect(process,static_cast<void (QProcess::*)(int)>(&QProcess::finished),this,&FTPDownloader::doFinish);
    QDir dir(PREFIX);
    if(! dir.exists())
    {
        dir.mkdir(PREFIX);
    }
}

FTPDownloader::~FTPDownloader()
{
    stop();
    delete process;
}

void FTPDownloader::startDownload(const QString &url)
{
    if(isRunning())
    {
        qDebug()<<this<<"is already running!";
        return;
    }
    if(! url.isEmpty())
    {
        QFileInfo info(url);
        FileName = info.fileName();
        tempFilename = FileName+".temp";
        QFile(tempFilename).remove();
        qDebug()<<FileName;
        URL = url;
        process->setArguments(QStringList()<<URL<<"-O"<<tempFilename);
        process->start();
    }
}

void FTPDownloader::startDownload()
{
    startDownload(URL);
}

bool FTPDownloader::isRunning()
{
    return process->state() != QProcess::NotRunning;
}

QProcess::ProcessState FTPDownloader::state() const
{
    return process->state();
}

bool FTPDownloader::stop()
{
    if(isRunning())
    {
        process->terminate();
        process->waitForFinished(100);
        qDebug()<<this<<isRunning();
        if(isRunning())
        {
            process->kill();
            process->waitForFinished(100);
            qDebug()<<this<<"-->"<<isRunning();
            return !isRunning();
        }
    }
    return true;
}

void FTPDownloader::readMsg()
{
    QRegExp exp("\\d+%");
    if(exp.indexIn(process->readAll()) >= 0)
    {
        qDebug()<<(exp.cap());
    }
}

void FTPDownloader::doFinish(int code)
{
    if(code == 0)
    {
        QFile file(PREFIX+FileName);
        int size = file.size();
        file.setFileName(tempFilename);
        int size0 = file.size();
        if(size != size0)
        {
            QString cmd = QString("mv -f %1 %2").arg(file.fileName(),PREFIX+FileName);
            system(cmd.toLocal8Bit().constData());
            qDebug()<<cmd;
        }
    }
    QFile file(tempFilename);
    if(file.exists())
    {
        file.remove();
    }
    qDebug()<<"download finish:"<<code;
    emit finished(code);
}

void FTPDownloader::setURL(const QString &url)
{
    URL = url;
}

