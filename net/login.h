#ifndef LOGIN_H
#define LOGIN_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QThread>
#include <QElapsedTimer>

class Login : public QObject
{
    Q_OBJECT
public:
    explicit Login(QObject *parent = 0);
    ~Login();
    int login();
    int login(const QString& name, const QString& password);
    int getMaterial();
    void setUserData(const QString& name, const QString& password);
    int getReturnCode() const;
    QString getURL() const;

private:
    void request(const QString& url);

    QNetworkAccessManager *manager;
    QNetworkReply *reply;
    QString URL;
    QThread *mThread;
    QByteArray data;
    QElapsedTimer timer;
    int return_code;
    QString userName;
    QString userPassword;
    QString key;
    int robotId;
    bool isOnline;

signals:
    void finished(int code);

public slots:
    void readData(qint64 bytesReceived, qint64 bytesTotal);
    void readData();
    void doFinish();
    void doSslErrors(QNetworkReply::NetworkError err);

};

#endif // LOGIN_H
