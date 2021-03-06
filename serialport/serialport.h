#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QTimer>
#include "global.h"
class QElapsedTimer;

class SerialPort : public QSerialPort
{
    Q_OBJECT
public:
    explicit SerialPort(QObject *parent = 0);
    ~SerialPort();
    QStringList scanAvailablePorts();
    enum MoveFlag{Up = SSDB_DIR_Up, Down, Left, Right, Stop = SSDB_DIR_Stop,
                  HeadUp = SSDB_DIR_HeadUp, HeadDown, HeadLeft, HeadRight, HeadMid = SSDB_DIR_HeadMid,
                  Charge = 0x20};
    enum Cmd_Type{Cmd_SetRunS = 0x06, Cmd_SetTurnS = 0x07, Cmd_SetShakeS = 0x08,
                  Cmd_SetChgVol = 0x09, Cmd_SetTimeChg = 0x0A, //FIXME 与头部回正命令重复，下位机待纠正
                Cmd_QueryBatVol = 0x10, Cmd_QueryRunS = 0x16, Cmd_QueryTurnS = 0x17, Cmd_QueryShakeS = 0x18,
                Cmd_QueryChgVol = 0x19, Cmd_QueryTimeChg = 0x1A, Cmd_Charge = 0x20, Cmd_WarningMsg = 0x21};
    struct CtrlCmd
    {
        Cmd_Type type;
        int data;
    };

    bool dataIsValid();
    void sendArgs(const SSDB_CtrlCmd &cmd);

public slots:
    bool openPort(const QString & portname, const int baudRate, bool close = false);
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
    void errMsg(const QString &, bool = false);
    void rcvSPData(const SerialPort::CtrlCmd &cmd);
};

#endif // SERIALPORT_H
