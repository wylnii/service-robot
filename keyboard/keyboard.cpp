#include "keyboard.h"
#include "ui_keyboard.h"
#include <QThread>
#include <QCryptographicHash>
#include "global.h"

Keyboard::Keyboard(QWidget *parent, const QString &disp, const QString &deflt) :
    QWidget(parent),
    ui(new Ui::Keyboard)
{
    ui->setupUi(this);

    setAutoFillBackground(true);

    QPalette pal = palette();

    QColor color = parentWidget()->palette().color(QPalette::Background);
    color.setAlpha(240);

    pal.setColor(QPalette::Background, color);
    setPalette(pal);

    setStyleSheet("QToolButton::enabled{border:2px outset gray;border-radius:5px;padding:0px 0px;}"
                  "QToolButton::pressed{border-color:#a0a0a0;border:3px groove ;background-color:#d0d0d0;}"
                  "QToolButton::checked{background-color:#000000;border:5px groove green;}"
                  "QToolButton::hover{border-color:#808080;background-color:#d0d0d0;}");

    move(0, (parentWidget()->height() - this->height())*0.94);
    inputMode = iMode_Normal;
    caps_Lock = false;
    saveToFile = true;
    mark.clear();

    signalMapper=new QSignalMapper(this);
    setMapper();//调用了setMapper函数，英文字母数字键盘集群关联信号和漕
    connectMapper();
//    ui->display->hide();
    ui->label->setText(disp);
    setDisplayText(deflt);
    connect(signalMapper,SIGNAL(mapped(const QString&)),
            this,SLOT(setDisplayText(const QString&)));
}

Keyboard::~Keyboard()
{
    delete ui;
}

void Keyboard::setInputMsg(const QString &Msg, const QString &mrk, bool save)
{
    mark= mrk;
    ui->label->setText(Msg);
    saveToFile = save;
    if(save)
        ui->display->setText(loadHistory(mrk));
    else
        ui->display->clear();
}

