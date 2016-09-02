#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include "keyboard/keyboard.h"
#include "net/ipinfotable.h"
#include "net/usb_wifi.h"
#include "serialport/serialport.h"
#include "videoplayer/videoplayer.h"
#include "global.h"
#include "SSDB/ssdb_client_.h"
#include "net/downloader.h"
#include "videoplayer/emotionplayer.h"
#include "net/netspeed.h"
#include "keyinput.h"
#include "net/login.h"
#include "net/networkqualitythread.h"
#include "net/natclient.h"
#include "ffmpeg/ffmpeg_sh.h"

namespace Ui {
class MainWindow;
class Keyboard;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void setBacklightBright(uchar bright);

signals:
    void connect_net(QString ssid,QString state,QString passcode);
    void stop_net();
    void openSerialPort(const QString &portname, const int baudRate, bool close = false);
    void robotMove(SerialPort::MoveFlag move);
    void connectSSDB();
    void sendCmd(QByteArray &cmd);
    void send_rtsp(QString rtsp_ip,QString port,QString feed,QString Resolution,QString fbs,QString bitrate,QString device);
    void natLogin();
    void natLogout(bool = false);

protected:
    void setStyleSheet();
//    bool event(QEvent *event);

public slots:
    void show();
    void on_pushButton_scan_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();
    void on_toolButton_test_clicked();
    void on_toolButton_play_clicked();
    void on_toolButton_up_clicked();
    void on_toolButton_down_clicked();
    void on_toolButton_left_clicked();
    void on_toolButton_right_clicked();
    void on_toolButton_stop_clicked();
    void on_pushButton_openPort_clicked();
    void on_tabWidget_tabBarClicked(int index);
    void on_pushButton_openssdb_clicked();
    void on_toolButton_headup_clicked();
    void on_toolButton_headdown_clicked();
    void on_toolButton_headleft_clicked();
    void on_toolButton_headright_clicked();

    void on_pushButton_test2_clicked();
    void on_toolButton_show_clicked();
    void on_toolButton_charge_clicked();
    void on_verticalSlider_valueChanged(int value);

    void on_toolButton_last_clicked();

    void on_toolButton_next_clicked();
    void on_verticalSlider_2_sliderReleased();
    void on_pushButton_natlogin_clicked();

private slots:
    void autoConnect();
    void setStatText(const QString &text);
    void setStatusBarText(const QString &text, bool type = 0);
    void rcvKBInput(const QString &input, const QString &mrk);
    void getSPMsg(const SerialPort::CtrlCmd &cmd);
    void getCtrlMsg(const SSDB_CtrlCmd &cmd);
    void getKeyinput(uchar key, bool status);
    void changeWindows();
    void getNATCtrlMsg(const QByteArray &msg);

    void on_pushButton_startvideo_clicked();

private:
    void showSupportMsg();
    Ui::MainWindow *ui;
    QThread *wifi_thread;
    QThread *serialport_thread;
    QLabel *status_label;
    QTableWidget *wifitable;
    Keyboard *mykeyboard;
    USB_WiFi *wifi;
    IPInfoTable *ipInfoTable;
    VideoPlayer *videoPlayer;
    SerialPort *serialport;
    SSDB_Client *ssdbClient;
    EmotionPlayer *emotionPlayer;
//    NetSpeed *netSpeed;
    KeyInput *keyInput;
    NetworkQualityThread *networkQualityThread;

    NatClient *nat;
    FFmpeg_sh *ffmpeg_run;
    QThread *ffmpegthread;
};

#endif // MAINWINDOW_H
