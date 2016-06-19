#include "mainwindow.h"
#ifdef HD_SCREEN
#include "ui_mainwindow.h"
#else
#include "ui_mainwindow800*480.h"
#endif
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
#ifdef HD_SCREEN
    ui->label_title->hide();
    ui->label_logo->hide();
#endif
    QRect screenrect = QApplication::desktop()->screenGeometry();

    move((screenrect.width() - WINDOW_WIDTH)/2, 0);

    RobotName = loadHistory("RobotName");
//    centralWidget()->setMouseTracking(1);
//    setMouseTracking(1);

    qDebug()<<"main thread:"<<QThread::currentThread();
//    setWindowFlags(Qt::WindowStaysOnTopHint);

    status_label=new QLabel(this);//程序状态显示

    statusBar()->addPermanentWidget(status_label);
    statusBar()->setStyleSheet(QString("QStatusBar::item{border: 0px}"));//去除没显示时的短线

    wifi_thread=new QThread(this);//wifi线程
    wifi_thread->start();

    serialport_thread = new QThread(this);
    serialport_thread->start();

    wifi=new USB_WiFi;//不能指定为this，要不然无法用moveToThread
    connect(wifi,&USB_WiFi::errormsg,this,&MainWindow::setStatText);
    connect(this,&MainWindow::connect_net,wifi,&USB_WiFi::connect_wifi);
    connect(this,&MainWindow::stop_net,wifi,&USB_WiFi::stop_wifi);
    wifi->moveToThread(wifi_thread);

#ifdef _TEST1
    if(! USB_WiFi::WiFi_exist())
    {
        setStatText("<font color='red'>Can't find any wlan device!</font>");
        QMessageBox::warning(this,"Warning","<font color='red'>Can't find any wlan device!</font><p>Please check your hardware!</p>"\
                            ,tr("\t\t&O&k\t\t"),tr("\t\tCancle\t\t"));
    }
#endif
    QTimer::singleShot(1500,Qt::VeryCoarseTimer,this,&MainWindow::autoConnect);//auto connect

    wifitable=new QTableWidget(ui->tabWidgetPage2);

#ifdef HD_SCREEN
    ipInfoTable=new IPInfoTable(ui->tabWidgetPage3,950,720);
    wifitable->setFixedSize(950,700);
    int wifitable_fixedsize = 60;
#else
    ipInfoTable=new IPInfoTable(ui->tabWidgetPage3,480,426);
    wifitable->setFixedSize(480,426);
    int wifitable_fixedsize = 40;
#endif

    //    wifitable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    wifitable->verticalHeader()->setDefaultSectionSize(wifitable_fixedsize); //设置行距
    wifitable->verticalHeader()->setFixedWidth(wifitable_fixedsize);
    wifitable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    wifitable->setColumnCount(3);
    wifitable->move(2,0);
    wifitable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wifitable->setSelectionBehavior(QAbstractItemView::SelectRows);
    wifitable->setAlternatingRowColors(true);
//    wifitable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
//    wifitable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    wifitable->horizontalHeader()->setFixedHeight(wifitable_fixedsize);
    wifitable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mykeyboard=new Keyboard(this);
    mykeyboard->hide();
    connect(mykeyboard,SIGNAL(enter(QString,QString)),this,SLOT(rcvKBInput(QString,QString)));

    videoPlayer = new VideoPlayer(NULL, this);
    connect(videoPlayer, &VideoPlayer::changeWindows, this, &MainWindow::changeWindows);
    setStatusBarText((videoPlayer->getPlaylist().join(", ").prepend("playList: ")),1);

    emotionPlayer = new EmotionPlayer(NULL, videoPlayer);//TODO

    ui->verticalSlider->setValue(videoPlayer->Volume());

    serialport = new SerialPort();
    serialport->moveToThread(serialport_thread);
    ui->comboBox->addItems(serialport->scanAvailablePorts());
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    ui->comboBox_2->setCurrentText(loadHistory("SerialPort_Baudrate",DEFAULT_BAUD));

    connect(serialport,&SerialPort::errMsg,this,&MainWindow::setStatusBarText);
    connect(serialport,&SerialPort::rcvSPData,this,&MainWindow::getSPMsg);
    connect(this, &MainWindow::openSerialPort, serialport, &SerialPort::openPort);
    connect(this, &MainWindow::robotMove, serialport, &SerialPort::move);
    connect(this, &MainWindow::sendCmd, serialport, static_cast<void (SerialPort::*)(const QByteArray &)>(&SerialPort::sendCMD));
    emit openSerialPort(loadHistory("SerialPort_Num","ttySAC3"),loadHistory("SerialPort_Baudrate",DEFAULT_BAUD).toInt());
    ssdbClient = new SSDB_Client(this,RobotName);
