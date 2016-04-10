#include "audioplayer.h"
#include <QDebug>
#include <QThread>

const QString AUDIO_PROGRAM = "./audioPlayer";

AudioPlayer::AudioPlayer(QObject *parent, const QString &server, int port)
    : QObject(parent), serverIP(server), port(port)
{
    process = new QProcess(this);
    process->setProgram(AUDIO_PROGRAM);
    connect(process,SIGNAL(readyRead()),this,SLOT(readMsg()));
}

AudioPlayer::~AudioPlayer()
{
    stop();
}

QString AudioPlayer::getRobotId() const
{
    return robotID;
}

void AudioPlayer::setRobotId(const QString &id)
{
    if(id.isEmpty())
    {
        qDebug()<<this<<"robotID is error!";
    }
    robotID = id;
}

void AudioPlayer::startAudioPlayer(const QString &robot_id)
{
    if(isRunning())
    {
        qDebug()<<this<<"is already running!";
        return;
    }
    if(robot_id.isEmpty() || serverIP.isEmpty() || port <1)
    {
        qDebug()<<this<<"args err!";
        return;
    }
    robotID = robot_id;
    process->setArguments(QStringList()<<serverIP<<QString::number(port)<<robot_id);
    process->start();
    qDebug()<<this<<"PID:"<<process->pid();
}

void AudioPlayer::startAudioPlayer()
{
//TODO
//    startAudioPlayer(robotID);
}

bool AudioPlayer::stop()
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

void AudioPlayer::setServer(const QString &ip, int port)
{
    this->serverIP = ip;
    this->port = port;
}

bool AudioPlayer::isRunning()
{
    return process->state() != QProcess::NotRunning;
}

QProcess::ProcessState AudioPlayer::state() const
{
    return process->state();
}

void AudioPlayer::readMsg()
{
    qDebug()<<process->readAll();
}
