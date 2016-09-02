#ifndef FFMPEG_SH_H
#define FFMPEG_SH_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QProcess>
#include <global.h>

class FFmpeg_sh : public QObject
{
    Q_OBJECT
public:
    explicit FFmpeg_sh(QObject *parent = 0);
    ~FFmpeg_sh();
    QProcess *process;
    QString ipAddr;
    QString device;
    QString feed;
    int processState();

private:
    bool hasfather;
    QMutex mutex;
    QTimer *timer;
    QString retMsg;

signals:
    void errMsg(QString, bool type = 0);

public slots:
    void rtsp_send(QString rtsp_ip, QString port, QString feed, QString Resolution, QString fps, QString bitrate, QString device);
    void stopProcess();
    void readMsg();
};

#endif // FFMPEG_SH_H
