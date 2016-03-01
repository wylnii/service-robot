/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[59];
    char stringdata0[973];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 11), // "connect_net"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 4), // "ssid"
QT_MOC_LITERAL(4, 29, 5), // "state"
QT_MOC_LITERAL(5, 35, 8), // "passcode"
QT_MOC_LITERAL(6, 44, 8), // "stop_net"
QT_MOC_LITERAL(7, 53, 14), // "openSerialPort"
QT_MOC_LITERAL(8, 68, 8), // "portname"
QT_MOC_LITERAL(9, 77, 8), // "baudRate"
QT_MOC_LITERAL(10, 86, 5), // "close"
QT_MOC_LITERAL(11, 92, 9), // "robotMove"
QT_MOC_LITERAL(12, 102, 20), // "SerialPort::MoveFlag"
QT_MOC_LITERAL(13, 123, 4), // "move"
QT_MOC_LITERAL(14, 128, 11), // "connectSSDB"
QT_MOC_LITERAL(15, 140, 7), // "sendCmd"
QT_MOC_LITERAL(16, 148, 3), // "cmd"
QT_MOC_LITERAL(17, 152, 4), // "show"
QT_MOC_LITERAL(18, 157, 26), // "on_pushButton_scan_clicked"
QT_MOC_LITERAL(19, 184, 29), // "on_pushButton_connect_clicked"
QT_MOC_LITERAL(20, 214, 32), // "on_pushButton_disconnect_clicked"
QT_MOC_LITERAL(21, 247, 26), // "on_toolButton_test_clicked"
QT_MOC_LITERAL(22, 274, 26), // "on_toolButton_play_clicked"
QT_MOC_LITERAL(23, 301, 24), // "on_toolButton_up_clicked"
QT_MOC_LITERAL(24, 326, 26), // "on_toolButton_down_clicked"
QT_MOC_LITERAL(25, 353, 26), // "on_toolButton_left_clicked"
QT_MOC_LITERAL(26, 380, 27), // "on_toolButton_right_clicked"
QT_MOC_LITERAL(27, 408, 26), // "on_toolButton_stop_clicked"
QT_MOC_LITERAL(28, 435, 30), // "on_pushButton_openPort_clicked"
QT_MOC_LITERAL(29, 466, 26), // "on_tabWidget_tabBarClicked"
QT_MOC_LITERAL(30, 493, 5), // "index"
QT_MOC_LITERAL(31, 499, 30), // "on_pushButton_openssdb_clicked"
QT_MOC_LITERAL(32, 530, 28), // "on_toolButton_headup_clicked"
QT_MOC_LITERAL(33, 559, 30), // "on_toolButton_headdown_clicked"
QT_MOC_LITERAL(34, 590, 30), // "on_pushButton_download_clicked"
QT_MOC_LITERAL(35, 621, 26), // "on_toolButton_show_clicked"
QT_MOC_LITERAL(36, 648, 28), // "on_toolButton_charge_clicked"
QT_MOC_LITERAL(37, 677, 30), // "on_verticalSlider_valueChanged"
QT_MOC_LITERAL(38, 708, 5), // "value"
QT_MOC_LITERAL(39, 714, 26), // "on_toolButton_last_clicked"
QT_MOC_LITERAL(40, 741, 26), // "on_toolButton_next_clicked"
QT_MOC_LITERAL(41, 768, 34), // "on_verticalSlider_2_sliderRel..."
QT_MOC_LITERAL(42, 803, 11), // "autoConnect"
QT_MOC_LITERAL(43, 815, 11), // "setStatText"
QT_MOC_LITERAL(44, 827, 4), // "text"
QT_MOC_LITERAL(45, 832, 16), // "setStatusBarText"
QT_MOC_LITERAL(46, 849, 4), // "type"
QT_MOC_LITERAL(47, 854, 10), // "rcvKBInput"
QT_MOC_LITERAL(48, 865, 5), // "input"
QT_MOC_LITERAL(49, 871, 3), // "mrk"
QT_MOC_LITERAL(50, 875, 13), // "handleRcvData"
QT_MOC_LITERAL(51, 889, 19), // "SerialPort::CtrlCmd"
QT_MOC_LITERAL(52, 909, 10), // "getCtrlMsg"
QT_MOC_LITERAL(53, 920, 12), // "SSDB_CtrlCmd"
QT_MOC_LITERAL(54, 933, 11), // "getKeyinput"
QT_MOC_LITERAL(55, 945, 3), // "key"
QT_MOC_LITERAL(56, 949, 6), // "status"
QT_MOC_LITERAL(57, 956, 13), // "changeWindows"
QT_MOC_LITERAL(58, 970, 2) // "en"

    },
    "MainWindow\0connect_net\0\0ssid\0state\0"
    "passcode\0stop_net\0openSerialPort\0"
    "portname\0baudRate\0close\0robotMove\0"
    "SerialPort::MoveFlag\0move\0connectSSDB\0"
    "sendCmd\0cmd\0show\0on_pushButton_scan_clicked\0"
    "on_pushButton_connect_clicked\0"
    "on_pushButton_disconnect_clicked\0"
    "on_toolButton_test_clicked\0"
    "on_toolButton_play_clicked\0"
    "on_toolButton_up_clicked\0"
    "on_toolButton_down_clicked\0"
    "on_toolButton_left_clicked\0"
    "on_toolButton_right_clicked\0"
    "on_toolButton_stop_clicked\0"
    "on_pushButton_openPort_clicked\0"
    "on_tabWidget_tabBarClicked\0index\0"
    "on_pushButton_openssdb_clicked\0"
    "on_toolButton_headup_clicked\0"
    "on_toolButton_headdown_clicked\0"
    "on_pushButton_download_clicked\0"
    "on_toolButton_show_clicked\0"
    "on_toolButton_charge_clicked\0"
    "on_verticalSlider_valueChanged\0value\0"
    "on_toolButton_last_clicked\0"
    "on_toolButton_next_clicked\0"
    "on_verticalSlider_2_sliderReleased\0"
    "autoConnect\0setStatText\0text\0"
    "setStatusBarText\0type\0rcvKBInput\0input\0"
    "mrk\0handleRcvData\0SerialPort::CtrlCmd\0"
    "getCtrlMsg\0SSDB_CtrlCmd\0getKeyinput\0"
    "key\0status\0changeWindows\0en"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      40,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       7,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,  214,    2, 0x06 /* Public */,
       6,    0,  221,    2, 0x06 /* Public */,
       7,    3,  222,    2, 0x06 /* Public */,
       7,    2,  229,    2, 0x26 /* Public | MethodCloned */,
      11,    1,  234,    2, 0x06 /* Public */,
      14,    0,  237,    2, 0x06 /* Public */,
      15,    1,  238,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    0,  241,    2, 0x0a /* Public */,
      18,    0,  242,    2, 0x0a /* Public */,
      19,    0,  243,    2, 0x0a /* Public */,
      20,    0,  244,    2, 0x0a /* Public */,
      21,    0,  245,    2, 0x0a /* Public */,
      22,    0,  246,    2, 0x0a /* Public */,
      23,    0,  247,    2, 0x0a /* Public */,
      24,    0,  248,    2, 0x0a /* Public */,
      25,    0,  249,    2, 0x0a /* Public */,
      26,    0,  250,    2, 0x0a /* Public */,
      27,    0,  251,    2, 0x0a /* Public */,
      28,    0,  252,    2, 0x0a /* Public */,
      29,    1,  253,    2, 0x0a /* Public */,
      31,    0,  256,    2, 0x0a /* Public */,
      32,    0,  257,    2, 0x0a /* Public */,
      33,    0,  258,    2, 0x0a /* Public */,
      34,    0,  259,    2, 0x0a /* Public */,
      35,    0,  260,    2, 0x0a /* Public */,
      36,    0,  261,    2, 0x0a /* Public */,
      37,    1,  262,    2, 0x0a /* Public */,
      39,    0,  265,    2, 0x0a /* Public */,
      40,    0,  266,    2, 0x0a /* Public */,
      41,    0,  267,    2, 0x0a /* Public */,
      42,    0,  268,    2, 0x08 /* Private */,
      43,    1,  269,    2, 0x08 /* Private */,
      45,    2,  272,    2, 0x08 /* Private */,
      45,    1,  277,    2, 0x28 /* Private | MethodCloned */,
      47,    2,  280,    2, 0x08 /* Private */,
      50,    1,  285,    2, 0x08 /* Private */,
      52,    1,  288,    2, 0x08 /* Private */,
      54,    2,  291,    2, 0x08 /* Private */,
      57,    1,  296,    2, 0x08 /* Private */,
      57,    0,  299,    2, 0x28 /* Private | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString,    3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    8,    9,   10,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    8,    9,
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,   16,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   30,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   38,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,   44,   46,
    QMetaType::Void, QMetaType::QString,   44,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   48,   49,
    QMetaType::Void, 0x80000000 | 51,   16,
    QMetaType::Void, 0x80000000 | 53,   16,
    QMetaType::Void, QMetaType::UChar, QMetaType::Bool,   55,   56,
    QMetaType::Void, QMetaType::Bool,   58,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->connect_net((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->stop_net(); break;
        case 2: _t->openSerialPort((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3]))); break;
        case 3: _t->openSerialPort((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2]))); break;
        case 4: _t->robotMove((*reinterpret_cast< SerialPort::MoveFlag(*)>(_a[1]))); break;
        case 5: _t->connectSSDB(); break;
        case 6: _t->sendCmd((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 7: _t->show(); break;
        case 8: _t->on_pushButton_scan_clicked(); break;
        case 9: _t->on_pushButton_connect_clicked(); break;
        case 10: _t->on_pushButton_disconnect_clicked(); break;
        case 11: _t->on_toolButton_test_clicked(); break;
        case 12: _t->on_toolButton_play_clicked(); break;
        case 13: _t->on_toolButton_up_clicked(); break;
        case 14: _t->on_toolButton_down_clicked(); break;
        case 15: _t->on_toolButton_left_clicked(); break;
        case 16: _t->on_toolButton_right_clicked(); break;
        case 17: _t->on_toolButton_stop_clicked(); break;
        case 18: _t->on_pushButton_openPort_clicked(); break;
        case 19: _t->on_tabWidget_tabBarClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 20: _t->on_pushButton_openssdb_clicked(); break;
        case 21: _t->on_toolButton_headup_clicked(); break;
        case 22: _t->on_toolButton_headdown_clicked(); break;
        case 23: _t->on_pushButton_download_clicked(); break;
        case 24: _t->on_toolButton_show_clicked(); break;
        case 25: _t->on_toolButton_charge_clicked(); break;
        case 26: _t->on_verticalSlider_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 27: _t->on_toolButton_last_clicked(); break;
        case 28: _t->on_toolButton_next_clicked(); break;
        case 29: _t->on_verticalSlider_2_sliderReleased(); break;
        case 30: _t->autoConnect(); break;
        case 31: _t->setStatText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 32: _t->setStatusBarText((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 33: _t->setStatusBarText((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 34: _t->rcvKBInput((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 35: _t->handleRcvData((*reinterpret_cast< const SerialPort::CtrlCmd(*)>(_a[1]))); break;
        case 36: _t->getCtrlMsg((*reinterpret_cast< const SSDB_CtrlCmd(*)>(_a[1]))); break;
        case 37: _t->getKeyinput((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 38: _t->changeWindows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 39: _t->changeWindows(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(QString , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connect_net)) {
                *result = 0;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::stop_net)) {
                *result = 1;
            }
        }
        {
            typedef void (MainWindow::*_t)(const QString & , const int & , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::openSerialPort)) {
                *result = 2;
            }
        }
        {
            typedef void (MainWindow::*_t)(SerialPort::MoveFlag );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::robotMove)) {
                *result = 4;
            }
        }
        {
            typedef void (MainWindow::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::connectSSDB)) {
                *result = 5;
            }
        }
        {
            typedef void (MainWindow::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::sendCmd)) {
                *result = 6;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 40)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 40;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 40)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 40;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::connect_net(QString _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::stop_net()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void MainWindow::openSerialPort(const QString & _t1, const int & _t2, bool _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 4
void MainWindow::robotMove(SerialPort::MoveFlag _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void MainWindow::connectSSDB()
{
    QMetaObject::activate(this, &staticMetaObject, 5, Q_NULLPTR);
}

// SIGNAL 6
void MainWindow::sendCmd(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}
QT_END_MOC_NAMESPACE
