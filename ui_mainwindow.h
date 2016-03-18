/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabWidgetPage1;
    QLabel *label_3;
    QLabel *label;
    QSlider *verticalSlider_2;
    QWidget *tabWidgetPage2;
    QWidget *widget_4;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton_scan;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_openssdb;
    QPushButton *pushButton_disconnect;
    QWidget *tabWidgetPage3;
    QWidget *tabWidgetPage4;
    QWidget *widget_videoCtrl;
    QSlider *verticalSlider;
    QLabel *label_5;
    QToolButton *toolButton_play;
    QToolButton *toolButton_last;
    QToolButton *toolButton_next;
    QWidget *widget_3;
    QPushButton *pushButton_download;
    QGroupBox *groupBox;
    QPushButton *pushButton_openPort;
    QLabel *label_2;
    QLabel *label_4;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QToolButton *toolButton_show;
    QToolButton *toolButton_test;
    QWidget *tabWidgetPage5;
    QWidget *widget;
    QToolButton *toolButton_right;
    QToolButton *toolButton_left;
    QToolButton *toolButton_stop;
    QToolButton *toolButton_up;
    QToolButton *toolButton_down;
    QToolButton *toolButton_headup;
    QToolButton *toolButton_headdown;
    QToolButton *toolButton_charge;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 480);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 800, 460));
        tabWidget->setFocusPolicy(Qt::NoFocus);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QStringLiteral("tabWidgetPage1"));
        label_3 = new QLabel(tabWidgetPage1);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(290, 80, 211, 211));
        label_3->setPixmap(QPixmap(QString::fromUtf8(":/image/resource/logo.png")));
        label = new QLabel(tabWidgetPage1);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(5, 340, 786, 86));
        QFont font;
        font.setPointSize(24);
        label->setFont(font);
        label->setStyleSheet(QStringLiteral("color: rgb(249, 19, 19);"));
        label->setAlignment(Qt::AlignCenter);
        verticalSlider_2 = new QSlider(tabWidgetPage1);
        verticalSlider_2->setObjectName(QStringLiteral("verticalSlider_2"));
        verticalSlider_2->setGeometry(QRect(690, 105, 29, 216));
        verticalSlider_2->setFocusPolicy(Qt::NoFocus);
        verticalSlider_2->setMaximum(127);
        verticalSlider_2->setValue(127);
        verticalSlider_2->setOrientation(Qt::Vertical);
        tabWidget->addTab(tabWidgetPage1, QString());
        tabWidgetPage2 = new QWidget();
        tabWidgetPage2->setObjectName(QStringLiteral("tabWidgetPage2"));
        widget_4 = new QWidget(tabWidgetPage2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        widget_4->setGeometry(QRect(610, 15, 171, 386));
        layoutWidget = new QWidget(widget_4);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(40, 25, 95, 346));
        verticalLayout = new QVBoxLayout(layoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton_scan = new QPushButton(layoutWidget);
        pushButton_scan->setObjectName(QStringLiteral("pushButton_scan"));
        pushButton_scan->setMinimumSize(QSize(0, 34));

        verticalLayout->addWidget(pushButton_scan);

        pushButton_connect = new QPushButton(layoutWidget);
        pushButton_connect->setObjectName(QStringLiteral("pushButton_connect"));
        pushButton_connect->setMinimumSize(QSize(0, 34));

        verticalLayout->addWidget(pushButton_connect);

        pushButton_openssdb = new QPushButton(layoutWidget);
        pushButton_openssdb->setObjectName(QStringLiteral("pushButton_openssdb"));
        pushButton_openssdb->setMinimumSize(QSize(0, 34));

        verticalLayout->addWidget(pushButton_openssdb);

        pushButton_disconnect = new QPushButton(layoutWidget);
        pushButton_disconnect->setObjectName(QStringLiteral("pushButton_disconnect"));
        pushButton_disconnect->setMinimumSize(QSize(0, 34));

        verticalLayout->addWidget(pushButton_disconnect);

        tabWidget->addTab(tabWidgetPage2, QString());
        tabWidgetPage3 = new QWidget();
        tabWidgetPage3->setObjectName(QStringLiteral("tabWidgetPage3"));
        tabWidget->addTab(tabWidgetPage3, QString());
        tabWidgetPage4 = new QWidget();
        tabWidgetPage4->setObjectName(QStringLiteral("tabWidgetPage4"));
        widget_videoCtrl = new QWidget(tabWidgetPage4);
        widget_videoCtrl->setObjectName(QStringLiteral("widget_videoCtrl"));
        widget_videoCtrl->setGeometry(QRect(495, 20, 236, 356));
        verticalSlider = new QSlider(widget_videoCtrl);
        verticalSlider->setObjectName(QStringLiteral("verticalSlider"));
        verticalSlider->setGeometry(QRect(105, 15, 29, 211));
        verticalSlider->setFocusPolicy(Qt::NoFocus);
        verticalSlider->setMaximum(128);
        verticalSlider->setValue(128);
        label_5 = new QLabel(widget_videoCtrl);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(70, 230, 96, 31));
        label_5->setAlignment(Qt::AlignCenter);
        toolButton_play = new QToolButton(widget_videoCtrl);
        toolButton_play->setObjectName(QStringLiteral("toolButton_play"));
        toolButton_play->setGeometry(QRect(95, 265, 55, 55));
        toolButton_play->setMinimumSize(QSize(0, 32));
        toolButton_play->setFocusPolicy(Qt::NoFocus);
        QIcon icon;
        icon.addFile(QStringLiteral(":/image/resource/play.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_play->setIcon(icon);
        toolButton_play->setIconSize(QSize(160, 160));
        toolButton_play->setAutoRaise(true);
        toolButton_last = new QToolButton(widget_videoCtrl);
        toolButton_last->setObjectName(QStringLiteral("toolButton_last"));
        toolButton_last->setGeometry(QRect(20, 265, 55, 55));
        toolButton_last->setMinimumSize(QSize(0, 32));
        toolButton_last->setFocusPolicy(Qt::NoFocus);
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/image/resource/last.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_last->setIcon(icon1);
        toolButton_last->setIconSize(QSize(160, 160));
        toolButton_last->setAutoRaise(true);
        toolButton_next = new QToolButton(widget_videoCtrl);
        toolButton_next->setObjectName(QStringLiteral("toolButton_next"));
        toolButton_next->setGeometry(QRect(170, 265, 55, 55));
        toolButton_next->setMinimumSize(QSize(0, 32));
        toolButton_next->setFocusPolicy(Qt::NoFocus);
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/image/resource/next.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_next->setIcon(icon2);
        toolButton_next->setIconSize(QSize(160, 160));
        toolButton_next->setAutoRaise(true);
        widget_3 = new QWidget(tabWidgetPage4);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        widget_3->setGeometry(QRect(35, 70, 381, 266));
        pushButton_download = new QPushButton(widget_3);
        pushButton_download->setObjectName(QStringLiteral("pushButton_download"));
        pushButton_download->setGeometry(QRect(250, 190, 92, 34));
        pushButton_download->setMinimumSize(QSize(0, 32));
        pushButton_download->setFocusPolicy(Qt::NoFocus);
        groupBox = new QGroupBox(widget_3);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(35, 35, 301, 106));
        pushButton_openPort = new QPushButton(groupBox);
        pushButton_openPort->setObjectName(QStringLiteral("pushButton_openPort"));
        pushButton_openPort->setGeometry(QRect(200, 45, 71, 32));
        pushButton_openPort->setMinimumSize(QSize(0, 32));
        pushButton_openPort->setFocusPolicy(Qt::NoFocus);
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 67, 17));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 35, 67, 17));
        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(75, 30, 96, 27));
        comboBox_2 = new QComboBox(groupBox);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(75, 65, 96, 27));
        toolButton_show = new QToolButton(widget_3);
        toolButton_show->setObjectName(QStringLiteral("toolButton_show"));
        toolButton_show->setGeometry(QRect(45, 185, 71, 41));
        toolButton_show->setFocusPolicy(Qt::NoFocus);
        toolButton_test = new QToolButton(widget_3);
        toolButton_test->setObjectName(QStringLiteral("toolButton_test"));
        toolButton_test->setGeometry(QRect(150, 185, 71, 41));
        toolButton_test->setFocusPolicy(Qt::NoFocus);
        tabWidget->addTab(tabWidgetPage4, QString());
        widget_3->raise();
        widget_videoCtrl->raise();
        tabWidgetPage5 = new QWidget();
        tabWidgetPage5->setObjectName(QStringLiteral("tabWidgetPage5"));
        widget = new QWidget(tabWidgetPage5);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(50, 25, 691, 376));
        toolButton_right = new QToolButton(widget);
        toolButton_right->setObjectName(QStringLiteral("toolButton_right"));
        toolButton_right->setGeometry(QRect(280, 130, 100, 100));
        toolButton_right->setFont(font);
        toolButton_right->setFocusPolicy(Qt::NoFocus);
        toolButton_left = new QToolButton(widget);
        toolButton_left->setObjectName(QStringLiteral("toolButton_left"));
        toolButton_left->setGeometry(QRect(20, 130, 100, 100));
        toolButton_left->setFont(font);
        toolButton_left->setFocusPolicy(Qt::NoFocus);
        toolButton_stop = new QToolButton(widget);
        toolButton_stop->setObjectName(QStringLiteral("toolButton_stop"));
        toolButton_stop->setGeometry(QRect(150, 130, 100, 100));
        toolButton_stop->setFont(font);
        toolButton_stop->setFocusPolicy(Qt::NoFocus);
        toolButton_up = new QToolButton(widget);
        toolButton_up->setObjectName(QStringLiteral("toolButton_up"));
        toolButton_up->setGeometry(QRect(150, 5, 100, 100));
        toolButton_up->setFont(font);
        toolButton_up->setFocusPolicy(Qt::NoFocus);
        toolButton_down = new QToolButton(widget);
        toolButton_down->setObjectName(QStringLiteral("toolButton_down"));
        toolButton_down->setGeometry(QRect(150, 255, 100, 100));
        toolButton_down->setFont(font);
        toolButton_down->setFocusPolicy(Qt::NoFocus);
        toolButton_headup = new QToolButton(widget);
        toolButton_headup->setObjectName(QStringLiteral("toolButton_headup"));
        toolButton_headup->setGeometry(QRect(550, 45, 100, 100));
        toolButton_headup->setFont(font);
        toolButton_headup->setFocusPolicy(Qt::NoFocus);
        toolButton_headdown = new QToolButton(widget);
        toolButton_headdown->setObjectName(QStringLiteral("toolButton_headdown"));
        toolButton_headdown->setGeometry(QRect(550, 225, 100, 100));
        toolButton_headdown->setFont(font);
        toolButton_headdown->setFocusPolicy(Qt::NoFocus);
        toolButton_charge = new QToolButton(tabWidgetPage5);
        toolButton_charge->setObjectName(QStringLiteral("toolButton_charge"));
        toolButton_charge->setGeometry(QRect(470, 305, 70, 90));
        toolButton_charge->setFocusPolicy(Qt::NoFocus);
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/image/resource/battery_charging.png"), QSize(), QIcon::Normal, QIcon::Off);
        toolButton_charge->setIcon(icon3);
        toolButton_charge->setIconSize(QSize(160, 160));
        toolButton_charge->setAutoRaise(true);
        tabWidget->addTab(tabWidgetPage5, QString());
        MainWindow->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        label_3->setText(QString());
        label->setText(QApplication::translate("MainWindow", " \345\256\211\345\276\275\345\267\245\344\270\232\345\244\247\345\255\246 \347\224\265\346\260\224\344\270\216\344\277\241\346\201\257\345\267\245\347\250\213\345\255\246\351\231\242", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage1), QApplication::translate("MainWindow", " Main ", 0));
        pushButton_scan->setText(QApplication::translate("MainWindow", "scan", 0));
        pushButton_connect->setText(QApplication::translate("MainWindow", "connect", 0));
        pushButton_openssdb->setText(QApplication::translate("MainWindow", "open SSDB", 0));
        pushButton_disconnect->setText(QApplication::translate("MainWindow", "disconnect", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage2), QApplication::translate("MainWindow", "NetWork", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage3), QApplication::translate("MainWindow", "IP Info", 0));
        label_5->setText(QApplication::translate("MainWindow", "Volume", 0));
        toolButton_last->setText(QString());
        toolButton_next->setText(QString());
        pushButton_download->setText(QApplication::translate("MainWindow", "Download", 0));
        groupBox->setTitle(QApplication::translate("MainWindow", "SerialPort", 0));
        pushButton_openPort->setText(QApplication::translate("MainWindow", "open", 0));
        label_2->setText(QApplication::translate("MainWindow", "Baud:", 0));
        label_4->setText(QApplication::translate("MainWindow", "Port:", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "9600", 0)
         << QApplication::translate("MainWindow", "19200", 0)
         << QApplication::translate("MainWindow", "38400", 0)
         << QApplication::translate("MainWindow", "57600", 0)
         << QApplication::translate("MainWindow", "115200", 0)
         << QApplication::translate("MainWindow", "230400", 0)
        );
        toolButton_show->setText(QApplication::translate("MainWindow", "show", 0));
        toolButton_test->setText(QApplication::translate("MainWindow", "test", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage4), QApplication::translate("MainWindow", "Control", 0));
        toolButton_right->setText(QApplication::translate("MainWindow", ">", 0));
        toolButton_left->setText(QApplication::translate("MainWindow", "<", 0));
        toolButton_stop->setText(QApplication::translate("MainWindow", "+", 0));
        toolButton_up->setText(QApplication::translate("MainWindow", "^", 0));
        toolButton_down->setText(QApplication::translate("MainWindow", "v", 0));
        toolButton_headup->setText(QApplication::translate("MainWindow", "^", 0));
        toolButton_headdown->setText(QApplication::translate("MainWindow", "v", 0));
        tabWidget->setTabText(tabWidget->indexOf(tabWidgetPage5), QApplication::translate("MainWindow", "Robot Control", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
