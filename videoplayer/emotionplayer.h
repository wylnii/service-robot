#ifndef EMOTIONPLAYER_H
#define EMOTIONPLAYER_H

#include <QObject>
#include <videoplayer/videoplayer.h>

class EmotionPlayer : public QObject
{
    Q_OBJECT
public:
    explicit EmotionPlayer(QObject *parent = 0, VideoPlayer *videoPlayer = 0);
    ~EmotionPlayer();
    void searchEmotion();
    void stop(bool repaint = false);

signals:

public slots:
    void changeEmotion(const QString &emotion);
    void changeEmotion(int index);
    void getCtrlMsg(const SSDB_CtrlCmd &cmd);
    void getGesture(int type);

private:
    void playEmotion(const QString &filePath);
    void replay();
    QThread *m_thread;
    VideoPlayer *player;
    QHash<int, QString> emotionList;
    int currentIndex;

};

#endif // EMOTIONPLAYER_H
