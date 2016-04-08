#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QInputDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);
    ui->label_title->hide();
    ui->label_logo->hide();
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
    connect(wifi,SIGNAL(errormsg(QString)),this,SLOT(setStatText(QString)));
    connect(this,SIGNAL(connect_net(QString,QString,QString)),wifi,SLOT(connect_wifi(QString,QString,QString)));
    connect(this,SIGNAL(stop_net()),wifi,SLOT(stop_wifi()));
    wifi->moveToThread(wifi_thread);

#ifdef _TEST1
    if(! USB_WiFi::WiFi_exist())
    {
        setStatText("<font color='red'>Can't find any wlan device!</font>");
        QMessageBox::warning(this,"Warning","<font color='red'>Can't find any wlan device!</font><p>Please check your hardware!</p>"\
                            ,tr("\t\t&O&k\t\t"),tr("\t\tCancle\t\t"));
    }
#endif
    QTimer::singleShot(1000,Qt::VeryCoarseTimer,this,SLOT(autoConnect()));//auto connect

    ipInfoTable=new IPInfoTable(ui->tabWidgetPage3,950,720);
    ipInfoTable->setFontPointSize(20);

    wifitable=new QTableWidget(ui->tabWidgetPage2);
//    wifitable->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    wifitable->verticalHeader()->setDefaultSectionSize(60); //设置行距
    wifitable->verticalHeader()->setFixedWidth(60);
    wifitable->verticalHeader()->setDefaultAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    wifitable->setColumnCount(3);
//    wifitable->setColumnWidth(0,200);
//    wifitable->setColumnWidth(1,100);
//    wifitable->setColumnWidth(2,110);
    wifitable->setFixedSize(950,720);
    wifitable->move(2,0);
    wifitable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    wifitable->setSelectionBehavior(QAbstractItemView::SelectRows);
    wifitable->setAlternatingRowColors(true);
//    wifitable->horizontalHeader()->setSectionResizeMode(0,QHeaderView::Stretch);
//    wifitable->horizontalHeader()->setSectionResizeMode(1,QHeaderView::Stretch);
    wifitable->horizontalHeader()->setFixedHeight(60);
    wifitable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    mykeyboard=new Keyboard(this);
    mykeyboard->hide();
    connect(mykeyboard,SIGNAL(enter(QString,QString)),this,SLOT(rcvKBInput(QString,QString)));

    screenEmotion = new ScreenEmotion(0, this);
    connect(screenEmotion, &ScreenEmotion::changeWindows, this, &MainWindow::changeWindows);

    videoPlayer = new VideoPlayer(NULL, screenEmotion);
    QDir dir("./");
    QStringList filelist = dir.entryList(QStringList()<<"*.mkv"<<"*.mp4"<<"*.flv"<<"*.rm"<<"*.rmvb");
    dir.setPath("/video/");
    foreach(QString file, dir.entryList(QStringList()<<"*.mkv"<<"*.mp4"<<"*.flv"<<"*.rm"<<"*.rmvb"))
    {
        filelist<<file.prepend(dir.absolutePath().append('/'));
    }
    videoPlayer->setPlaylist(filelist);
    setStatusBarText((filelist.join(" & ").prepend("playList: ")),1);
    ui->verticalSlider->setValue(videoPlayer->Volume());

    serialport = new SerialPort;
    serialport->moveToThread(serialport_thread);
    ui->comboBox->addItems(serialport->scan_com());
    ui->comboBox->setCurrentIndex(ui->comboBox->count()-1);
    ui->comboBox_2->setCurrentText(QString::number(DEFAULT_BAUD));

    connect(serialport,&SerialPort::errMsg,this,&MainWindow::setStatusBarText);
    connect(serialport,&SerialPort::rcvSPData,this,&MainWindow::getSPMsg);
    connect(this, &MainWindow::openSerialPort, serialport, &SerialPort::openPort);
    connect(this, &MainWindow::robotMove, serialport, &SerialPort::move);
    connect(this, &MainWindow::sendCmd, serialport, static_cast<void (SerialPort::*)(const QByteArray &)>(&SerialPort::sendCMD));

    ssdbClient = new SSDB_Client(this,RobotName);
//    ssdbClient->moveToThread(serialport_thread);
//    ssdbClient->setClientName(RobotName);
    ssdbClient->setServerAddr(loadHistory("SSDB_server"));
    ssdbClient->setServerPort(loadHistory("SSDB_port").toInt());

    connect(ssdbClient,&SSDB_Client::errMsg,this,&MainWindow::setStatusBarText);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, this, &MainWindow::getCtrlMsg);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, serialport, &SerialPort::getCtrlMsg);
    connect(ssdbClient, &SSDB_Client::CtrlMsg, videoPlayer, &VideoPlayer::getCtrlMsg);
    connect(videoPlayer, &VideoPlayer::returnMsg, ssdbClient, &SSDB_Client::rcvVideoMsg);
    connect(serialport,&SerialPort::rcvSPData,ssdbClient,&SSDB_Client::getSPMsg);
    connect(this, SIGNAL(connectSSDB()), ssdbClient, SLOT(connectServer()));

