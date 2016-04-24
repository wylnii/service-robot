#ifndef VIDEOPLAYER_H
#define VIDEOPLAYER_H

#include <QObject>
#include <QtCore>
#include <QtWidgets>
#include <QTimer>
#include "global.h"
#include "audioplayer/audioplayer.h"

/*
class VideoThread : public QThread
{
    Q_OBJECT
public:
    VideoThread();
    ~VideoThread();
    bool play_stop;
    bool play_over;
    void stop();
    double position();
    double duration();

protected:
    void run();
};
*/

class VideoPlayer : public QThread
{
    Q_OBJECT
public:
    explicit VideoPlayer(QObject *parent = 0, QWidget *widget = 0);
    ~VideoPlayer();
    void setSource(const char *name);
    void setSource(const QString &name);
    void setVolume(int vol);
    int Volume();
    QString source() const;
    void Init();
    int openFile_and_getStream();
    void wait_for_end();
    void addToPlaylist(const QString &file, int que = -1);
    void removeFromPlaylist(const QString &file, int que = -1);
    double position() const;
    double duration() const;

    enum PlayMode{Cycle = 0, SingleCycle = 1, Single = 2};
    void setPlayMode(PlayMode mode);
    PlayMode getPlayMode() const;
    const QString &getPlayingFilename() const;
    const QStringList &getPlaylist() const;
    void setPlaylist(const QStringList &list);

    bool IsPlaying() const;
    bool IsPause() const;
    bool IsOpened() const;

    void setFace(QWidget *value);

protected:
    void run();
    void freeMem();
    void updateUI();

private:
    QThread *m_thread;
    QString filename;
    QStringList playlist;
    int playingNO;
    bool isOpened;
    bool isPlaying;
    bool Stop;
    quint64 play_cnt;
    PlayMode playMode;
    QTimer *timer;
    QWidget *face;
    AudioPlayer *audioPlayer;

public slots:
    int play();
    int play(const QString & file);
    int play(int no);
    void silence(const bool & s = 1);
    void replay();
    void pause();
    void stop(bool repaint = false);
    void playNext(int n = 1);
    void playLast(int l= 1);
    void getCtrlMsg(const SSDB_CtrlCmd &cmd);

signals:
    void playEnd();
    void returnMsg(const QString &list, int type);
    void stopAudioPlayer();
};

#endif // VIDEOPLAYER_H
