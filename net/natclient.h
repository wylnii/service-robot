#ifndef NATCLIENT_H
#define NATCLIENT_H

#include <QObject>
#include <QtNetwork>
#include <net/proto.h>
#include <global.h>

 struct NatClientInfo
{
    char name[10];
    QHostAddress IP;
    WORD port;
    DWORD natype;
};
struct NatServerInfo
{
    QHostAddress IP;
    WORD port;
};

class NatClient : public QObject
{
    Q_OBJECT
public:
    explicit NatClient(QObject *parent = 0);
    ~NatClient();
    NatClientInfo localNat,callerNat;
    QList<NatClientInfo> userNatlist;
    NatServerInfo server;

    bool isOnline() const;

signals:
    void errorMsg(QString e);
    void reciveMsg(QByteArray m);

public slots:
    //void broadcastData();
    void receiveData();
    void processLogin(QByteArray data);
    void processP2PmsgREQ(const QByteArray &data, const QHostAddress &addr, const quint16 port);
    void processSomeWantCallYou(QByteArray data);
    void login();
    void logout(bool force = false);
    void sendData(const QByteArray &data);
    void processOnlineAck();
    void onlineCheck();
    void setServerIP(QString ip);
    void setServerPort(WORD port);
    void setLocalNatName(const QByteArray &name);

private:
    bool loginState;
    QUdpSocket *NatSocket;
    QUdpSocket *receiveSocket;
    QTimer *onlineTimer;
};

#endif // NATCLIENT_H