//    ssdbClient->moveToThread(serialport_thread);//TODO multi-thread
//    ssdbClient->setClientName(RobotName);
    ssdbClient->setServerAddr(loadHistory("SSDB_server"));
    ssdbClient->setServerPort(loadHistory("SSDB_port").toInt());

    connect(ssdbClient,&SSDB_Client::errMsg,this,&MainWindow::setStatusBarText);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, this, &MainWindow::getCtrlMsg);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, serialport, &SerialPort::getCtrlMsg);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, videoPlayer, &VideoPlayer::getCtrlMsg);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, emotionPlayer, &EmotionPlayer::getCtrlMsg);
    connect(videoPlayer, &VideoPlayer::returnMsg, ssdbClient, &SSDB_Client::rcvVideoMsg);
    connect(serialport,&SerialPort::rcvSPData,ssdbClient,&SSDB_Client::getSPMsg);
    connect(this, &MainWindow::connectSSDB, ssdbClient, static_cast<bool (SSDB_Client::*)()>(&SSDB_Client::connectServer));

//    netSpeed = new NetSpeed();
    networkQualityThread = new NetworkQualityThread(this);
    connect(networkQualityThread, &NetworkQualityThread::updateNetworkQuality, ssdbClient, &SSDB_Client::getNetworkQuality);
    networkQualityThread->start();

    keyInput = new KeyInput(this);
    connect(keyInput, &KeyInput::keyPressed, this, &MainWindow::getKeyinput);

    setStyleSheet();
}

MainWindow::~MainWindow()
{
    wifi_thread->quit();
    serialport_thread->quit();
//    videoPlayer->stop();
    wifi_thread->quit();
    serialport_thread->quit();
    thread()->msleep(100);
    delete videoPlayer;
    delete wifi;
    delete ssdbClient;
    delete serialport;
    delete emotionPlayer;
    delete keyInput;
    qDebug()<<"exit";
    delete ui;
}

void MainWindow::setBacklightBright(uchar bright)
{
    char cmd[50];
    sprintf(cmd, "echo %d > /dev/backlight-1wire", bright);
    system(cmd);
}

void MainWindow::setStyleSheet()
{
    QString stylesheet = "QPushButton::enabled{border:2px outset gray;border-radius:4px;}"
                  "QPushButton::disabled{border:2px outset gray;border-radius:4px;}"
                  "QPushButton::pressed{border-color:#a0a0a0;border:3px groove ;background-color:#d0d0d0;}"
                  "QPushButton::checked{background-color:#000000;border:5px groove green;}"
                  "QPushButton::hover{border-color:#606060;/*background-color:#d0d0d0;*/}"
                  ;
    stylesheet +="QToolButton::enabled{border:2px outset gray;border-radius:5px;padding:0px 0px;}"
                  "QToolButton::pressed{border-color:#a0a0a0;border:3px groove ;background-color:#d0d0d0;}"
                  "QToolButton::checked{background-color:#000000;border:5px groove green;}"
                  "QToolButton::hover{border-color:#606060;/*background-color:#d0d0d0;*/}" ;
   stylesheet += "QComboBox {"
                 "border: 1px solid gray;"
                 "border-radius: 3px;"
                 "padding: 1px 1px 1px 3px;"
                 "}";
   ui->widget->setStyleSheet(stylesheet);
   ui->toolButton_charge->setStyleSheet("QToolButton{border:0px outset gray;border-radius:5px;padding:0px 0px;}");
   ui->widget_3->setStyleSheet(stylesheet);
   ui->widget_4->setStyleSheet(stylesheet);

   QString tabBarStyle = "QTabBar::tab {min-width:90px;"
                         "background-color: #f2f1f0;"
                         "border: 1px solid #c2c7cb;"
                         "border-top-left-radius: 6px;"
                         "border-top-right-radius: 6px;"
                         "padding:8px;}"
                         "QTabWidget::pane{border-width:1px;border-color: #306880; border-top: 1px solid #A2A7FB;}"
                         "QTabBar::tab:!selected {margin-top: 6px;} "
                         "QTabBar::tab:selected {color: rgb(37, 138, 198);font:18dp }";

    ui->tabWidget->setStyleSheet(tabBarStyle);

    QString sliderStyle = "QSlider  {"
                          "background-color: #00000000;"
                          "min-width:5px;"
                          "max-width:50px;"
                          "/*border:15px solid #00000000;*/"
                          "}"
                          "QSlider::add-page:vertical { "
                          "background-color: rgb(37, 168, 198);"
                          "width:4px;"
                          "border-radius: 4px;"
                          "}"
                          "QSlider::sub-page:vertical {"
                          "background-color: rgb(87, 97, 106);"
                          "width:4px;"
                          "border-radius: 4px;"
                          "}"
                          "QSlider::groove:vertical  {"
                          "background:transparent;"
                          "width:8px;"
                          "border-radius: 4px;"
                          "}"
                          "QSlider::handle:vertical {"
                          "height: 16px;"
                          "width: 16px;"
                          "border-image: url(:/image/resource/point.png);"
                          "margin: -0 -4px; "
                          "}";
    ui->verticalSlider->setStyleSheet(sliderStyle);
    ui->verticalSlider_2->setStyleSheet(sliderStyle);
}

