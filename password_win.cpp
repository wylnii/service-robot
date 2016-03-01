#include "password_win.h"
#include "ui_password_win.h"

password_win::password_win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::password_win)
{
    ui->setupUi(this);
    setWindowFlags(Qt::Tool|Qt::WindowStaysOnTopHint|Qt::FramelessWindowHint);
}

password_win::~password_win()
{
    delete ui;
}
void password_win::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() == Qt::LeftButton)
    {
//        move(event->globalPos() - dragPosition);
//        event->accept();
    }
}
void password_win::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
//        dragPosition = event->globalPos() - frameGeometry().topLeft();
//        event->accept();
    }
}
void password_win::textshow(QString t)
{
    if(t=="clear")
    {
        ui->lineEdit_password->clear();
    }
    else if(t=="right")
    {
        ui->lineEdit_password->cursorForward(false,1);
    }
    else if(t=="left")
    {
        ui->lineEdit_password->cursorBackward(false,1);
    }
    else if(t=="back")
    {
        ui->lineEdit_password->backspace();
    }
    else if(t=="ok")
    {
//        if(ui->lineEdit_password->text().length()<8)
//        {
//            this->hide();
//            return;
//        }
        emit sendtext(ui->lineEdit_password->text());
        this->hide();
    }
    else
    {
        ui->lineEdit_password->insert(t);
    }
    ui->lineEdit_password->setFocus();
    setFocus();
}
void password_win::clearpassword()
{
    ui->lineEdit_password->clear();
}
