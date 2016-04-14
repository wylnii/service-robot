#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QtSerialPort>
#include <QObject>
#include <QElapsedTimer>
#include "global.h"

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    QStringList scanAvailablePorts();
    enum MoveFlag{Up = 0x01, Down, Left, Right, Stop = 0x05, HeadUp = 0x11, HeadDown = 0x12, HeadLeft = 0x13, HeadRight = 0x14,\
                  HeadMid = 0x15, Charge = 0x20};
    enum Cmd_Type{Cmd_SetRunS = 0x06, Cmd_SetTurnS = 0x07, Cmd_SetShakeS = 0x08, Cmd_SetChgVol = 0x09, Cmd_SetTimeChg = 0x15,\
                Cmd_QueryBatVol = 0x10, Cmd_QueryRunS = 0x16, Cmd_QueryTurnS = 0x17, Cmd_QueryShakeS = 0x18,\
                Cmd_QueryChgVol = 0x19, Cmd_Charge = 0x20, Cmd_WarningMsg = 0x21};
    struct CtrlCmd
    {
        Cmd_Type type;
        int data;
    };

    bool dataIsValid();
    void sendArgs(const SSDB_CtrlCmd &cmd);

public slots:
    bool openPort(const QString & portname, const int &baudRate, bool close = false);
    void move(MoveFlag motion);
    void readCom();
    void getData();
    void getCtrlMsg(const SSDB_CtrlCmd &cmd);
    void sendCMD(const QByteArray &cmd);
    void sendCMD(const uchar *cmd, int length = -1);
    void queryRobotMsg();

private:
    void analyseData(const QByteArray &rcvMsg);
    QElapsedTimer *timer;
    QByteArray rcvMsg;
    int dataLength;
    QByteArray lastCMD;
    QTimer mtimer;
    int timerCount;

signals:
    void errMsg(QString, bool = 0);
    void rcvSPData(SerialPort::CtrlCmd cmd);
};

#endif // SERIALPORT_H
