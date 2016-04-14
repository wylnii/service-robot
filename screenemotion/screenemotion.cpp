#include "screenemotion.h"

const QString EmotionDir = "./emotion/";

ScreenEmotion::ScreenEmotion(QWidget *parent, QWidget *mainWind):QLabel(parent),
    p1(radius,radius), p2(radius,SCREEN_HEIGHT-radius), p3(SCREEN_WIDTH-radius,radius),p4(SCREEN_WIDTH-radius,SCREEN_HEIGHT-radius)
{
    Q_ASSERT(mainWind != NULL);
    mainWindow = mainWind;
    movie = new QMovie(this);
//    movie->setSpeed(20);
    setMovie(movie);
    emotionList.clear();
    emotions.clear();
    setFixedSize(SCREEN_WIDTH, SCREEN_HEIGHT);
    setWindowFlags(Qt::WindowStaysOnTopHint);
    setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    setMouseTracking(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Background,QColor(0,0,0));
    setPalette(pal);
    setScaledContents(true);
//    hide();
    searchEmotion();
    currentEmt = 0;
//    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &ScreenEmotion::autoChangeEmt);
//    timer->start(2000);
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

void ScreenEmotion::mousePressEvent(QMouseEvent *e)
{
#ifdef DEBUG
    qDebug()<<e->pos();
#endif
    int last = posList.count();
    if(last > 0)
    {
        if(((posList[last - 1] - e->pos())/radius).isNull())
            return;
    }
    posList.append(e->pos());
    if(posList.count()>3)
    {
        QPoint pot1((posList[last - 3] - p1)/radius/2);
        QPoint pot2((posList[last - 2] - p2)/radius/2);
        QPoint pot3((posList[last - 1] - p3)/radius/2);
        QPoint pot4((posList[last]       - p4)/radius/2);
//        qDebug()<<pot<<pot2;
        if(pot1.isNull() && pot2.isNull() && pot3.isNull() && pot4.isNull())
        {
            emit changeWindows();
            exHide();
            posList.clear();
        }
        else
        {
            posList.removeFirst();
        }
    }
}
