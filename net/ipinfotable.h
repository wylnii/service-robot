#ifndef IPINFO_H
#define IPINFO_H

#include <QTextEdit>
#include <QtNetwork>
class IPInfoTable : public QTextEdit
{
    Q_OBJECT
public:
    explicit IPInfoTable(QWidget *parent = 0, int width = 100, int height = 100);
    ~IPInfoTable();
    QStringList get_ipinfo();
    void showIPInfo();
    static bool eth0_exist();
    static bool hasValidIP();

signals:
    void errormsg(QString);//以信号模式将运行过程中的信息发送出去
public slots:
};

#endif // IPINFO_H
