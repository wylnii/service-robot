#include "mainwindow.h"
#include <QApplication>
#include "global.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &contex, const QString &msg);
void checkLogfileSize(int maxSize = 1024*1024);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if(argc > 1)
    {
        QCommandLineParser parser;
        QCommandLineOption o1("t", "test network delay", "pattern", "");
        parser.addOption(o1);
        parser.addVersionOption();
        parser.addHelpOption();
        QString info = QString("\r%1 %2(%6x%7)\ncompiled at:\t%3 %4\npowered by:\t%5")
                .arg(a.applicationName(), VERSION_STR, __DATE__, __TIME__, "WYL")
                .arg(SCREEN_WIDTH).arg(SCREEN_HEIGHT);
        a.setApplicationVersion(VERSION+info);
        parser.setApplicationDescription(info);
        parser.process(a);
        if(parser.isSet(o1))
        {
            NetworkQualityThread c;
            if(argc > 2)
            {
                qDebug()<<c.getNetworkQuality(parser.value(o1));
            }
            else
            {
                qDebug()<<c.getNetworkQuality();
            }
            return 0;
        }
        return 0;
    }

//    qSetMessagePattern("%{time MM/dd HH:mm:ss.zzz} : %{message}");
    //启动时检查log文件大小，大于1M则分卷保存
    checkLogfileSize();

    qInstallMessageHandler(customMessageHandler);

    qDebug()<<endl<<a.applicationName().toLocal8Bit().data()<<VERSION_STR<<__DATE__<<__TIME__
           <<"\nstart :\t"<<a.arguments()<<"\n";

    QFont f("WenQuanYi Micro Hei");
#ifdef HD_SCREEN
    f.setPointSize(16);
#else
    f.setPointSize(10);
#endif
    a.setFont(f);

    MainWindow w;
    w.show();

    return a.exec();
}

void checkLogfileSize(int maxSize)
{
    QFile file(LOG_FILE);
    int size = file.size();
    if(size > maxSize)
    {
        QString newFilename = QDateTime::currentDateTime().toString("log-yyyyMMddHHmmss'.txt'");
        qDebug()<<newFilename;
        file.rename(newFilename);
    }
}

void recordLog(const QString &log)
{
    QString time = QDateTime::currentDateTime().toString("MM/dd HH:mm:ss.zzz -> ");
    QString msg("echo '%1%2' >> %3");
    msg = msg.arg(time,log,LOG_FILE);
//    QFile outFile("log.txt");
//    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
//    QTextStream out(&outFile);
//    out << time << log << "\r\n";
//    outFile.close();
    system(msg.toLocal8Bit().constData());
}

void customMessageHandler(QtMsgType type, const QMessageLogContext &contex, const QString &msg)
{
    Q_UNUSED(contex);
    QString log;
    switch ((int)type)
    {
    case QtDebugMsg:
        log = msg;
        break;
    case QtWarningMsg:
//        log = QString("Warning: %1").arg(msg);
        fprintf(stderr,"%s\n",msg.toLocal8Bit().constData());
        return;
        break;
    case QtCriticalMsg:
        log = QString("Critical: %1").arg(msg);
        break;
    case QtFatalMsg:
        log = QString("Fatal: %1").arg(msg);
        break;
    default:
        break;
    }
#ifdef RECORD_LOG
    recordLog(log);
#endif
#ifdef PRINT_SCREEN
    fprintf(stderr,"%s\n",msg.toLocal8Bit().constData());
#endif
}
