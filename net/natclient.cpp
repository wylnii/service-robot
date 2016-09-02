#include "natclient.h"
#include <QDebug>
#ifdef __linux
#include <arpa/inet.h>
#endif
#ifdef _WIN32
extern "C"{
#include <winSock2.h>
#include <winSock.h>
#include <sys/types.h>
}
#endif

NatClient::NatClient(QObject *parent) : QObject(parent)
{
    NatSocket = new QUdpSocket(this);
    connect(NatSocket,&QIODevice::readyRead,this,&NatClient::receiveData);

    onlineTimer = new QTimer(this);
    onlineTimer->setTimerType(Qt::VeryCoarseTimer);
    onlineTimer->setInterval(30000);
    connect(onlineTimer,&QTimer::timeout,this,&NatClient::onlineCheck);
    loginState=false;//接入状态
    QString NAT = loadHistory("NAT");
    setServerIP(NAT.left(NAT.indexOf(':')));
    setServerPort(NAT.midRef(NAT.indexOf(':')+1).toInt());
    localNat.natype = 1;
    setLocalNatName(RobotName.toLatin1());//不要超过10个字符
}

NatClient::~NatClient()
{
    if(loginState)
    {
        logout();
        NatSocket->close();
    }
}

void NatClient::login()
{
    qDebug()<<"log thread:"<<QThread::currentThread();
    if(loginState)
    {
        emit errorMsg("already login");
        return;
    }
    logout(true);
    emit errorMsg("logining...");
    //receiveSocket.bind(6061);
    onlineTimer->stop();
    //Login Message
    struct stLoginMessage loginMsg;
    loginMsg.msgHead.dwMessageType = htonl(MSGTYPE_LOGIN);
    strncpy(loginMsg.userName,localNat.name,sizeof(loginMsg.userName));
    loginMsg.natType = htonl(localNat.natype);

    for(int i = 0; i < 3; i ++)
    {
        NatSocket->writeDatagram(((const char *)&loginMsg),sizeof(loginMsg),server.IP,server.port);
        for(int ii=0;ii<100;ii++)
        {
            qApp->processEvents();
            thread()->msleep(10);

            if(loginState)
            {
                emit errorMsg(QString("login success %1s").arg(i+ii*0.01));
                onlineTimer->start();
                return;
            }
        }
    }
    emit errorMsg("login failed");
}

void NatClient::logout(bool force)
{
    if(loginState || force)
    {
        stLogoutMessage logoutMsg;
        logoutMsg.msgHead.dwMessageType = htonl(MSGTYPE_LOGOUT);
        strncpy(logoutMsg.userName, localNat.name, sizeof(logoutMsg.userName));
//        qDebug()<<"localNAME"<<logoutMsg.userName;
        NatSocket->writeDatagram(((const char *)&logoutMsg),sizeof(logoutMsg),server.IP,server.port);
        NatSocket->close();
        loginState = false;
        if(! force)
            emit errorMsg("log out");
    }
}

void NatClient::onlineCheck()
{
        processOnlineAck();
}

void NatClient::sendData(const QByteArray &data)
{
    if(loginState)
    {
        stP2PMessageReqMessage reqMsg;
        reqMsg.msgHead.dwMessageType = htonl(MSGTYPE_P2PMSG_REQ);
        strncpy(reqMsg.message, data.constData(), sizeof(reqMsg.message));
        NatSocket->writeDatagram(((const char *)&reqMsg),sizeof(reqMsg),callerNat.IP,callerNat.port);
    }
    else
        emit errorMsg("please login first");
}

void NatClient::receiveData()
{
    //    qDebug()<<"nat thread:"<<QThread::currentThread();
    QByteArray data;
    QHostAddress addr;
    quint16 port;
    while(NatSocket->hasPendingDatagrams())
    {
        data.resize(NatSocket->pendingDatagramSize());
        NatSocket->readDatagram(data.data(),MAX_MESSAGE_SIZE,&addr,&port);
        //            qDebug()<<"data:"<<data;
        //            qDebug()<<"addr:"<<addr<<port;
        stMessageHead* msgHead = (stMessageHead*)data.data();
        MessageType msgType = (MessageType )ntohl(msgHead->dwMessageType);

        switch((int)msgType)
        {
        case MSGTYPE_GETALLUSER_ACK:
        {
            processLogin(data);//用于处理用户已经登录上服务器的ack处理
            loginState=true;
            break;
        }
        case MSGTYPE_ONLINE_ACK:
        {
            qDebug()<<"MSGTYPE_ONLINE_ACK\t"<<QTime::currentTime().toString();
            //processOnlineAck();
            break;
        }
        case MSGTYPE_P2PMSG_REQ:
        {
            processP2PmsgREQ(data, addr, port);
            break;
        }
        case MSGTYPE_P2PMSG_ACK:
        {
            qDebug()<<"MSGTYPE_P2PMSG_ACK";
            break;
        }
        case MSGTYPE_P2PSOMEONEWANTCALLYOU:
        {
            processSomeWantCallYou(data);
            qDebug()<<"MSGTYPE_P2PSOMEONEWANTCALLYOU";
            break;
        }
        case MSGTYPE_P2PTRASH:
        {
            qDebug()<<"MSGTYPE_P2PTRASH";
            break;
        }
        default:
            qDebug()<<"unknown cmd";
            break;
        }
    }
}

