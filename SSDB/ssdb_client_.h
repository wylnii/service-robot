#ifndef SSDB_CLIENT__H
#define SSDB_CLIENT__H

#include <QObject>
#include <QtCore>
#include "SSDB/ssdb_client.h"
#include "global.h"
#include "serialport/serialport.h"

class SSDB_Client : public QThread
{
    Q_OBJECT
public:
    SSDB_Client(QObject * parent = 0, const QString &name = QString(), const QString &addr = QString("127.0.0.1"), int port = 8888);
    ~SSDB_Client();
    bool isConnected();
    void disConnect();
    ssdb::SSDBClient *Client() const;
    void analyseCMD(const std::string &ret);

    std::string getClientName() const;
    void setClientName(const std::string &name);
    void setClientName(const QString &name);

    QString getServerAddr() const;
    void setServerAddr(const QString &addr);

    int getServerPort() const;
    void setServerPort(int port);
    ssdb::Status hget(const std::string& key, std::string* val);
    ssdb::Status hset(const std::string& key, const std::string& val);
    void getArgs();

public slots:
    bool connectServer(const QString &host, int port);
    bool connectServer();
    void ticktack();
    void queryDirCtrl();
    void rcvVideoMsg(const QString &list, int type);
    void queryVideoCtrl();
    void sendVideoInfo();
    void getSPMsg(const SerialPort::CtrlCmd &cmd);

signals:
    void CtrlMsg(SSDB_CtrlCmd);
    void errMsg(QString, bool = 0);

private:
    ssdb::SSDBClient *m_client;
    std::string clientName;
    QString serverAddr;
    int serverPort;
    bool stop;
    bool timerStart;
    bool queryDirCtrlTimerStart;
    bool sendInfo_timer;
    bool queryVideoCtrl_timer;
    QElapsedTimer *m_timer;
    QMutex mutex;
    QVector<SSDB_DIR> dirCmds;
    bool isNewDirCmd(SSDB_DIR cmd);

protected:
    void run();
};

#endif // SSDB_CLIENT_H
