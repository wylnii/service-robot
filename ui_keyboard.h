/********************************************************************************
** Form generated from reading UI file 'keyboard.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_KEYBOARD_H
#define UI_KEYBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Keyboard
{
public:
    QLineEdit *display;
    QGroupBox *groupBox;
    QFrame *line;
    QToolButton *toolButton_z;
    QToolButton *toolButton_n;
    QToolButton *toolButton_3;
    QToolButton *toolButton_8;
    QToolButton *toolButton_i;
    QToolButton *toolButton_j;
    QToolButton *toolButton_6;
    QToolButton *toolButton_5;
    QToolButton *toolButton_u;
    QToolButton *toolButton_w;
    QToolButton *toolButton_inv;
    QToolButton *toolButton_c;
    QToolButton *toolButton_2;
    QToolButton *toolButton_xinghao;
    QToolButton *toolButton_line1;
    QToolButton *toolButton_1;
    QToolButton *toolButton_fenhao;
    QToolButton *toolButton_p;
    QToolButton *toolButton_e;
    QToolButton *toolButton_esc;
    QToolButton *toolButton_9;
    QToolButton *toolButton_t;
    QToolButton *toolButton_0;
    QToolButton *toolButton_s;
    QToolButton *toolButton_r;
    QToolButton *toolButton_h;
    QToolButton *toolButton_a;
    QToolButton *toolButton_y;
    QToolButton *toolButton_l;
    QToolButton *toolButton_f;
    QToolButton *toolButton_line3;
    QToolButton *toolButton_right;
    QToolButton *toolButton_q;
    QToolButton *toolButton_b;
    QToolButton *toolButton_o;
    QToolButton *toolButton_left;
    QToolButton *toolButton_v;
    QToolButton *toolButton_capslock;
    QToolButton *toolButton_k;
    QToolButton *toolButton_wenhao;
    QToolButton *toolButton_x;
    QToolButton *toolButton_backspace;
    QToolButton *toolButton_enter;
    QToolButton *toolButton_7;
    QToolButton *toolButton_dot;
    QToolButton *toolButton_d;
    QToolButton *toolButton_space;
    QToolButton *toolButton_g;
    QToolButton *toolButton_4;
    QToolButton *toolButton_line2;
    QToolButton *toolButton_m;
    QLabel *label;

    void setupUi(QWidget *Keyboard)
    {
        if (Keyboard->objectName().isEmpty())
            Keyboard->setObjectName(QStringLiteral("Keyboard"));
        Keyboard->resize(800, 213);
        display = new QLineEdit(Keyboard);
        display->setObjectName(QStringLiteral("display"));
        display->setGeometry(QRect(225, 10, 400, 31));
        QFont font;
        font.setPointSize(11);
        display->setFont(font);
        groupBox = new QGroupBox(Keyboard);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(0, 40, 800, 171));
        line = new QFrame(groupBox);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(576, 10, 16, 156));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        toolButton_z = new QToolButton(groupBox);
        toolButton_z->setObjectName(QStringLiteral("toolButton_z"));
        toolButton_z->setGeometry(QRect(141, 85, 50, 40));
        toolButton_z->setFocusPolicy(Qt::NoFocus);
        toolButton_n = new QToolButton(groupBox);
        toolButton_n->setObjectName(QStringLiteral("toolButton_n"));
        toolButton_n->setGeometry(QRect(391, 85, 50, 40));
        toolButton_n->setFocusPolicy(Qt::NoFocus);
        toolButton_3 = new QToolButton(groupBox);
        toolButton_3->setObjectName(QStringLiteral("toolButton_3"));
        toolButton_3->setGeometry(QRect(740, 85, 50, 40));
        toolButton_3->setFocusPolicy(Qt::NoFocus);
        toolButton_8 = new QToolButton(groupBox);
        toolButton_8->setObjectName(QStringLiteral("toolButton_8"));
        toolButton_8->setGeometry(QRect(690, 7, 50, 40));
        toolButton_8->setFocusPolicy(Qt::NoFocus);
        toolButton_i = new QToolButton(groupBox);
        toolButton_i->setObjectName(QStringLiteral("toolButton_i"));
        toolButton_i->setGeometry(QRect(426, 7, 50, 40));
        toolButton_i->setFocusPolicy(Qt::NoFocus);
        toolButton_j = new QToolButton(groupBox);
        toolButton_j->setObjectName(QStringLiteral("toolButton_j"));
        toolButton_j->setGeometry(QRect(426, 46, 50, 40));
        toolButton_j->setFocusPolicy(Qt::NoFocus);
        toolButton_6 = new QToolButton(groupBox);
        toolButton_6->setObjectName(QStringLiteral("toolButton_6"));
        toolButton_6->setGeometry(QRect(740, 46, 50, 40));
        toolButton_6->setFocusPolicy(Qt::NoFocus);
        toolButton_5 = new QToolButton(groupBox);
        toolButton_5->setObjectName(QStringLiteral("toolButton_5"));
        toolButton_5->setGeometry(QRect(690, 46, 50, 40));
        toolButton_5->setFocusPolicy(Qt::NoFocus);
        toolButton_u = new QToolButton(groupBox);
        toolButton_u->setObjectName(QStringLiteral("toolButton_u"));
        toolButton_u->setGeometry(QRect(376, 7, 50, 40));
        toolButton_u->setFocusPolicy(Qt::NoFocus);
        toolButton_w = new QToolButton(groupBox);
        toolButton_w->setObjectName(QStringLiteral("toolButton_w"));
        toolButton_w->setGeometry(QRect(126, 7, 50, 40));
        toolButton_w->setFocusPolicy(Qt::NoFocus);
        toolButton_inv = new QToolButton(groupBox);
        toolButton_inv->setObjectName(QStringLiteral("toolButton_inv"));
        toolButton_inv->setGeometry(QRect(75, 124, 66, 40));
        toolButton_c = new QToolButton(groupBox);
        toolButton_c->setObjectName(QStringLiteral("toolButton_c"));
        toolButton_c->setGeometry(QRect(241, 85, 50, 40));
        toolButton_c->setFocusPolicy(Qt::NoFocus);
        toolButton_2 = new QToolButton(groupBox);
        toolButton_2->setObjectName(QStringLiteral("toolButton_2"));
        toolButton_2->setGeometry(QRect(690, 85, 50, 40));
        toolButton_2->setFocusPolicy(Qt::NoFocus);
        toolButton_xinghao = new QToolButton(groupBox);
        toolButton_xinghao->setObjectName(QStringLiteral("toolButton_xinghao"));
        toolButton_xinghao->setGeometry(QRect(590, 7, 50, 40));
        toolButton_xinghao->setFocusPolicy(Qt::NoFocus);
        toolButton_line1 = new QToolButton(groupBox);
        toolButton_line1->setObjectName(QStringLiteral("toolButton_line1"));
        toolButton_line1->setGeometry(QRect(10, 46, 65, 40));
        toolButton_line1->setFocusPolicy(Qt::NoFocus);
        toolButton_1 = new QToolButton(groupBox);
        toolButton_1->setObjectName(QStringLiteral("toolButton_1"));
        toolButton_1->setGeometry(QRect(640, 85, 50, 40));
        toolButton_1->setFocusPolicy(Qt::NoFocus);
        toolButton_fenhao = new QToolButton(groupBox);
        toolButton_fenhao->setObjectName(QStringLiteral("toolButton_fenhao"));
        toolButton_fenhao->setGeometry(QRect(491, 85, 85, 40));
        toolButton_fenhao->setFocusPolicy(Qt::NoFocus);
        toolButton_p = new QToolButton(groupBox);
        toolButton_p->setObjectName(QStringLiteral("toolButton_p"));
        toolButton_p->setGeometry(QRect(526, 7, 50, 40));
        toolButton_p->setFocusPolicy(Qt::NoFocus);
        toolButton_e = new QToolButton(groupBox);
        toolButton_e->setObjectName(QStringLiteral("toolButton_e"));
        toolButton_e->setGeometry(QRect(176, 7, 50, 40));
        toolButton_e->setFocusPolicy(Qt::NoFocus);
        toolButton_esc = new QToolButton(groupBox);
        toolButton_esc->setObjectName(QStringLiteral("toolButton_esc"));
        toolButton_esc->setGeometry(QRect(10, 124, 65, 40));
        toolButton_9 = new QToolButton(groupBox);
        toolButton_9->setObjectName(QStringLiteral("toolButton_9"));
        toolButton_9->setGeometry(QRect(740, 7, 50, 40));
        toolButton_9->setFocusPolicy(Qt::NoFocus);
        toolButton_t = new QToolButton(groupBox);
        toolButton_t->setObjectName(QStringLiteral("toolButton_t"));
        toolButton_t->setGeometry(QRect(276, 7, 50, 40));
        toolButton_t->setFocusPolicy(Qt::NoFocus);
        toolButton_0 = new QToolButton(groupBox);
        toolButton_0->setObjectName(QStringLiteral("toolButton_0"));
        toolButton_0->setGeometry(QRect(590, 85, 50, 40));
        toolButton_0->setFocusPolicy(Qt::NoFocus);
        toolButton_s = new QToolButton(groupBox);
        toolButton_s->setObjectName(QStringLiteral("toolButton_s"));
        toolButton_s->setGeometry(QRect(176, 46, 50, 40));
        toolButton_s->setFocusPolicy(Qt::NoFocus);
        toolButton_r = new QToolButton(groupBox);
        toolButton_r->setObjectName(QStringLiteral("toolButton_r"));
        toolButton_r->setGeometry(QRect(226, 7, 50, 40));
        toolButton_r->setFocusPolicy(Qt::NoFocus);
        toolButton_h = new QToolButton(groupBox);
        toolButton_h->setObjectName(QStringLiteral("toolButton_h"));
        toolButton_h->setGeometry(QRect(376, 46, 50, 40));
        toolButton_h->setFocusPolicy(Qt::NoFocus);
        toolButton_a = new QToolButton(groupBox);
        toolButton_a->setObjectName(QStringLiteral("toolButton_a"));
        toolButton_a->setGeometry(QRect(126, 46, 50, 40));
        toolButton_a->setFocusPolicy(Qt::NoFocus);
        toolButton_y = new QToolButton(groupBox);
        toolButton_y->setObjectName(QStringLiteral("toolButton_y"));
        toolButton_y->setGeometry(QRect(326, 7, 50, 40));
        toolButton_y->setFocusPolicy(Qt::NoFocus);
        toolButton_l = new QToolButton(groupBox);
        toolButton_l->setObjectName(QStringLiteral("toolButton_l"));
        toolButton_l->setGeometry(QRect(526, 46, 50, 40));
        toolButton_l->setFocusPolicy(Qt::NoFocus);
        toolButton_f = new QToolButton(groupBox);
        toolButton_f->setObjectName(QStringLiteral("toolButton_f"));
        toolButton_f->setGeometry(QRect(276, 46, 50, 40));
        toolButton_f->setFocusPolicy(Qt::NoFocus);
        toolButton_line3 = new QToolButton(groupBox);
        toolButton_line3->setObjectName(QStringLiteral("toolButton_line3"));
        toolButton_line3->setGeometry(QRect(75, 85, 66, 40));
        toolButton_line3->setFocusPolicy(Qt::NoFocus);
        toolButton_right = new QToolButton(groupBox);
        toolButton_right->setObjectName(QStringLiteral("toolButton_right"));
        toolButton_right->setGeometry(QRect(499, 124, 77, 40));
        toolButton_q = new QToolButton(groupBox);
        toolButton_q->setObjectName(QStringLiteral("toolButton_q"));
        toolButton_q->setGeometry(QRect(76, 7, 50, 40));
        toolButton_q->setFocusPolicy(Qt::NoFocus);
        toolButton_b = new QToolButton(groupBox);
        toolButton_b->setObjectName(QStringLiteral("toolButton_b"));
        toolButton_b->setGeometry(QRect(341, 85, 50, 40));
        toolButton_b->setFocusPolicy(Qt::NoFocus);
        toolButton_o = new QToolButton(groupBox);
        toolButton_o->setObjectName(QStringLiteral("toolButton_o"));
        toolButton_o->setGeometry(QRect(476, 7, 50, 40));
        toolButton_o->setFocusPolicy(Qt::NoFocus);
        toolButton_left = new QToolButton(groupBox);
        toolButton_left->setObjectName(QStringLiteral("toolButton_left"));
        toolButton_left->setGeometry(QRect(423, 124, 77, 40));
        toolButton_v = new QToolButton(groupBox);
        toolButton_v->setObjectName(QStringLiteral("toolButton_v"));
        toolButton_v->setGeometry(QRect(291, 85, 50, 40));
        toolButton_v->setFocusPolicy(Qt::NoFocus);
        toolButton_capslock = new QToolButton(groupBox);
        toolButton_capslock->setObjectName(QStringLiteral("toolButton_capslock"));
        toolButton_capslock->setGeometry(QRect(10, 7, 65, 40));
        toolButton_capslock->setFocusPolicy(Qt::TabFocus);
        toolButton_k = new QToolButton(groupBox);
        toolButton_k->setObjectName(QStringLiteral("toolButton_k"));
        toolButton_k->setGeometry(QRect(476, 46, 50, 40));
        toolButton_k->setFocusPolicy(Qt::NoFocus);
        toolButton_wenhao = new QToolButton(groupBox);
        toolButton_wenhao->setObjectName(QStringLiteral("toolButton_wenhao"));
        toolButton_wenhao->setGeometry(QRect(76, 46, 50, 40));
        toolButton_wenhao->setFocusPolicy(Qt::NoFocus);
        toolButton_x = new QToolButton(groupBox);
        toolButton_x->setObjectName(QStringLiteral("toolButton_x"));
        toolButton_x->setGeometry(QRect(191, 85, 50, 40));
        toolButton_x->setFocusPolicy(Qt::NoFocus);
        toolButton_backspace = new QToolButton(groupBox);
        toolButton_backspace->setObjectName(QStringLiteral("toolButton_backspace"));
        toolButton_backspace->setGeometry(QRect(590, 124, 100, 40));
        toolButton_enter = new QToolButton(groupBox);
        toolButton_enter->setObjectName(QStringLiteral("toolButton_enter"));
        toolButton_enter->setGeometry(QRect(690, 124, 100, 40));
        toolButton_7 = new QToolButton(groupBox);
        toolButton_7->setObjectName(QStringLiteral("toolButton_7"));
        toolButton_7->setGeometry(QRect(640, 7, 50, 40));
        toolButton_7->setFocusPolicy(Qt::NoFocus);
        toolButton_dot = new QToolButton(groupBox);
        toolButton_dot->setObjectName(QStringLiteral("toolButton_dot"));
        toolButton_dot->setGeometry(QRect(590, 46, 50, 40));
        toolButton_dot->setFocusPolicy(Qt::NoFocus);
        toolButton_d = new QToolButton(groupBox);
        toolButton_d->setObjectName(QStringLiteral("toolButton_d"));
        toolButton_d->setGeometry(QRect(226, 46, 50, 40));
        toolButton_d->setFocusPolicy(Qt::NoFocus);
        toolButton_space = new QToolButton(groupBox);
        toolButton_space->setObjectName(QStringLiteral("toolButton_space"));
        toolButton_space->setGeometry(QRect(141, 124, 281, 40));
        toolButton_space->setFocusPolicy(Qt::NoFocus);
        toolButton_g = new QToolButton(groupBox);
        toolButton_g->setObjectName(QStringLiteral("toolButton_g"));
        toolButton_g->setGeometry(QRect(326, 46, 50, 40));
        toolButton_g->setFocusPolicy(Qt::NoFocus);
        toolButton_4 = new QToolButton(groupBox);
        toolButton_4->setObjectName(QStringLiteral("toolButton_4"));
        toolButton_4->setGeometry(QRect(640, 46, 50, 40));
        toolButton_4->setFocusPolicy(Qt::NoFocus);
        toolButton_line2 = new QToolButton(groupBox);
        toolButton_line2->setObjectName(QStringLiteral("toolButton_line2"));
        toolButton_line2->setGeometry(QRect(10, 85, 65, 40));
        toolButton_line2->setFocusPolicy(Qt::NoFocus);
        toolButton_m = new QToolButton(groupBox);
        toolButton_m->setObjectName(QStringLiteral("toolButton_m"));
        toolButton_m->setGeometry(QRect(441, 85, 50, 40));
        toolButton_m->setFocusPolicy(Qt::NoFocus);
        label = new QLabel(Keyboard);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(15, 10, 201, 31));
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
#ifndef QT_NO_SHORTCUT
        label->setBuddy(display);
#endif // QT_NO_SHORTCUT
        QWidget::setTabOrder(display, toolButton_capslock);
        QWidget::setTabOrder(toolButton_capslock, toolButton_esc);
        QWidget::setTabOrder(toolButton_esc, toolButton_inv);
        QWidget::setTabOrder(toolButton_inv, toolButton_left);
        QWidget::setTabOrder(toolButton_left, toolButton_right);
        QWidget::setTabOrder(toolButton_right, toolButton_backspace);
        QWidget::setTabOrder(toolButton_backspace, toolButton_enter);

        retranslateUi(Keyboard);

        QMetaObject::connectSlotsByName(Keyboard);
    } // setupUi

    void retranslateUi(QWidget *Keyboard)
    {
        Keyboard->setWindowTitle(QApplication::translate("Keyboard", "keyboard", 0));
        toolButton_z->setText(QApplication::translate("Keyboard", "z", 0));
        toolButton_n->setText(QApplication::translate("Keyboard", "n", 0));
        toolButton_3->setText(QApplication::translate("Keyboard", "3", 0));
        toolButton_8->setText(QApplication::translate("Keyboard", "8", 0));
        toolButton_i->setText(QApplication::translate("Keyboard", "i", 0));
        toolButton_j->setText(QApplication::translate("Keyboard", "j", 0));
        toolButton_6->setText(QApplication::translate("Keyboard", "6", 0));
        toolButton_5->setText(QApplication::translate("Keyboard", "5", 0));
        toolButton_u->setText(QApplication::translate("Keyboard", "u", 0));
        toolButton_w->setText(QApplication::translate("Keyboard", "w", 0));
        toolButton_inv->setText(QApplication::translate("Keyboard", "Inv", 0));
        toolButton_c->setText(QApplication::translate("Keyboard", "c", 0));
        toolButton_2->setText(QApplication::translate("Keyboard", "2", 0));
        toolButton_xinghao->setText(QApplication::translate("Keyboard", "*", 0));
        toolButton_line1->setText(QApplication::translate("Keyboard", "/", 0));
        toolButton_1->setText(QApplication::translate("Keyboard", "1", 0));
        toolButton_fenhao->setText(QApplication::translate("Keyboard", ":", 0));
        toolButton_p->setText(QApplication::translate("Keyboard", "p", 0));
        toolButton_e->setText(QApplication::translate("Keyboard", "e", 0));
        toolButton_esc->setText(QApplication::translate("Keyboard", "Clr", 0));
        toolButton_9->setText(QApplication::translate("Keyboard", "9", 0));
        toolButton_t->setText(QApplication::translate("Keyboard", "t", 0));
        toolButton_0->setText(QApplication::translate("Keyboard", "0", 0));
        toolButton_s->setText(QApplication::translate("Keyboard", "s", 0));
        toolButton_r->setText(QApplication::translate("Keyboard", "r", 0));
        toolButton_h->setText(QApplication::translate("Keyboard", "h", 0));
        toolButton_a->setText(QApplication::translate("Keyboard", "a", 0));
        toolButton_y->setText(QApplication::translate("Keyboard", "y", 0));
        toolButton_l->setText(QApplication::translate("Keyboard", "l", 0));
        toolButton_f->setText(QApplication::translate("Keyboard", "f", 0));
        toolButton_line3->setText(QApplication::translate("Keyboard", "_", 0));
        toolButton_right->setText(QApplication::translate("Keyboard", "-->", 0));
        toolButton_q->setText(QApplication::translate("Keyboard", "q", 0));
        toolButton_b->setText(QApplication::translate("Keyboard", "b", 0));
        toolButton_o->setText(QApplication::translate("Keyboard", "o", 0));
        toolButton_left->setText(QApplication::translate("Keyboard", "<--", 0));
        toolButton_v->setText(QApplication::translate("Keyboard", "v", 0));
        toolButton_capslock->setText(QApplication::translate("Keyboard", "Caps", 0));
        toolButton_k->setText(QApplication::translate("Keyboard", "k", 0));
        toolButton_wenhao->setText(QApplication::translate("Keyboard", "?", 0));
        toolButton_x->setText(QApplication::translate("Keyboard", "x", 0));
        toolButton_backspace->setText(QApplication::translate("Keyboard", "DEL", 0));
        toolButton_enter->setText(QApplication::translate("Keyboard", "Enter", 0));
        toolButton_7->setText(QApplication::translate("Keyboard", "7", 0));
        toolButton_dot->setText(QApplication::translate("Keyboard", ".", 0));
        toolButton_d->setText(QApplication::translate("Keyboard", "d", 0));
        toolButton_space->setText(QApplication::translate("Keyboard", "Space", 0));
        toolButton_g->setText(QApplication::translate("Keyboard", "g", 0));
        toolButton_4->setText(QApplication::translate("Keyboard", "4", 0));
        toolButton_line2->setText(QApplication::translate("Keyboard", "\\", 0));
        toolButton_m->setText(QApplication::translate("Keyboard", "m", 0));
        label->setText(QApplication::translate("Keyboard", "Input:", 0));
    } // retranslateUi

};

namespace Ui {
    class Keyboard: public Ui_Keyboard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_KEYBOARD_H
