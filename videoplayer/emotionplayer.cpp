#include "emotionplayer.h"
#include <QDebug>

EmotionPlayer::EmotionPlayer(QObject *parent, VideoPlayer *videoPlayer) : QObject(parent)
{
    currentIndex = 0;
    Q_ASSERT(videoPlayer);
    player = videoPlayer;
    connect(player,&VideoPlayer::replayEmotion,this,&EmotionPlayer::replay);

    m_thread = new QThread(this);
    m_thread->start();
    moveToThread(m_thread);
    searchEmotion();
}

EmotionPlayer::~EmotionPlayer()
{
    m_thread->quit();
    m_thread->wait(100);
    delete m_thread;
}

void EmotionPlayer::searchEmotion()
{
    static const QString EmotionDir = "./emotion/";
    QDir dir(EmotionDir);
    QStringList filters;
    filters<<"*.mkv"<<"*.mp4"<<"*.flv"<<"*.rm"<<"*.rmvb";
    QStringList filelist = dir.entryList(filters);
    emotionList.clear();
    EmotionList.clear();
    int index = 0;
    foreach (QString file, filelist)
    {
        QString filename = QFileInfo(file).completeBaseName();
        emotionList.insert(index++, file.prepend(EmotionDir));
        EmotionList.append(filename);
    }
    qDebug()<<"emotionlist:"<<EmotionList;
}

void EmotionPlayer::stop(bool repaint)
{
    player->stop(repaint);
}

void EmotionPlayer::changeEmotion(const QString &emotionName)
{
    int index = EmotionList.indexOf(emotionName);
    changeEmotion(index);
}

void EmotionPlayer::changeEmotion(int index)
{
    if(index < emotionList.size() && index >= 0)
    {
        currentIndex = index;
        playEmotion(emotionList[index]);
    }
    else
    {
        qDebug()<<"Emotion index ("<<index<<") out of range";
    }
}

void EmotionPlayer::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    switch (cmd.type)
    {
    case SSDB_CTRL_Emotion:
        if(cmd.emotionIndex >= 0)
            changeEmotion(cmd.emotionIndex);
        else
            changeEmotion(cmd.msg);
        break;
    case SSDB_CTRL_VideoCtrl:
        if(cmd.videoCtrl == Video_Stop)
        {
            QThread::msleep(100);
            playEmotion(emotionList[currentIndex]);
        }
        break;
    default:
        break;
    }
}

void EmotionPlayer::playEmotion()
{
    playEmotion(emotionList[currentIndex]);
}

void EmotionPlayer::replay()
{
//        qDebug()<<"emotion end:"<<emotionList[currentIndex];
    playEmotion(emotionList[currentIndex]);
}

void EmotionPlayer::playEmotion(const QString &filePath)
{
    qDebug()<<"changeEmotion : "<<filePath;
    int ret = 0;
    ret = player->play(filePath, 1);
    if(ret != 0)
    {
        return;
    }
}

