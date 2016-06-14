#ifndef IPINFO_H
#define IPINFO_H

#include <QTextEdit>
#include <QtNetwork>
#include <global.h>

class IPInfoTable : public QTextEdit
{
    Q_OBJECT
public:
    explicit IPInfoTable(QWidget *parent = 0, int width = 100, int height = 100);
    ~IPInfoTable();
    QStringList getIpinfo();
    void showIPInfo();
    static bool eth0_exist();
    static bool hasValidIP();
    static bool checkNet();

signals:
    void errormsg(QString);//以信号模式将运行过程中的信息发送出去

private:
    static int getNetworkQuality(const QString &pattern = "");
};

#endif // IPINFO_H