void MainWindow::show()
{
#ifndef _TEST
    emotionPlayer->changeEmotion("connect");
//    QMainWindow::show();//TODO
//    screenEmotion->show();
#else
    QMainWindow::show();
#endif
}

void MainWindow::setStatText(const QString &text)
{
    static int statusBar_height = statusBar()->height();
    status_label->setText(text);
    qDebug()<<text;
    repaint(0,SCREEN_HEIGHT-statusBar_height,SCREEN_WIDTH,statusBar_height);
}

void MainWindow::setStatusBarText(const QString &text, bool type)
{
    if(type)
    {
        statusBar()->showMessage(text,8000);
        qDebug()<<text;
    }
    else
        setStatText(text);
}

void MainWindow::on_pushButton_scan_clicked()
{
    ui->pushButton_scan->setDisabled(1);
    QList<QStringList> list;
#ifdef _TEST
    QStringList header;
    header<<"SSID"<<"Intensity"<<"state";
    list.append(header);
    QStringList header1;
    header1<<"openwifi"<<"100%"<<"open";
    list.append(header1);
    QStringList header2;
    header2<<"lockedwifi"<<"100%"<<"locked";
    list.append(header2);
    QStringList header3;
    header3<<"<hidden>"<<"80%"<<"locked";
    list.append(header3);
#else
    if(wifi->connetct_ssid.isEmpty())
        list=wifi->scan_wifi(0);
    else
        list=wifi->scan_wifi(1);
#endif
//    wifitable->clear();
    wifitable->setRowCount(0);
    wifitable->setHorizontalHeaderLabels(list.at(0));

    for (int i=1;i<list.count();i++)
    {
        QString SSID=list.at(i).at(0);
        QString Intensity=list.at(i).at(1);
        QString state=list.at(i).at(2);
        wifitable->insertRow(wifitable->rowCount());

        QTableWidgetItem *item1 = new QTableWidgetItem(SSID);
        item1->setTextAlignment(Qt::AlignCenter);
        wifitable->setItem(wifitable->rowCount()-1,0,item1);
        QTableWidgetItem *item2 = new QTableWidgetItem(Intensity);
        item2->setTextAlignment(Qt::AlignCenter);
        wifitable->setItem(wifitable->rowCount()-1,1,item2);
        QTableWidgetItem *item3 = new QTableWidgetItem(state);
        item3->setTextAlignment(Qt::AlignCenter);
        wifitable->setItem(wifitable->rowCount()-1,2,item3);
    }
    ui->pushButton_scan->setEnabled(true);
}

void MainWindow::autoConnect()
{
    if(! IPInfoTable::network_exist())
    {
        emotionPlayer->stop();
        setStatText("<font color='red'>找不到网络设备!</font>");
/*        int ret = QMessageBox::warning(this,"Warning","<font color='red'>找不到网络设备!</font><p>是否重启？</p>"\
//                            ,tr("\t\t确定\t\t"),tr("\t\t取消\t\t"));
//        if(ret == 0)
//        {*/
#ifndef _TEST
        system("reboot");
#endif
        return;
    }
    else if (USB_WiFi::WiFi_exist())
    {
        system("ifconfig eth0 down");//disable eth0
        bool success = wifi->connect_wifi(loadHistory("SSID"),loadHistory("STATE"),loadHistory("#WIFI_password"));
        if(success)
        {
            emotionPlayer->changeEmotion("service");
            emit connectSSDB();
            if(! ssdbClient->isConnected())
            {
                showSupportMsg();
            }
        }
        return;
    }

//启动时检查网络连接
    if(loadHistory("Check_Net_Connect",1).toInt() <= 0)
    {
        emotionPlayer->stop(true);
        return;
    }
    qDebug()<<"Check_Net_Connect...";
    if(IPInfoTable::checkNet())
    {
#ifndef _TEST
        emotionPlayer->changeEmotion("service");
#endif
        emit connectSSDB();
        QString cmd("./audioPlayer %1 %2 %3");
        cmd = cmd.arg(loadHistory("SSDB_server","60.171.108.155"),"20000",RobotName);
        qDebug()<<cmd;
        system(cmd.toLocal8Bit().constData());
        if(! ssdbClient->isConnected())
        {
            showSupportMsg();
        }
    }
    else    //检查网络连接失败，显示帮助界面
    {
        showSupportMsg();
    }
}