void Keyboard::setMapper()
{
    //number
    signalMapper->setMapping(ui->toolButton_0,ui->toolButton_0->text());
    signalMapper->setMapping(ui->toolButton_1,ui->toolButton_1->text());
    signalMapper->setMapping(ui->toolButton_2,ui->toolButton_2->text());
    signalMapper->setMapping(ui->toolButton_3,ui->toolButton_3->text());
    signalMapper->setMapping(ui->toolButton_4,ui->toolButton_4->text());
    signalMapper->setMapping(ui->toolButton_5,ui->toolButton_5->text());
    signalMapper->setMapping(ui->toolButton_6,ui->toolButton_6->text());
    signalMapper->setMapping(ui->toolButton_7,ui->toolButton_7->text());
    signalMapper->setMapping(ui->toolButton_8,ui->toolButton_8->text());
    signalMapper->setMapping(ui->toolButton_9,ui->toolButton_9->text());
    //letter
    signalMapper->setMapping(ui->toolButton_a,ui->toolButton_a->text());
    signalMapper->setMapping(ui->toolButton_b,ui->toolButton_b->text());
    signalMapper->setMapping(ui->toolButton_c,ui->toolButton_c->text());
    signalMapper->setMapping(ui->toolButton_d,ui->toolButton_d->text());
    signalMapper->setMapping(ui->toolButton_e,ui->toolButton_e->text());
    signalMapper->setMapping(ui->toolButton_f,ui->toolButton_f->text());
    signalMapper->setMapping(ui->toolButton_g,ui->toolButton_g->text());
    signalMapper->setMapping(ui->toolButton_h,ui->toolButton_h->text());
    signalMapper->setMapping(ui->toolButton_i,ui->toolButton_i->text());
    signalMapper->setMapping(ui->toolButton_j,ui->toolButton_j->text());
    signalMapper->setMapping(ui->toolButton_k,ui->toolButton_k->text());
    signalMapper->setMapping(ui->toolButton_l,ui->toolButton_l->text());
    signalMapper->setMapping(ui->toolButton_m,ui->toolButton_m->text());
    signalMapper->setMapping(ui->toolButton_n,ui->toolButton_n->text());
    signalMapper->setMapping(ui->toolButton_o,ui->toolButton_o->text());
    signalMapper->setMapping(ui->toolButton_p,ui->toolButton_p->text());
    signalMapper->setMapping(ui->toolButton_q,ui->toolButton_q->text());
    signalMapper->setMapping(ui->toolButton_r,ui->toolButton_r->text());
    signalMapper->setMapping(ui->toolButton_s,ui->toolButton_s->text());
    signalMapper->setMapping(ui->toolButton_t,ui->toolButton_t->text());
    signalMapper->setMapping(ui->toolButton_u,ui->toolButton_u->text());
    signalMapper->setMapping(ui->toolButton_v,ui->toolButton_v->text());
    signalMapper->setMapping(ui->toolButton_w,ui->toolButton_w->text());
    signalMapper->setMapping(ui->toolButton_x,ui->toolButton_x->text());
    signalMapper->setMapping(ui->toolButton_y,ui->toolButton_y->text());
    signalMapper->setMapping(ui->toolButton_z,ui->toolButton_z->text());
    //other
    signalMapper->setMapping(ui->toolButton_line1,ui->toolButton_line1->text());
    signalMapper->setMapping(ui->toolButton_line2,ui->toolButton_line2->text());
    signalMapper->setMapping(ui->toolButton_line3,ui->toolButton_line3->text());
    signalMapper->setMapping(ui->toolButton_wenhao,ui->toolButton_wenhao->text());
    signalMapper->setMapping(ui->toolButton_dot,ui->toolButton_dot->text());
    signalMapper->setMapping(ui->toolButton_fenhao,ui->toolButton_fenhao->text());
    signalMapper->setMapping(ui->toolButton_xinghao,ui->toolButton_xinghao->text());
    signalMapper->setMapping(ui->toolButton_space," ");
}
void Keyboard::connectMapper()
{
    connect(ui->toolButton_0,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_1,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_2,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_3,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_4,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_5,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_6,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_7,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_8,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_9,SIGNAL(clicked()),signalMapper,SLOT(map()));
    //letter
    connect(ui->toolButton_a,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_b,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_c,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_d,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_e,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_f,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_g,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_h,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_i,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_j,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_k,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_l,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_m,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_n,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_o,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_p,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_q,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_r,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_s,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_t,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_u,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_v,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_w,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_x,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_y,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_z,SIGNAL(clicked()),signalMapper,SLOT(map()));
    //other
    connect(ui->toolButton_line1,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_line2,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_line3,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_wenhao,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_dot,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_space,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_fenhao,SIGNAL(clicked()),signalMapper,SLOT(map()));
    connect(ui->toolButton_xinghao,SIGNAL(clicked()),signalMapper,SLOT(map()));
}

