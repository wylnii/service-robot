#include "ssdb_client_.h"

using namespace ssdb;
using namespace std;

const char* Query_KEY = "event";
const char* DirCtrl_CMD = "DirCtl";
const char* Param_CMD = "setparam";
const char* Param_KEY = "param";
const char* Video_CMD = "VideoPlay";
const char* VideoInfo_KEY = "VideoInfo";
const char* VideoPlayList_KEY = "VideoPlayList";

const char* EndVideo_CMD = "EndVideo";
const char* EndDirCtrl_CMD = "EndDirCtl";

SSDB_Client::SSDB_Client(QObject *parent, const QString &name, const QString &addr, int port):\
    QThread(parent), serverAddr(addr), serverPort(port)
{
    setObjectName(STRING(SSDB_Client));
    qRegisterMetaType<SSDB_CtrlCmd>("SSDB_CtrlCmd");

    setClientName(name.toStdString());
    m_client = new SSDBClient;
    m_timer = new QElapsedTimer;

    dirCmds<<SSDB_DIR_Stop<<SSDB_DIR_Stop<<SSDB_DIR_Stop;

    timerStart = false;
    queryDirCtrlTimerStart = false;
    queryVideoCtrl_timer = false;
    sendInfo_timer = false;
    stop = true;
}

SSDB_Client::~SSDB_Client()
{
    stop = true;
    if(isConnected())
    {
        disConnect();
    }
    wait(1000);
    delete m_client;
    delete m_timer;
}

bool SSDB_Client::isConnected()
{
    return m_client->isConnect();
}

void SSDB_Client::disConnect()
{
    stop = true;
    timerStart = false;
    queryDirCtrlTimerStart = false;
    sendInfo_timer = false;
    m_client->disConnect();
    emit errMsg("disconnect ssdb");
}

SSDBClient *SSDB_Client::Client() const
{
    return m_client;
}

void SSDB_Client::analyseCMD(const std::string &ret)
{
    if(ret == DirCtrl_CMD)
    {
        qDebug()<<ret.data();
        queryDirCtrlTimerStart = true;
    }
    else if(ret == Param_CMD)
    {
        string val;
        hget(Param_KEY, &val);
        if(! val.empty())
        {
            QString param = QString::fromStdString(val);
            QStringList argList = param.split(" ",QString::SkipEmptyParts);
            if(argList.count() == 4)
            {
                SSDB_CtrlCmd cmd;
                cmd.type = SSDB_CTRL_ParamSet;
                cmd.msg = param;
                cmd.param.speed_run = argList[0].toInt();
                cmd.param.speed_turnOver = argList[1].toInt();
                cmd.param.speed_headShake = argList[2].toInt();
                cmd.param.time_waitForCharge = argList[3].toInt();
                emit CtrlMsg(cmd);
            }
        }
    }
    else if(ret == Video_CMD)
    {
        queryVideoCtrl_timer = true;

        SSDB_CtrlCmd cmd;
        cmd.type = SSDB_CTRL_VideoCtrl;
        cmd.videoCtrl = Video_PlayList;
        emit CtrlMsg(cmd);
    }
    else if(ret == EndVideo_CMD)
    {
        queryVideoCtrl_timer = false;
        sendInfo_timer = false;
    }
    else if(ret == EndDirCtrl_CMD)
    {
        queryDirCtrlTimerStart = false;
    }
    hset(Query_KEY, string("NULL"));
}