void NatClient::processLogin(QByteArray data)
{
    userNatlist.clear();//清空客户端列表信息

    stAllUserAckMessage* allUserAckMsg = (stAllUserAckMessage*)data.data();
    DWORD UserCount = ntohl(allUserAckMsg->dwUserCount);
    stUserNode* currUserNode = &(allUserAckMsg->userNodeArray[0]);

//    qDebug()<<UserCount;
    for(uint i = 0; i<UserCount; i++)
    {
        NatClientInfo info;

        strncpy(info.name, currUserNode->userName, sizeof(currUserNode->userName));
//        strncpy(ip, currUserNode->ip, sizeof(currUserNode->ip));

        info.IP = QHostAddress(currUserNode->ip);
        info.port = ntohs(currUserNode->port);
        info.natype = ntohl(currUserNode->natType);

        userNatlist<<info;
        currUserNode++;
//        qDebug()<<info.name<<info.IP<<info.port<<info.natype;
        if(!(strcmp(userNatlist.at(i).name,localNat.name)))//strcmp在相等时为零；
        {
            localNat.IP=userNatlist.at(i).IP;
            localNat.port=userNatlist.at(i).port;
        }
    }
    qDebug()<<"localIP:"<<localNat.IP<<localNat.port;
}

void NatClient::processP2PmsgREQ(const QByteArray &data, const QHostAddress &addr, quint16 port)//对接收到的数据的处理
{
    stP2PMessageReqMessage *req = (stP2PMessageReqMessage *)data.data();

    QByteArray msg = req->message;
    emit reciveMsg(msg);
    stP2PMessageAckMessage ackMsg;
    callerNat.IP = addr;
    callerNat.port = port;
    ackMsg.msgHead.dwMessageType = htonl(MSGTYPE_P2PMSG_ACK);
    NatSocket->writeDatagram(((const char *)&ackMsg),sizeof(ackMsg),callerNat.IP,callerNat.port);
}

void NatClient::processSomeWantCallYou(QByteArray data)
{
    stP2PSomeoneWantCallYouMessage* msg = (stP2PSomeoneWantCallYouMessage*)data.data();
    msg->callerPort = ntohs(msg->callerPort);

    callerNat.IP = QHostAddress(msg->callerIp);
    callerNat.port = msg->callerPort;

//    qDebug()<<"CallerIP:"<<callerNat.IP;
//    qDebug()<<"CallerPort:"<<callerNat.port;

    stP2PTrashMessage ackMsg;
    ackMsg.msgHead.dwMessageType = htonl(MSGTYPE_P2PTRASH);
    NatSocket->writeDatagram(((const char *)&ackMsg),sizeof(ackMsg),callerNat.IP,callerNat.port);
}

void NatClient::processOnlineAck()
{
    if(loginState)
    {
//        qDebug()<<"online";
        stOnLineReqMessage reqMsg;
        reqMsg.msgHead.dwMessageType = htonl(MSGTYPE_ONLINE_REQ);
        strncpy(reqMsg.userName, localNat.name, sizeof(reqMsg.userName));
        NatSocket->writeDatagram(((const char *)&reqMsg),sizeof(reqMsg),server.IP,server.port);
    }
}

void NatClient::setServerIP(QString ip)
{
    server.IP=QHostAddress(ip);
}

void NatClient::setServerPort(WORD port)
{
    server.port=port;
}

void NatClient::setLocalNatName(const QByteArray &name)
{
    strncpy(localNat.name,name.constData(),sizeof(localNat.name));//不要超过10个字符
}

bool NatClient::isOnline() const
{
    return loginState;
}
