#include "login.h"
#include <QTimer>

const QString LOGIN_URL = "http://60.171.108.115:8076/rb/"
                          "t_loginbyrobot.aspx?action=login&robotcode=%1&password=%2";
const QString LOGOUT_URL = "http://60.171.108.115:8076/rb/"
                          "t_loginbyrobot.aspx?action=logout&robotid=%1&key=%2";
const QString DATA_URL = "http://60.171.108.115:8076/rb/"
                         "t_getmaterial.aspx?action=queryall&robotid=%1&key=%2";

Login::Login(QObject *parent) : QObject(parent)
{
    manager = new QNetworkAccessManager();
    mThread = new QThread(this);
    mThread->start();
    moveToThread(mThread);

    data.clear();
    key.clear();
    robotId = 0;
    URL.clear();
    return_code = 0;
    isOnline = false;
}

Login::~Login()
{
    if(isOnline)
        logout();
    mThread->quit();
    qDebug()<<"quit";
    mThread->wait();
    delete manager;
    delete mThread;
}

int Login::login()//blocked
{
    if(userName.isEmpty() || userPassword.isEmpty())
    {
        qDebug()<<"userData is incompleted!";
        return -1;
    }
    key.clear();
    request(LOGIN_URL.arg(userName).arg(userPassword));
    qDebug()<<data;
    QRegExp exp("result=(\\d+)\\rrobotid=(\\d+)\\rkey=([\\w]+)");
    exp.indexIn(data);
    int result_code = exp.cap(1).toInt();
    if(result_code == 0 || exp.captureCount() != 3)
    {
        return_code = -1;//err
        return return_code;
    }

    robotId = exp.cap(2).toInt();
    key = exp.cap(3);

    qDebug()<<robotId<<key;
    if(return_code == 0)
        isOnline = true;
    return return_code;
}

int Login::login(const QString &name, const QString &password)
{
    setUserData(name, password);
    return login();
}

int Login::logout()
{
    if(!isOnline)
    {
        qDebug()<<"please login first!";
        return -3;
    }
    if(key.isEmpty())
    {
        qDebug()<<"key is empty!";
        return -1;
    }
    request(LOGOUT_URL.arg(robotId).arg(key));

    qDebug()<<data;
    QRegExp exp("result=(\\d+)");
    exp.indexIn(data);
    int result_code = exp.cap(1).toInt();
    if(result_code == 0)
    {
        return_code = -1;//err
        return return_code;
    }

    isOnline = false;
    return 0;
}

int Login::getMaterial()
{
    if(!isOnline)
    {
        qDebug()<<"please login first!";
        return -3;
    }
    if(key.isEmpty())
    {
        qDebug()<<"key is empty!";
        return -1;
    }
    request(DATA_URL.arg(robotId).arg(key));
    QRegExp exp("result=(\\d+)\\nforce=(\\d+)\\|version=(\\d+)\\|URL=(.+)\\n");
    exp.indexIn(data);
    int result_code = exp.cap(1).toInt();
    if(result_code == 0 || exp.captureCount() != 4)
    {
        return_code = -2;//err
        return return_code;
    }

    URL = exp.cap(4);

    qDebug()<<exp.cap(2)<<exp.cap(3)<<URL;
    return return_code;
}

void Login::setUserData(const QString &name, const QString &password)
{
    userName = name;
    userPassword = password;
}

void Login::doFinish()
{
//    qDebug()<<data;
//    qDebug()<<QString::number((double)data.length()/timer.elapsed(),'f',2).append(" KB/s")<<timer.elapsed();
    timer.invalidate();
    emit finished(return_code);
}

void Login::doSslErrors(QNetworkReply::NetworkError err)
{
    qDebug()<<err<<reply->errorString();
    reply->disconnect();
    return_code = err;
}

void Login::readData(qint64 bytesReceived, qint64 bytesTotal)
{
    data.append(reply->readAll());
    qDebug()<<bytesReceived<<bytesTotal<<QString::number((double)bytesReceived/timer.elapsed(),'f',2)<<timer.elapsed();
}

void Login::readData()
{
    data.append(reply->readAll());
}

void Login::request(const QString &url)//blocked
{
    data.clear();
    return_code = 0;
    reply = manager->get(QNetworkRequest(url));
//            connect(reply,SIGNAL(downloadProgress(qint64,qint64)),this,SLOT(readData(qint64,qint64)));
    connect(reply,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(reply,SIGNAL(finished()),this,SLOT(doFinish()));
    connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(doSslErrors(QNetworkReply::NetworkError)));
    timer.start();
    QObject::connect(this,SIGNAL(finished(int)),&loop,SLOT(quit()));
    QObject::connect(reply,SIGNAL(error(QNetworkReply::NetworkError)),&loop,SLOT(quit()));
    QTimer::singleShot(2000,
                       [&](void)
    {
        if(loop.isRunning())
        {
            qDebug()<<"timeout";
            loop.quit();
            return_code = -3;
            emit error(return_code);
        }
    });
    loop.exec();
}

QString Login::getURL() const
{
    return URL;
}

int Login::getReturnCode() const
{
    return return_code;
}