void Keyboard::on_toolButton_capslock_clicked()
{
    caps_Lock = !caps_Lock;
    if(caps_Lock)
    {
        //letter
        ui->toolButton_a->setText("A");
        ui->toolButton_b->setText("B");
        ui->toolButton_c->setText("C");
        ui->toolButton_d->setText("D");
        ui->toolButton_e->setText("E");
        ui->toolButton_f->setText("F");
        ui->toolButton_g->setText("G");
        ui->toolButton_h->setText("H");
        ui->toolButton_i->setText("I");
        ui->toolButton_j->setText("J");
        ui->toolButton_k->setText("K");
        ui->toolButton_l->setText("L");
        ui->toolButton_m->setText("M");
        ui->toolButton_n->setText("N");
        ui->toolButton_o->setText("O");
        ui->toolButton_p->setText("P");
        ui->toolButton_q->setText("Q");
        ui->toolButton_r->setText("R");
        ui->toolButton_s->setText("S");
        ui->toolButton_t->setText("T");
        ui->toolButton_u->setText("U");
        ui->toolButton_v->setText("V");
        ui->toolButton_w->setText("W");
        ui->toolButton_x->setText("X");
        ui->toolButton_y->setText("Y");
        ui->toolButton_z->setText("Z");
        ui->toolButton_fenhao->setText(";");
        ui->toolButton_line3->setText("-");
        ui->toolButton_line2->setText("%");
        ui->toolButton_line1->setText("+");
        ui->toolButton_xinghao->setText("#");
        ui->toolButton_dot->setText("!");
        ui->toolButton_wenhao->setText("@");
    }
    else
    {
        //letter
        ui->toolButton_a->setText("a");
        ui->toolButton_b->setText("b");
        ui->toolButton_c->setText("c");
        ui->toolButton_d->setText("d");
        ui->toolButton_e->setText("e");
        ui->toolButton_f->setText("f");
        ui->toolButton_g->setText("g");
        ui->toolButton_h->setText("h");
        ui->toolButton_i->setText("i");
        ui->toolButton_j->setText("j");
        ui->toolButton_k->setText("k");
        ui->toolButton_l->setText("l");
        ui->toolButton_m->setText("m");
        ui->toolButton_n->setText("n");
        ui->toolButton_o->setText("o");
        ui->toolButton_p->setText("p");
        ui->toolButton_q->setText("q");
        ui->toolButton_r->setText("r");
        ui->toolButton_s->setText("s");
        ui->toolButton_t->setText("t");
        ui->toolButton_u->setText("u");
        ui->toolButton_v->setText("v");
        ui->toolButton_w->setText("w");
        ui->toolButton_x->setText("x");
        ui->toolButton_y->setText("y");
        ui->toolButton_z->setText("z");
        ui->toolButton_fenhao->setText(":");
        ui->toolButton_line3->setText("_");
        ui->toolButton_line2->setText("\\");
        ui->toolButton_line1->setText("/");
        ui->toolButton_xinghao->setText("*");
        ui->toolButton_dot->setText(".");
        ui->toolButton_wenhao->setText("?");
    }
    setMapper();
}

void Keyboard::on_toolButton_inv_clicked()
{
    if(inputMode == iMode_Normal)
    {
        inputMode = iMode_Passwd;
    }
    else if(inputMode == iMode_Passwd)
    {
        inputMode = iMode_Normal;
    }

    if(inputMode == iMode_Normal)
    {
        ui->display->setEchoMode(QLineEdit::Normal);
    }
    else if(inputMode == iMode_Passwd)
    {
        ui->display->setEchoMode(QLineEdit::Password);
    }
}

void Keyboard::on_toolButton_enter_clicked()
{
    this->hide();
    if(!ui->display->text().isEmpty() && saveToFile)
    {
        saveHistory(ui->display->text(),mark);
    }
        emit enter(ui->display->text(), mark);
}

void Keyboard::on_toolButton_backspace_clicked()
{
    ui->display->backspace();
    emit press("back");
}

void Keyboard::on_toolButton_left_clicked()
{
    ui->display->cursorBackward(false,1);
    emit press("left");
}

void Keyboard::on_toolButton_right_clicked()
{
    ui->display->cursorForward(false,1);
    emit press("right");
}

void Keyboard::on_toolButton_esc_clicked()
{
    if(ui->display->text().isEmpty())
    {
        close();
        return;
    }
    ui->display->clear();
    emit press("clear");
}

void Keyboard::show()
{
    ui->display->setFocus();
    QWidget::show();
}

QString Keyboard::getMark() const
{
    return mark;
}

void Keyboard::setDisplayText(const QString &text)
{
    if(text.length()>1)
        ui->display->setText(text);
    else
        ui->display->insert(text);
    emit press(text);
}
