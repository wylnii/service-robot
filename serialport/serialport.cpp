#include "serialport.h"
/*
ARM板与下位机UART通信协议说明：
共四个字节（FF XX XX BCC，16进制）：FF数据头+一个字节控制指令+一个字节数据+一个字节BCC校验（异或校验）。
注意：每帧指令需间隔10ms以上。

控制指令如下：

指令	说明
01-05	控制机器人前后左右行走（第三个字节为任意，如FF 01 FF 01）
06	设置机器人行走速度
07	设置机器人转弯速度
08	设置机器人摇头速度
09	设置机器人充电门槛电压（低于此电压自动寻找充电桩充电）
Volt=XX/256.0*29
1A-1F	保留
11-14	控制机器人上下左右摇头（第三字节为任意，如FF 11 FF 11）
15	机器人头部回正
10	查询当前电池电压
16	查询机器人当前设定行走速度
17	查询机器人当前设定转弯速度
18	查询机器人当前设定摇头速度
19	查询机器人当前设定充电门槛电压
20	下达寻找充电桩指令
21	查询当前障碍状态（障碍状态变化时会自动返回，也可手动查询）
22-7F	保留


下位机回应当前障碍状态说明：
位于一帧的第三字节，byte1-byte8（低位-高位），有遮挡为1，无遮挡为0。

Byte1	Byte2	Byte3	Byte4	Byte5	Byte6	Byte7	Byte8
上超声波	下超声波	后超声波	左红外	右红外	台阶	保留	保留

下位机回应帧格式：
校验正确：FF CMD XX BCC	CMD为上述控制指令
校验错误：FF CE XX BCC		CE=CMD|0x80
BCC校验：
BCC=FF^CMD^XX				^为异或位运算
 */

SerialPort::SerialPort(QObject *parent) : QSerialPort(parent)
{
    qRegisterMetaType<SerialPort::MoveFlag>("SerialPort::MoveFlag");
    qRegisterMetaType<SerialPort::CtrlCmd>("SerialPort::CtrlCmd");

    timer = new QElapsedTimer;
    dataLength = 0;
    rcvMsg.clear();
    lastCMD.clear();

    connect(this,SIGNAL(readyRead()),this,SLOT(readCom()));
//    openPort(scan_com().last(),DEFAULT_BAUD);
    mtimer.setTimerType(Qt::VeryCoarseTimer);
    mtimer.start(5000);
    connect(&mtimer,SIGNAL(timeout()),this,SLOT(queryRobotMsg()));
    timerCount = 0;
}

SerialPort::~SerialPort()
{
    close();
    delete timer;
}

bool compareString(const QString &s1, const QString &s2)
{
    if(s1.length() == s2.length())
        return s1 < s2;
    else
        return s1.length() < s2.length();
}

QStringList SerialPort::scanAvailablePorts()
{
    QList<QSerialPortInfo> portsInfo = QSerialPortInfo::availablePorts();//List all available port
    QStringList portList;
    if(portsInfo.length() > 0)
    {
        foreach (QSerialPortInfo info, portsInfo)
        {
            portList << info.portName();
        }
        qSort(portList.begin(),portList.end(),compareString);
//        qDebug()<<portList;
    }
    else
    {
        portList << "NULL";
        qDebug("Can't found any COM port\t");
    }
    return portList;
}

/*protocol: FF XX XX BCC
 * head: FF
 * data: 3 bytes (1 control byte + 1 data byte)
 * check method: BCC
 *
 *  detail: 01-05   direction ctrl  up down left right   FF 01 XX BCC
 *               06         set speed                                               FF 06 XX BCC
 *               07         set turn over speed                            FF 07 XX BCC
 *               08         set shake head speed                        FF 08 XX BCC
 *               09         set charge voltage                              FF 09 XX BCC   XX = Voltage
 *               11-12   headup headdown                              FF 11 XX BCC
 *               13-14   headleft headright
 *               15         headmid
 *               10         query battery voltage                        FF 10 BCC
 *               16         query speed                                          FF 16 BCC
 *               17         query turn over speed                       FF 17 BCC
 *               18         query shake head speed                   FF 18 BCC
 *               19         query charge voltage                         FF 19 BCC
 *               20         search charge point                            FF 20 XX BCC
 *               21         :barrier:   Byte1   Byte2   Byte3   Byte4 Byte5  Byte6   Byte7  Byte8    1 is barrier
 *                                                s_UP  s_down  s_back   L_L     L_R     foot_S     #          #
 *               20-7F   reserved
 *
 *
 *  reply : right       FF CMD XX BCC
 *               fault       FF XX BCC   XX = CMD|0x80
 *
 *               query     FF CMD XX BCC
 *
 * BCC check : BCC = FF^XX^XX......
 */

