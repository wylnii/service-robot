#ifndef SCREENFACE_H
#define SCREENFACE_H

#include <QtCore>
#include <QtWidgets>
#include <QLabel>
#include <QMovie>
#include "global.h"

class ScreenEmotion : public QLabel
{
    Q_OBJECT
public:
    ScreenEmotion(QWidget *parent = 0, QWidget *mainWind = 0);
    enum Emotion{ connecting, idle, search_wait, service, shy, talk,\
                  voiceListen,  EmotionCount };
    void setMovieFile(const QString &path);
    void addEmotion(int type, const QString &fileName);
    void searchEmotion();

public slots:
    void changeEmotion(Emotion emotion);
    void startMovie();
    void stopMovie();
    void show();
    void hide();
    void exHide();
    void autoChangeEmt();
    void getCtrlMsg(const SSDB_CtrlCmd &cmd);

signals:
    void changeWindows(bool en = true);
    void initEmotions(const QStringList& list);

private:
    QMovie *movie;
    QHash<int, QString> emotionList;
    QList<QPoint> posList;
//    QTimer *timer;
    int currentEmt;
    QWidget *mainWindow;

    const int radius = 80;
    const QPoint p1,p2,p3,p4;

protected:
    void mousePressEvent(QMouseEvent *e);

};

#endif // SCREENFACE_H