//    netSpeed = new NetSpeed();

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
    delete screenEmotion;
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
    stylesheet +=("QToolButton::enabled{border:2px outset gray;border-radius:5px;padding:0px 0px;}"
                  "QToolButton::pressed{border-color:#a0a0a0;border:3px groove ;background-color:#d0d0d0;}"
                  "QToolButton::checked{background-color:#000000;border:5px groove green;}"
                  "QToolButton::hover{border-color:#606060;/*background-color:#d0d0d0;*/}") ;
   stylesheet += "QComboBox {"
                 "border: 1px solid gray;"
                 "border-radius: 3px;"
                 "padding: 1px 1px 1px 3px;"
                 "}";
   ui->widget->setStyleSheet(stylesheet);
   ui->widget_3->setStyleSheet(stylesheet);
   ui->widget_4->setStyleSheet(stylesheet);

   QString tabBarStyle = "QTabBar::tab {min-width:90px;\
           background-color: #f2f1f0;\
border: 1px solid #c2c7cb;\
   border-top-left-radius: 6px;\
   border-top-right-radius: 6px;\
padding:8px;}\
QTabWidget::pane{border-width:1px;border-color: #306880; border-top: 1px solid #A2A7FB;}\
QTabBar::tab:!selected {margin-top: 6px;} \
QTabBar::tab:selected {color: rgb(37, 138, 198);font:18px }";

  ui->tabWidget->setStyleSheet(tabBarStyle);

QString sliderStyle = "QSlider  {\
        background-color: #00000000;\
        min-width:5px;\
        max-width:50px;\
        /*border:15px solid #00000000;*/\
    }\
     QSlider::add-page:vertical { \
        background-color: rgb(37, 168, 198);\
        width:4px;\
     border-radius: 4px;\
     }\
     QSlider::sub-page:vertical {\
        background-color: rgb(87, 97, 106);\
        width:4px;\
     border-radius: 4px;\
     }\
    QSlider::groove:vertical  {\
        background:transparent;\
        width:8px;\
    border-radius: 4px;\
    }\
    QSlider::handle:vertical {\
         height: 16px;\
        width: 16px;\
        border-image: url(:/image/resource/point.png);\
         margin: -0 -4px; \
     }";
        ui->verticalSlider->setStyleSheet(sliderStyle);
        ui->verticalSlider_2->setStyleSheet(sliderStyle);
}

void MainWindow::show()
{
//    QMainWindow::show();
#ifndef _TEST
    screenEmotion->changeEmotion(ScreenEmotion::connecting);
    screenEmotion->show();
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
    ui->pushButton_scan->setEnabled(1);
}

void MainWindow::autoConnect()
{
    if(! IPInfoTable::eth0_exist())
    {
        screenEmotion->stopMovie();
        setStatText("<font color='red'>找不到网络设备!</font>");
        int ret = QMessageBox::warning(this,"Warning","<font color='red'>找不到网络设备!</font><p>是否重启？</p>"\
                            ,tr("\t\t确定\t\t"),tr("\t\t取消\t\t"));
        if(ret == 0)
        {
#ifndef _TEST
            system("reboot");
#endif
            return;
        }
    }
    else if (USB_WiFi::WiFi_exist())
    {
        if(! wifi->connect_wifi(loadHistory("SSID"),loadHistory("STATE"),loadHistory("#WIFI_password")))
            return;
    }

    QElapsedTimer timer;
    int cnt = 16;

    while (! IPInfoTable::hasValidIP() && cnt --)
    {
        timer.start();
        while(! timer.hasExpired(400))
        {
            qApp->processEvents();
        }
    }

    if(cnt < 0)
    {
        system("./restart_service &");
        qApp->exit();
    }

#ifndef _TEST
    screenEmotion->changeEmotion(ScreenEmotion::service);
#endif

    emit connectSSDB();
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
}

void MainWindow::getSPMsg(const SerialPort::CtrlCmd &cmd)
{
    setStatText(QString("type: %1 data: %2").arg(cmd.type, 0, 16).arg(cmd.data, 8, 2, QChar('0')));
}

void MainWindow::on_tabWidget_tabBarClicked(int index)
{
    if(index == 2)
        ipInfoTable->showIPInfo();
}

void MainWindow::getCtrlMsg(const SSDB_CtrlCmd &cmd)
{
    qDebug()<<"MainWidow get:"<<cmd.msg<<cmd.type<<cmd.dirCtrl<<cmd.videoCtrl;
    if(cmd.type == SSDB_CTRL_VideoCtrl)
    {
        switch (cmd.videoCtrl)
        {
        case Video_Play:
            screenEmotion->hide();
            break;
        case Video_Pause:
            if(videoPlayer->IsOpened())
                screenEmotion->show();
            break;
        case Video_ContinuePlay:
            if(videoPlayer->IsOpened())
                screenEmotion->hide();
            break;
        case Video_Stop:
            screenEmotion->show();
            break;
        case Video_PlayNext:
            screenEmotion->hide();
            break;
        case Video_PlayLast:
            screenEmotion->hide();
            break;
        case Video_SetPlayList:
            break;
        case Video_PlayList:
            break;
        case Video_Info:
            break;
        case Video_SetCyclePlay:
            screenEmotion->hide();
            break;
        case Video_SetSinglePlay:
            screenEmotion->hide();
            break;
        case Video_SetSingleCyclePlay:
            screenEmotion->hide();
            break;
        default:
            break;
        }
    }
}

void MainWindow::getKeyinput(uchar key, bool status)
{
    if(status)
    {
        setStatText(QString("key %1 : %2").arg(key).arg(status? "pressed":"released"));
        switch (key)
        {
        case 1:
            screenEmotion->show();
            break;
        case 2:
            screenEmotion->exHide();
            break;
        case 3:
            on_toolButton_play_clicked();
            break;
        case 4:
            break;
        default:
            break;
        }
    }
}

void MainWindow::changeWindows(bool en)
{
    if(en)
    {
        mykeyboard->setInputMsg("Unlock Password :","Unlock_password",false);
        mykeyboard->show();
    }
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
    screenEmotion->show();
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
