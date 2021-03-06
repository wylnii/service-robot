#ifndef GLOBAL_H
#define GLOBAL_H

#include <QVariant>
#include <QSettings>
#include <QTextCodec>

#define RECORD_LOG
#define PRINT_SCREEN
#define DEBUG

#define STRING(str) #str
#define STRCAT(str1,str2) (str1)##(str2)

#if QT_VERSION > 0x050500
#define _TEST
#endif

//定义HD_SCREEN 高清屏
//#define HD_SCREEN

#ifdef HD_SCREEN
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 800;
#else
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 480;
#endif

#define VERSION  "3.0.0"
#ifdef HD_SCREEN
#define VERSION_STR VERSION " for HD Screen"
#else
#define VERSION_STR VERSION " for SD Screen"
#endif

#ifndef Logout
#define Logout qDebug()<<this
#endif

#ifndef LOG_FILE
#define LOG_FILE "log.txt"
#endif

extern QString RobotName;
extern QTextCodec *textCodec;
extern QStringList EmotionList;   //for SSDB
extern QStringList VideoPlaylist;   //for SSDB


const int WINDOW_WIDTH = SCREEN_WIDTH;
const int WINDOW_HEIGHT = SCREEN_HEIGHT;

const int RCV_DATA_INTERVAL = 10;
const int DEFAULT_BAUD = 9600;

enum SSDB_CTRL_Type{SSDB_CTRL_DirCtrl, SSDB_CTRL_ParamSet, SSDB_CTRL_Video, SSDB_CTRL_VideoCtrl, SSDB_CTRL_Charge, SSDB_CTRL_Emotion, SSDB_CTRL_num};
enum SSDB_DIR{SSDB_DIR_Up = 0x01, SSDB_DIR_Down, SSDB_DIR_Left, SSDB_DIR_Right, SSDB_DIR_Stop = 0x05,\
              SSDB_DIR_HeadUp = 0x11, SSDB_DIR_HeadDown = 0x12, SSDB_DIR_HeadLeft = 0x13, SSDB_DIR_HeadRight = 0x14, SSDB_DIR_HeadMid = 0x15};
enum SSDB_Video_Ctrl{Video_Play = 1, Video_Pause, Video_ContinuePlay, Video_Stop, Video_PlayNext, Video_PlayLast, \
                     Video_PlayList, Video_Info, Video_SetPlayList, Video_Err = -1,\
                     Video_SetCyclePlay = 0x100, Video_SetSinglePlay = 0x101,  Video_SetSingleCyclePlay = 0x102};

struct SSDB_PARAM{
    uchar speed_run = 0;
    uchar speed_turnOver = 0;
    uchar speed_headShake = 0;
    uchar time_waitForCharge = 0;
};

struct SSDB_CtrlCmd{
    SSDB_CTRL_Type type = SSDB_CTRL_num;
    SSDB_DIR dirCtrl = SSDB_DIR_Stop;
    SSDB_PARAM param;
    SSDB_Video_Ctrl videoCtrl = Video_Err;
    QString msg;
    int emotionIndex = -1;
};
//Q_DECLARE_METATYPE(SSDB_CtrlCmd)

void saveHistory(const QVariant &input, const QString &mrk, const QString &group = QString("configure"));
QByteArray loadHistory(const QString &mrk, const QVariant &dfl_value = QVariant(), const QString &group = QString("configure"));
QByteArray encrypt(const QByteArray &code, bool en = false);

#endif // GLOBAL_H

