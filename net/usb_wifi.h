#ifndef USB_WIFI_H
#define USB_WIFI_H

#include <QtCore>
#include <QTableWidgetItem>
#include <QTableWidget>

class USB_WiFi : public QObject
{
    Q_OBJECT
public:
    explicit USB_WiFi(QObject *parent = 0);
    ~USB_WiFi();
    //QStringList wifiinfo;
    static bool WiFi_exist();//测试有没有wifi模块
    QString connetct_ssid;//所连接的wifi网路ssid

private:
    QProcess *process;
    int retry;
    QMutex mutex;

signals:
    void errormsg(QString);//以信号模式将运行过程中的信息发送出去
public slots:
    QList<QStringList> scan_wifi(int update);//扫描wifi,更新wifi列表
    bool connect_wifi(QString ssid,QString state,QString passcode);//连接wifi
    bool connect_wifi_by_(const QString &cmd, const QString &ssid, const QString &type);
    bool stop_wifi();//断开wifi连接
};

#endif // USB_WIFI_H