void SerialPort::move(MoveFlag motion)
{
    switch (motion)
    {
    case Up:
        sendCMD(QByteArray("\xff\x01\xff\x01"));
        break;
    case Down:
        sendCMD(QByteArray("\xff\x02\xff\x02"));
        break;
    case Left:
        sendCMD(QByteArray("\xff\x03\xff\x03"));
        break;
    case Right:
        sendCMD(QByteArray("\xff\x04\xff\x04"));
        break;
    case Stop:
        sendCMD(QByteArray("\xff\x05\xff\x05"));
        break;
    case HeadUp:
        sendCMD(QByteArray("\xff\x11\xff\x11"));
        break;
    case HeadDown:
        sendCMD(QByteArray("\xff\x12\xff\x12"));
        break;
    case HeadLeft:
        sendCMD(QByteArray("\xff\x13\xff\x13"));
        break;
    case HeadRight:
        sendCMD(QByteArray("\xff\x14\xff\x14"));
        break;
    case HeadMid:
        sendCMD(QByteArray("\xff\x15\xff\x15"));
        break;
    case Charge:
        sendCMD(QByteArray("\xff\x20\xff\x20"));
        break;
    default:
        break;
    }
}

bool SerialPort::dataIsValid()
{
    if(rcvMsg.length() > 0 && timer->elapsed() > RCV_DATA_INTERVAL)
        return true;
    else
        return false;
}

void SerialPort::sendCMD(const QByteArray &cmd)
{
    if(!cmd.isEmpty())
    {
        for (auto &ch : cmd)
        {
            putChar(ch);
            thread()->usleep(1000);
        }
    }
}

void SerialPort::sendCMD(const uchar *cmd, int length)
{
    if(length > 0)
    {
        while (length --)
        {
            putChar(*cmd++);
            thread()->usleep(1000);
        }
        thread()->msleep(10);
    }
}

void SerialPort::queryRobotMsg()
{
    if(isOpen())
    {
        if((timerCount&0x01) == 1)
            sendCMD("\xff\x10\xff\x10");//voltage
//        else
//            sendCMD("\xff\x21\xff\x21");//barrier
        timerCount ++;
    }
}

void SerialPort::sendArgs(const SSDB_CtrlCmd &cmd)
{
    uchar speed_run = cmd.param.speed_run;
    uchar speed_turnOver = cmd.param.speed_turnOver;
    uchar speed_headShake = cmd.param.speed_headShake;
    uchar time_waitForCharge = cmd.param.time_waitForCharge;

    uchar cnt = 0;
    uchar toSend[4] = {0xff};
    if(speed_run > 0)
    {
        toSend[1] = Cmd_SetRunS;
        toSend[2] = speed_run;
        toSend[3] = toSend[0]^toSend[1]^toSend[2];
        sendCMD(toSend, 4);
        cnt ++;
    }
    if(speed_turnOver > 0)
    {
        toSend[1] = Cmd_SetTurnS;
        toSend[2] = speed_turnOver;
        toSend[3] = toSend[0]^toSend[1]^toSend[2];
        sendCMD(toSend, 4);
        cnt ++;
    }
    if(speed_headShake > 0)
    {
        toSend[1] = Cmd_SetShakeS;
        toSend[2] = speed_headShake;
        toSend[3] = toSend[0]^toSend[1]^toSend[2];
        sendCMD(toSend, 4);
        cnt ++;
    }
    if(time_waitForCharge > 0)
    {
        toSend[1] = Cmd_SetTimeChg;
        toSend[2] = time_waitForCharge;
        toSend[3] = toSend[0]^toSend[1]^toSend[2];
        sendCMD(toSend, 4);
        cnt ++;
    }
    if(cnt == 4)
    {
        saveHistory(cmd.msg, "Args");
    }
}

