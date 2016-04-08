#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QProcess>

class AudioPlayer : public QObject
{
    Q_OBJECT
public:
    explicit AudioPlayer(QObject *parent = 0, const QString& server = QString("60.171.108.115"), int port = 20000);
    ~AudioPlayer();
    QString getRobotId() const;
    void setRobotId(const QString &id);
    void startAudioPlayer(const QString& robot_id);
    void startAudioPlayer();

    QString getServerIP() const;
    void setServer(const QString &ip, int port);
    bool isRunning();
    QProcess::ProcessState state() const;

signals:

public slots:
    bool stop();
    void readMsg();

private:
    QProcess *process;
    QString serverIP;
    int port;
    QString robotID;

};

#endif // AUDIOPLAYER_H
