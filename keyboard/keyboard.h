#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>
#include <QSignalMapper>
#include <QMouseEvent>
#include <QDebug>

namespace Ui {
class Keyboard;
}

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = 0, const QString & disp = QLatin1String("Input:"), const QString &deflt = QString());
    ~Keyboard();
    enum
    {
        iMode_Normal = 0,
        iMode_Passwd = 1
    }; //密码模式与正常模式
    void setInputMsg(const QString & Msg, const QString &mrk = QString(), bool save = true);//set input tips

    QString getMark() const;

signals:
    void press(QString);
    void enter(QString, QString);

private slots:
    void on_toolButton_capslock_clicked();//大小写锁定
    void on_toolButton_inv_clicked();//显示模式设置
    void on_toolButton_enter_clicked();//确认
    void on_toolButton_backspace_clicked();//删除
    void on_toolButton_left_clicked();//光标左移
    void on_toolButton_right_clicked();//光标右移
    void on_toolButton_esc_clicked();//推出键盘

public slots:
    void setDisplayText(const QString& text);//显示输入
    void show();

private:
    Ui::Keyboard *ui;
    int inputMode;//文本显示模式：密码或者正常
    QSignalMapper *signalMapper;
    bool caps_Lock;//大小写锁定,1为大写，0为小写
    QString mark;
    bool saveToFile;

    void setMapper();//映射信号
    void connectMapper();//连接信号
};

#endif // KEYBOARD_H