bool SSDB_Client::connectServer(const QString &host, int port)
{
    serverAddr = host;
    serverPort = port;
    m_client->connect(host.toLatin1().constData(), port);
    qDebug()<<currentThread();

    if(m_client->isConnect())
    {
        //        Status s;
        //        s = m_client->auth("1234567890123456789012345678901234567890");
        //        if(s.error())
        //            return false;
//        QImage img(":/image/resource/logo.png");
//        QBuffer buffer;
//        QDataStream data(&buffer);
//        buffer.open(QIODevice::ReadWrite);
//        data<<img;
//        qDebug()<<buffer.size();
//        const char* to = buffer.data().data();
//        m_client->set("img",string(to,buffer.size()));
//        string ret;
//        m_client->get("img",&ret);
//        buffer.close();
//        buffer.setData(ret.data(),ret.length());
//        buffer.open(QIODevice::ReadWrite);
//        QImage img2;
//        QDataStream data2(&buffer);
//        data2>>img2;
//        qDebug()<<img2.size();
        emit errMsg("connect ssdb succeed!");
        timerStart = true;
        this->start();
#ifndef _TEST
        QTimer::singleShot(3500, Qt::VeryCoarseTimer, this, &SSDB_Client::getArgs);
#endif
        return true;
    }
    else
    {
        emit errMsg("connect ssdb failed!");
        return false;
    }
}

bool SSDB_Client::connectServer()
{
    return connectServer(serverAddr, serverPort);
}

void SSDB_Client::ticktack()
{
    std::string ret;
    Status s;
    s = hget(Query_KEY, &ret);
    //    qDebug()<<s.code().data()<<ret.data();
    if(s.ok() && ret.length() > 4)
    {
        analyseCMD(ret);
    }
}

void SSDB_Client::queryDirCtrl()
{
    std::string ret;
    Status s;
    s = hget(DirCtrl_CMD, &ret);
    if(s.ok() && ret.length() > 1)
    {
        SSDB_CtrlCmd cmd;
        cmd.type = SSDB_CTRL_DirCtrl;
        if(ret == "up")
            cmd.dirCtrl = SSDB_DIR_Up;
        else if(ret == "down")
            cmd.dirCtrl = SSDB_DIR_Down;
        else if(ret == "left")
            cmd.dirCtrl = SSDB_DIR_Left;
        else if(ret == "right")
            cmd.dirCtrl = SSDB_DIR_Right;
        else if(ret == "stop")
            cmd.dirCtrl = SSDB_DIR_Stop;
        else if(ret == "headup")
            cmd.dirCtrl = SSDB_DIR_HeadUp;
        else if(ret == "headdown")
            cmd.dirCtrl = SSDB_DIR_HeadDown;
        else
            return;
        if(isNewDirCmd(cmd.dirCtrl))
        {
            cmd.msg = QString::fromStdString(ret);
            emit CtrlMsg(cmd);
            emit errMsg(cmd.msg);
        }
    }
}

void SSDB_Client::rcvVideoMsg(const QString &list, int type)
{
    QString msg("%1 %2");
    switch (type)
    {
    case Video_PlayList:
    {
        hset(VideoPlayList_KEY, textCodec->fromUnicode(list).constData());
        emit errMsg(msg.arg(type).arg(list));
    }
        break;
    case Video_Info:
    {
        hset(VideoInfo_KEY, textCodec->fromUnicode(list).constData());
        emit errMsg(msg.arg(type).arg(list));
    }
        break;
    default:
        break;
    }
}

