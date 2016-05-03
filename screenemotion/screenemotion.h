#ifndef SCREENFACE_H
#define SCREENFACE_H

#include <QtCore>
#include <QtWidgets>
#include <QLabel>
#include <QMovie>
#include "global.h"
#include "label.h"

class ScreenEmotion : public Label
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
    void getGesture(int type);
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

private:
    QMovie *movie;
    QHash<int, QString> emotionList;
//    QTimer *timer;
    int currentEmt;
    QWidget *mainWindow;
};

#endif // SCREENFACE_H
