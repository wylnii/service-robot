#include "ipinfotable.h"

IPInfoTable::IPInfoTable(QWidget *parent, int width, int height) : QTextEdit(parent)
{
    setFixedSize(width,height);
    setReadOnly(true);
}

IPInfoTable::~IPInfoTable()
{

}

QStringList IPInfoTable::get_ipinfo()//主要用于获得设备的ip信息
{
    QStringList localinfo;
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    for(int i = list.count() - 1; i >= 0; i --)
    { //遍历每一个网络接口
        QNetworkInterface interface = list[i];
        localinfo << QString("Device:%1").arg(interface.name());
        //设备名
        localinfo << QString("MAC:%1").arg(interface.hardwareAddress());
        //硬件地址
        QList<QNetworkAddressEntry> entryList = interface.addressEntries();
        //获取IP地址条目列表，每个条目中包含一个IP地址，一个子网掩码和一个广播地址
        foreach(QNetworkAddressEntry entry,entryList)
        {//遍历每一个IP地址条目
            if(!entry.broadcast().isNull())
            {
                localinfo<<QString("IPv4 Address:%1").arg(entry.ip().toString());
                //IP地址
                localinfo<<QString("Netmask:%1").arg(entry.netmask().toString());
                //子网掩码
                localinfo<<QString("Broadcast:%1").arg(entry.broadcast().toString());
                //广播地址
            }
        }
        localinfo<<QString("*********************************************");
    }
    return localinfo;
}

bool IPInfoTable::eth0_exist()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface, list)
    { //遍历每一个网络接口
        if(interface.name() == "eth0")
            return true;
    }
    return false;
}

bool IPInfoTable::hasValidIP()
{
    QList<QNetworkInterface> list = QNetworkInterface::allInterfaces();
    //获取所有网络接口的列表
    foreach(QNetworkInterface interface, list)
    { //遍历每一个网络接口
        if(interface.name() == "eth0")
        {
            foreach(QNetworkAddressEntry entry,interface.addressEntries())
            {
                if(entry.ip().protocol() == QAbstractSocket::IPv4Protocol)
                {
                    qDebug()<<entry.ip()<<entry.broadcast()<<entry.netmask();
                    if(entry.ip() == QHostAddress("192.168.1.230") || entry.ip().isNull())  //检测到有效IP（系统默认IP为192.168.1.230）
                        return false;
                    else
                        return true;
                }
            }
        }
    }
    return false;
}

void IPInfoTable::showIPInfo()
{
    clear();
    QStringList localinfo = get_ipinfo();
    setText(localinfo.join('\n'));
}