void SSDB_Client::queryVideoCtrl()
{
    string val;
    hget(Video_CMD, &val);

    if(! val.empty())
    {
        QStringList list = textCodec->toUnicode(val.data()).split(" ",QString::SkipEmptyParts);
        if(list.length() > 0)
        {
            SSDB_CtrlCmd cmd;
            cmd.type = SSDB_CTRL_VideoCtrl;
            if(list[0] == "Cycle")
            {
                sendInfo_timer = true;
                cmd.videoCtrl = Video_SetCyclePlay;
                if(list.length() > 1)
                    cmd.msg = list[1];
            }
            else if(list[0] == "Single")
            {
                sendInfo_timer = true;
                cmd.videoCtrl = Video_SetSinglePlay;
                if(list.length() > 1)
                    cmd.msg = list[1];
            }
            else if(list[0] == "SingleCycle")
            {
                sendInfo_timer = true;
                cmd.videoCtrl = Video_SetSingleCyclePlay;
                if(list.length() > 1)
                    cmd.msg = list[1];
            }
            else if(list[0] == "Play")
            {
                sendInfo_timer = true;
                cmd.videoCtrl = Video_Play;
            }
            else if(list[0] == "Pause")
            {
                sendInfo_timer = false;
                cmd.videoCtrl = Video_Pause;
            }
            else if(list[0] == "ContinuePlay")
            {
                sendInfo_timer = true;
                cmd.videoCtrl = Video_ContinuePlay;
            }
            else if(list[0] == "Stop")
            {
                sendInfo_timer = false;
                msleep(5);
                hset(VideoInfo_KEY, "NULL");
                cmd.videoCtrl = Video_Stop;
            }
            else
            {
                return;
            }
            emit CtrlMsg(cmd);
            emit errMsg(list.join(" "));
        }
    }
    hset(Video_CMD, string("NULL"));
}

void SSDB_Client::sendVideoInfo()
{
    SSDB_CtrlCmd cmd;
    cmd.type = SSDB_CTRL_VideoCtrl;
    cmd.videoCtrl = Video_Info;
    emit CtrlMsg(cmd);
}

bool SSDB_Client::isNewDirCmd(SSDB_DIR cmd)
{
    dirCmds<<cmd;
    if(dirCmds.count() > 5)
        dirCmds.removeFirst();
    if(dirCmds.count(cmd) < 5)
        return true;
    else
        return false;
}

std::string SSDB_Client::getClientName() const
{
    return clientName;
}

void SSDB_Client::setClientName(const std::string &name)
{
    if(clientName != name)
    {
        clientName = name;
        saveHistory(name.data(), "RobotName");
    }
}

void SSDB_Client::setClientName(const QString &name)
{
    setClientName(name.toStdString());
}

QString SSDB_Client::getServerAddr() const
{
    return serverAddr;
}

void SSDB_Client::setServerAddr(const QString &addr)
{
    if(serverAddr != addr)
    {
        serverAddr = addr;
        saveHistory(addr, "SSDB_server", "configure");
    }
}

int SSDB_Client::getServerPort() const
{
    return serverPort;
}

void SSDB_Client::setServerPort(int port)
{
    if(serverPort != port && port > 0)
    {
        serverPort = port;
        saveHistory(port, "SSDB_port");
    }
}

Status SSDB_Client::hget(const string &key, string *val)
{
    QMutexLocker locker(&mutex);
    return m_client->hget(clientName, key, val);
}

Status SSDB_Client::hset(const string &key, const string &val)
{
    QMutexLocker locker(&mutex);
    return m_client->hset(clientName, key, val);
}

void SSDB_Client::getArgs()
{
//    hset(VideoInfo_KEY, "");
//    hset(VideoPlayList_KEY, "");
    analyseCMD(Param_CMD);
}

void SSDB_Client::run()
{
    if(! stop)
        return;
    stop = false;
    qDebug()<<currentThread();
    int timeCnt = 0;
    while(! stop)
    {
        timeCnt = 0;
        m_timer->start();
        if(timerStart)
        {
            ticktack();
//            qDebug()<<QTime::currentTime();
        }
        while(timeCnt < 10)
        {
            timeCnt ++;
            if(queryVideoCtrl_timer)
            {
                if(timeCnt == 4)
                {
                    if(sendInfo_timer)//send video msg current statue
                        sendVideoInfo();
                    queryVideoCtrl();
                }
            }
            if(queryDirCtrlTimerStart)
            {
                queryDirCtrl();
            }
            //            int i = 12;
//            while(! m_timer->hasExpired(120) && ! stop)
//            {
//                QThread::msleep(10);
//            }
//            m_timer->start();
            QEventLoop loop;
            QTimer::singleShot(100,&loop,SLOT(quit()));
            loop.exec();
        }
    }
    m_timer->invalidate();
}