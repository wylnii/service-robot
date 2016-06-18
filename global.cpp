#include "global.h"

QString RobotName;
QTextCodec *textCodec = QTextCodec::codecForName("GB18030");
QStringList EmotionList;   //for SSDB
QStringList VideoPlaylist;   //for SSDB

QByteArray encrypt(const QByteArray &code, bool en) //0:en+, 1:de-
{
    if(! en)
    {
        return code.toBase64().toBase64();
    }
    else
    {
        return code.fromBase64(code.fromBase64(code));
    }
}

QByteArray loadHistory(const QString &mrk, const QVariant &default_value, const QString &group)
{
    QByteArray value;
    QSettings settings("configure.ini",QSettings::IniFormat);
    settings.beginGroup(group);
    if(! mrk.isEmpty())
    {
        value = settings.value(mrk, default_value).toByteArray();
//        qDebug()<<"load"<<value<<mrk;
    }
    settings.endGroup();
    return (mrk[0] == '#'? encrypt(value,true):value);
}

void saveHistory(const QVariant &input, const QString &mrk, const QString &group)
{
        QSettings settings("configure.ini",QSettings::IniFormat);
        settings.beginGroup(group);
        if(! input.isNull() && ! mrk.isEmpty())
        {
            settings.setValue(mrk, mrk[0] == '#'? encrypt(input.toByteArray()):input);
//            qDebug()<<"save"<<input<<mrk;
        }
        settings.endGroup();
}
