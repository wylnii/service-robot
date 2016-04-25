#include "screenemotion.h"

const QString EmotionDir = "./emotion/";

ScreenEmotion::ScreenEmotion(QWidget *parent, QWidget *mainWind):Label(parent)
{
    Q_ASSERT(mainWind != NULL);
    mainWindow = mainWind;
    movie = new QMovie(this);
//    movie->setSpeed(20);
    setMovie(movie);
    emotionList.clear();
    emotions.clear();
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
//    hide();
    searchEmotion();
    setMovieFile(emotionList[service]);
    currentEmt = 0;
//    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &ScreenEmotion::autoChangeEmt);
//    timer->start(2000);
    connect(this,&Label::gestureActivated,this, &ScreenEmotion::getGesture);
}

void ScreenEmotion::setMovieFile(const QString &path)
{
    if(QFile::exists(path))
    {
        movie->stop();
        movie->setFileName(path);
//        movie->setScaledSize(this->size());
        qDebug()<<"changeEmotion : "<<path;
    }
}

void ScreenEmotion::addEmotion(int type, const QString &fileName)
{
    if(QFile::exists(fileName))
    {
        emotionList.insert(type, fileName);
    }
}

void ScreenEmotion::searchEmotion()
{
    QDir dir(EmotionDir);
    QStringList filelist = dir.entryList(QStringList()<<"*.gif"<<"*.png"<<"*.jpeg"<<"*.jpg");
    emotions.clear();
    foreach (QString file, filelist)
    {
        QString filename = QFileInfo(file).completeBaseName().toLower();
        Emotion mot = EmotionCount;
        if(filename == "connect")
            mot = connecting;
        else if(filename == "idle")
            mot = idle;
        else if(filename == "search_wait")
            mot = search_wait;
        else if(filename == "service")
            mot = service;
        else if(filename == "shy")
            mot = shy;
        else if(filename == "talk")
            mot = talk;
        else if(filename == "voicelisten")
            mot = voiceListen;

        if(mot != EmotionCount)
        {
            emotionList.insert(mot, file.prepend(EmotionDir));
            emotions.append(filename);
        }
    }
}

void ScreenEmotion::getGesture(int type)
{
    if(type == 0)
    {
        exHide();
        emit changeWindows();
    }
}

void ScreenEmotion::changeEmotion(Emotion emotion)
{
    if(emotion < EmotionCount && emotion >= 0)
    {
        setMovieFile(emotionList[emotion]);
        startMovie();
    }
}

void ScreenEmotion::startMovie()
{
    if(movie->isValid())
    {
        movie->start();
    }
}

void ScreenEmotion::stopMovie()
{
    movie->stop();
}

void ScreenEmotion::show()
{
    if(isHidden())
    {
        mainWindow->hide();
        QWidget::show();
        startMovie();
    }
}

void ScreenEmotion::hide()
{
    if(! isHidden())
    {
        QWidget::hide();
        movie->stop();
    }
}

void ScreenEmotion::exHide()
{
    if(! isHidden())
    {
        hide();
        mainWindow->show();
        movie->stop();
    }
}

void ScreenEmotion::autoChangeEmt()
{
    changeEmotion((Emotion)(currentEmt++));
    currentEmt%=EmotionCount;
}

void ScreenEmotion::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    if(cmd.type == SSDB_CTRL_Emotion)
    {
        changeEmotion((Emotion)cmd.emotinIndex);
    }
}
