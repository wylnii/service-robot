#include "emotionplayer.h"

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
    emotions.clear();
    emotionList.clear();
    int index = 0;
    foreach (QString file, filelist)
    {
        QString filename = QFileInfo(file).completeBaseName().toLower();
        emotionList.insert(index++, file.prepend(EmotionDir));
        emotions.append(filename);
    }
    qDebug()<<"emotionlist:"<<emotionList;
}

void EmotionPlayer::stop(bool repaint)
{
    player->stop(repaint);
}

void EmotionPlayer::changeEmotion(const QString &emotionName)
{
    int index = emotions.indexOf(emotionName);
    changeEmotion(index);
}

void EmotionPlayer::changeEmotion(int index)
{
    if(index < emotionList.size() && index >= 0)
    {
        currentIndex = index;
        playEmotion(emotionList[index]);
    }
}

void EmotionPlayer::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    switch (cmd.type)
    {
    case SSDB_CTRL_Emotion:
        if(cmd.emotinIndex >= 0)
            changeEmotion(cmd.emotinIndex);
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

void EmotionPlayer::getGesture(int type)
{
    switch (type)
    {
    case 0:
        emit changeWindows();
        break;
    default:
        break;
    }
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

