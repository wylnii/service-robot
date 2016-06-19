#ifndef DOWNLOADER_H
#define DOWNLOADER_H

#include <QProcess>

class FTPDownloader : public QObject
{
    Q_OBJECT
public:
    explicit FTPDownloader(QObject *parent = 0);
    ~FTPDownloader();
    void startDownload(const QString& url);
    void startDownload();
    bool isRunning();
    QProcess::ProcessState state() const;

    void setURL(const QString &url);

signals:
    void finished(int code);

public slots:
    bool stop();
    void readMsg();
    void doFinish(int code);

private:
    QProcess *process;
    QString URL;
    QString FileName;
    QString tempFilename;
};

#endif // DOWNLOADER_H
