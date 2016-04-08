#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QObject>
#include <QtNetwork>

class Downloader : public QObject
{
    Q_OBJECT
public:
    explicit Downloader(QObject *parent = 0);
    ~Downloader();
    void setURL(const QString &url);
    QString getURL() const;
    bool isDownloading();

signals:
    void finished();

public slots:
    void doFinish();
    void doSslErrors(QNetworkReply::NetworkError err);
    void readData(qint64 bytesReceived, qint64 bytesTotal);
    void readData();
    void startDownload(const QString &url);
    void startDownload();
    void stopDownload();

private:
    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QFile *file;
    QElapsedTimer timer;
    QString URL;
    bool downloading;
    QThread *thread;

};

#endif // DOWNLOADER_H
