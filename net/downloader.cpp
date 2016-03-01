#include "downloader.h"

Downloader::Downloader(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    file = new QFile(this);
    thread = new QThread(this);
//    thread->start();
//    moveToThread(thread);
    downloading = false;
}

Downloader::~Downloader()
{
    thread->quit();
    thread->wait();
    delete manager;
    delete file;
    delete thread;
}

void Downloader::setURL(const QString &url)
{
    URL = url;
}

void Downloader::doFinish()
{
    file->flush();
    file->close();
    downloading = false;
    qDebug()<<file->size()<<QString::number((double)file->size()/timer.elapsed(),'f',2).append(" KB/s")<<timer.elapsed();
    timer.invalidate();
    emit finished();
}

void Downloader::doSslErrors(QNetworkReply::NetworkError err)
{
    qDebug()<<err<<reply->errorString();
    reply->disconnect();
    stopDownload();
}

void Downloader::readData(qint64 bytesReceived, qint64 bytesTotal)
{
    QByteArray rcv = reply->readAll();
    file->write(rcv);
    qDebug()<<bytesReceived<<bytesTotal<<QString::number((double)bytesReceived/timer.elapsed(),'f',2)<<timer.elapsed();
}

void Downloader::readData()
{
    QByteArray rcv = reply->readAll();
    file->write(rcv);
}

void Downloader::startDownload(const QString &url)
{
    if(! file->isOpen())
    {
        QFileInfo info(url);

        file->setFileName(info.fileName());
        URL = url;
        if(file->open(QFile::WriteOnly))
        {
            reply = manager->get(QNetworkRequest(url));
//            connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(readData(qint64,qint64)));
            connect(reply,SIGNAL(readyRead()),this,SLOT(readData()));
            connect(reply,SIGNAL(finished()),this,SLOT(doFinish()));
            connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(doSslErrors(QNetworkReply::NetworkError)));
            downloading = true;
            timer.start();
        }
    }
}

void Downloader::startDownload()
{
    startDownload(URL);
}

void Downloader::stopDownload()
{
    reply->disconnect();
    file->close();
    if(file->exists())
    {
        file->remove();
    }
    downloading = false;
}

QString Downloader::getURL() const
{
    return URL;
}

bool Downloader::isDownloading()
{
    return downloading;
}

