#include "mainwindow.h"
#include <QApplication>
#include "global.h"

void customMessageHandler(QtMsgType type, const QMessageLogContext &contex, const QString &msg);

int main(int argc, char *argv[])
{
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB18030"));

//    qSetMessagePattern("%{time MM/dd HH:mm:ss.zzz} : %{message}");
    qInstallMessageHandler(customMessageHandler);

    QApplication a(argc, argv);
    qDebug()<<"\n\nstart :\t"<<a.arguments()<<"\n";

    QFont f("WenQuanYi Micro Hei");
    f.setPointSize(16);
    a.setFont(f);

    MainWindow w;
    w.show();

    return a.exec();
}

void recordLog(const QString &log)
{
    QString time = QDateTime::currentDateTime().toString("MM/dd HH:mm:ss.zzz -> ");
    QFile outFile("log.txt");
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream out(&outFile);
    out << time << log << "\r\n";
    outFile.close();
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
        fprintf(stderr,"%s\n",msg.toLatin1().constData());
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
    fprintf(stderr,"%s\n",msg.toLatin1().constData());
#endif
}