void MainWindow::on_pushButton_connect_clicked()
{
    int current=wifitable->currentRow();
    if(current>=0)
    {
        QString wifissid=wifitable->item(current,0)->text();
        QString wifistate=wifitable->item(current,2)->text();
        saveHistory(wifissid,"SSID");
        saveHistory(wifistate,"STATE");

        if(wifistate != "open")
        {
            mykeyboard->setInputMsg("Input Password :","#WIFI_password");
            mykeyboard->show();
        }
        else
        {
            emit connect_net(wifissid,wifistate,QString("0"));
        }
    }
}

void MainWindow::rcvKBInput(const QString &input, const QString &mrk)
{
    if(mrk == "#WIFI_password")
    {
        int current=wifitable->currentRow();
        if(current>=0)
        {
//            wifitable->setEnabled(false);
            QString wifissid=wifitable->item(current,0)->text();
            QString wifistate=wifitable->item(current,2)->text();
            if(wifistate != "open" && !input.isEmpty())
            {
                emit connect_net(wifissid,wifistate,input);
            }
//            wifitable->setEnabled(true);
        }
    }
    else if(mrk == "IP")
    {
        if(input.contains(QRegExp("^((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])$")))
        {
//            ffmpeg_run->ipAddr = input;

            mykeyboard->setInputMsg("Input Device :", "Device");
            mykeyboard->show();
        }
        else
        {
            setStatusBarText("eg :\t192.168.1.1",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "Device")
    {
        if(input.contains(QRegExp("^/dev/.+\\d+$")))
        {
//            ffmpeg_run->device = input;
            mykeyboard->setInputMsg("Input Feed :", "Feed");
            mykeyboard->show();
        }
        else
        {
            setStatusBarText("eg :\t/dev/video15",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "Feed")
    {
        if(input.contains(QRegExp("^[\\d\\w]+$")))
        {
//            ffmpeg_run->feed = input;
//            emit send_rtsp(ffmpeg_run->ipAddr,"",ffmpeg_run->feed,"640*480","15","256k",ffmpeg_run->device);
        }
        else
        {
            setStatusBarText("eg :\tarmcam1",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "NAT")
    {
        QRegExp regexp("^(((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5]))\\s?:\\s?([\\d]{1,5})$");
        if(regexp.indexIn(input) != -1)
        {
//            nat->setServerIP(regexp.cap(1));
//            nat->setServerPort(regexp.cap(5).toInt());
            mykeyboard->setInputMsg("Input NAT Name :", "RobotName");
            mykeyboard->show();
        }
        else
        {
            setStatusBarText("eg :\t192.168.1.1:1234",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "RobotName")
    {
        if(input.length() > 3)
        {
            ssdbClient->setClientName(input);
            emit connectSSDB();
        }
        else
        {
            setStatusBarText("eg :\tRobot427",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "SSDB_server")
    {
        QRegExp regexp("^(((\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5])\\.){3}(\\d{1,2}|1\\d\\d|2[0-4]\\d|25[0-5]))$");
        if(regexp.indexIn(input) != -1)
        {
            ssdbClient->setServerAddr(input);
            mykeyboard->setInputMsg("SSDB Server Port :","SSDB_port");
            mykeyboard->show();
        }
        else
        {
            setStatusBarText("eg :\t192.168.1.117",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "SSDB_port")
    {
        QRegExp regexp("([\\d]{2,5})$");
        if(regexp.indexIn(input) != -1)
        {
            ssdbClient->setServerPort(input.toInt());
            mykeyboard->setInputMsg("SSDB Client Name :","RobotName");
            mykeyboard->show();
        }
        else
        {
            setStatusBarText("eg :\t8888",1);
            mykeyboard->show();
        }
    }
    else if(mrk == "Unlock_password")
    {
        if(! (input == loadHistory("Unlock_password")))
        {
            mykeyboard->show();
        }
    }
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    emit stop_net();
}

void MainWindow::on_toolButton_up_clicked()
{
    emit robotMove(SerialPort::Up);
}

void MainWindow::on_toolButton_down_clicked()
{
    emit robotMove(SerialPort::Down);
}

void MainWindow::on_toolButton_left_clicked()
{
    emit robotMove(SerialPort::Left);
}

void MainWindow::on_toolButton_right_clicked()
{
    emit robotMove(SerialPort::Right);
}

void MainWindow::on_toolButton_stop_clicked()
{
    emit robotMove(SerialPort::Stop);
}

void MainWindow::on_pushButton_openPort_clicked()
{
    emit openSerialPort(ui->comboBox->currentText(),ui->comboBox_2->currentText().toInt(), serialport->isOpen());
    saveHistory(ui->comboBox->currentText(),"SerialPort_Num");
    saveHistory(ui->comboBox_2->currentText().toInt(),"SerialPort_Baudrate");
}

void MainWindow::getSPMsg(const SerialPort::CtrlCmd &cmd)
{
    setStatText(QString("type: 0x%1 data: %2").arg(cmd.type, 0, 16).arg(cmd.data, 8, 2, QChar('0')));
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
    {
        ipInfoTable->showIPInfo();
    }
}

void MainWindow::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    qDebug()<<"MainWidow get:"<<cmd.msg<<"type:"<<cmd.type<<"dir:"<<cmd.dirCtrl<<"video:"<<cmd.videoCtrl;
}

void MainWindow::getKeyinput(uchar key, bool status)
{
    if(status)
    {
        setStatText(QString("key %1 : %2").arg(key).arg(status? "pressed":"released"));
        switch (key)
        {
        case 1:
            emotionPlayer->playEmotion();
            break;
        case 2:
            QMainWindow::show();
            break;
        case 3:
            on_toolButton_play_clicked();
            break;
        case 4:
            qApp->exit();
            break;
        default:
            break;
        }
    }
}

void MainWindow::changeWindows()
{
    QMainWindow::show();
    mykeyboard->setInputMsg("Unlock Password :","Unlock_password",false);
    mykeyboard->show();
}

void MainWindow::showSupportMsg()
{
    this->hide();
    emotionPlayer->stop();
    Label &l = videoPlayer->getLabel();
    l.setPixmap(QPixmap(":/image/resource/support.jpg"));
    l.activateWindow();
}

void MainWindow::on_pushButton_openssdb_clicked()
{
    if(ssdbClient->isConnected())
    {
        ssdbClient->disConnect();
    }
    else
    {
        mykeyboard->setInputMsg("SSDB Server Addr :","SSDB_server");
        mykeyboard->show();
    }
}

void MainWindow::on_toolButton_headup_clicked()
{
    emit robotMove(SerialPort::HeadUp);
}

void MainWindow::on_toolButton_headdown_clicked()
{
    emit robotMove(SerialPort::HeadDown);
}

void MainWindow::on_toolButton_headleft_clicked()
{
    emit robotMove(SerialPort::HeadLeft);
}

void MainWindow::on_toolButton_headright_clicked()
{
    emit robotMove(SerialPort::HeadRight);
}

void MainWindow::on_pushButton_download_clicked()
{
    Downloader *downloader = new Downloader(this);

    if(! downloader->isDownloading())
    {
        downloader->startDownload("\
http://mirrors.ustc.edu.cn/qtproject/official_releases/gdb/linux-32/md5sums.txt\
");
    }
    else
        downloader->stopDownload();
}

void MainWindow::on_toolButton_show_clicked()
{
    emotionPlayer->changeEmotion("service");
//    emotionPlayer->show();
}

void MainWindow::on_toolButton_charge_clicked()
{
    emit robotMove(SerialPort::Charge);
}

void MainWindow::on_toolButton_test_clicked()
{
    QFile file("test");
    file.open(QFile::ReadOnly);
    QByteArray cmd = file.readAll();
    file.close();
    QList<QByteArray> list = cmd.split(' ');
    qDebug()<<cmd;
    cmd.clear();
    foreach (QByteArray ch, list)
    {
        cmd.append(QByteArray::fromHex(ch));
    }
    emit sendCmd(cmd);
}

void MainWindow::on_toolButton_play_clicked()
{
    if(! videoPlayer->IsPlaying())
    {
        videoPlayer->play();
    }
    else
    {
        videoPlayer->stop(true);
    }
}

void MainWindow::on_verticalSlider_valueChanged(int value)
{
    videoPlayer->setVolume(value);
}

void MainWindow::on_toolButton_last_clicked()
{
    videoPlayer->playLast();
}

void MainWindow::on_toolButton_next_clicked()
{
    videoPlayer->playNext();
}

void MainWindow::on_verticalSlider_2_sliderReleased()
{
#ifndef _TEST
    setBacklightBright(ui->verticalSlider_2->value());
#endif
}