bool SerialPort::openPort(const QString &portname, const int &baudRate, bool close)
{
    //    qDebug()<<"serial_thread"<<QThread::currentThread();
    if(close)
    {
        this->close();
        emit errMsg(QString("%1 closed").arg(portName()));
        return true;
    }
    else if(baudRate > 0)
    {
        setPortName(portname);
        setBaudRate(baudRate);
        if(open(QSerialPort::ReadWrite))
        {
            emit errMsg(QString("open succeed : %1 %2").arg(portname).arg(baudRate));
            return true;
        }
        else
        {
            emit errMsg(QString("open error : %1 %2 %3").arg(errorString(),portname).arg(baudRate));
            return false;
        }
    }
    return false;
}

void SerialPort::readCom()
{
    timer->start();
    QByteArray rcv = readAll();
    rcvMsg.append(rcv);
    dataLength = rcvMsg.length();
    QTimer::singleShot(RCV_DATA_INTERVAL + 2, Qt::PreciseTimer, this, &SerialPort::getData);
}

void SerialPort::getData()
{
    if(dataLength == rcvMsg.length() && dataIsValid())
    {
        qDebug()<<dataLength<<rcvMsg.toHex()<<timer->elapsed();
        analyseData(rcvMsg);
        dataLength = 0;
        rcvMsg.clear();
        timer->invalidate();
    }
}

void SerialPort::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
//    qDebug()<<QThread::currentThread()<<thread();

    switch (cmd.type)
    {
    case SSDB_CTRL_DirCtrl:
        move((SerialPort::MoveFlag)cmd.dirCtrl);
        break;
    case SSDB_CTRL_ParamSet:
    {
        sendArgs(cmd);
    }
        break;
    case SSDB_CTRL_Charge:
        move(SerialPort::Charge);
    default:
        break;
    }
}

void SerialPort::analyseData(const QByteArray &rcvMsg)
{
    if((uchar)rcvMsg[0] == 0xff) //data head
    {
        uchar sum = 0;
        int last = rcvMsg.length() - 1;
        for(int i = 0; i < last; i ++)
        {
            sum ^= (uchar)rcvMsg[i];
        }
        if(sum == (uchar)rcvMsg[last] && last > 1) //last byte:check
        {
            qDebug("check:0x%02X",sum);
            int data = 0;
            switch ((uchar)rcvMsg[1])
            {
            case Cmd_QueryBatVol:
                if(last >= 3)
                    data = (uchar)rcvMsg[2];//TODO 第三字节为电压信息 Volt=data/256.0*29
                break;
            case Cmd_QueryRunS:
                data = (uchar)rcvMsg[2];
                break;
            case Cmd_QueryTurnS:
                data = (uchar)rcvMsg[2];
                break;
            case Cmd_QueryShakeS:
                data = (uchar)rcvMsg[2];
                break;
            case Cmd_QueryChgVol:
                if(last >= 3)
                    data = (uchar)rcvMsg[2];
                break;
            case Cmd_WarningMsg:
                data = (uchar)rcvMsg[2];
                break;
            default:
                if(((uchar)rcvMsg[1] >> 7) == 0x01)
                {
                    uchar cmd[4] = {0xff, (uchar)(rcvMsg[1] & 0x7f), 0xff};
                    cmd[3] = (cmd[0]^cmd[1]^cmd[2]);
                    thread()->msleep(20);
                    sendCMD(cmd, 3);
                }
                break;
            }
            if(data > 0)
            {
                emit rcvSPData(CtrlCmd{(Cmd_Type)rcvMsg[1], data});
            }
        }
    }
}
