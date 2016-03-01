/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serialport/serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SerialPort_t {
    QByteArrayData data[20];
    char stringdata0[173];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPort_t qt_meta_stringdata_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialPort"
QT_MOC_LITERAL(1, 11, 6), // "errMsg"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 7), // "rcvData"
QT_MOC_LITERAL(4, 27, 19), // "SerialPort::CtrlCmd"
QT_MOC_LITERAL(5, 47, 3), // "cmd"
QT_MOC_LITERAL(6, 51, 8), // "openPort"
QT_MOC_LITERAL(7, 60, 8), // "portname"
QT_MOC_LITERAL(8, 69, 8), // "baudRate"
QT_MOC_LITERAL(9, 78, 5), // "close"
QT_MOC_LITERAL(10, 84, 4), // "move"
QT_MOC_LITERAL(11, 89, 8), // "MoveFlag"
QT_MOC_LITERAL(12, 98, 6), // "motion"
QT_MOC_LITERAL(13, 105, 7), // "readCom"
QT_MOC_LITERAL(14, 113, 7), // "getData"
QT_MOC_LITERAL(15, 121, 10), // "getCtrlMsg"
QT_MOC_LITERAL(16, 132, 12), // "SSDB_CtrlCmd"
QT_MOC_LITERAL(17, 145, 7), // "sendCMD"
QT_MOC_LITERAL(18, 153, 12), // "const uchar*"
QT_MOC_LITERAL(19, 166, 6) // "length"

    },
    "SerialPort\0errMsg\0\0rcvData\0"
    "SerialPort::CtrlCmd\0cmd\0openPort\0"
    "portname\0baudRate\0close\0move\0MoveFlag\0"
    "motion\0readCom\0getData\0getCtrlMsg\0"
    "SSDB_CtrlCmd\0sendCMD\0const uchar*\0"
    "length"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   74,    2, 0x06 /* Public */,
       1,    1,   79,    2, 0x26 /* Public | MethodCloned */,
       3,    1,   82,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    3,   85,    2, 0x0a /* Public */,
       6,    2,   92,    2, 0x2a /* Public | MethodCloned */,
      10,    1,   97,    2, 0x0a /* Public */,
      13,    0,  100,    2, 0x0a /* Public */,
      14,    0,  101,    2, 0x0a /* Public */,
      15,    1,  102,    2, 0x0a /* Public */,
      17,    1,  105,    2, 0x0a /* Public */,
      17,    2,  108,    2, 0x0a /* Public */,
      17,    1,  113,    2, 0x2a /* Public | MethodCloned */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, 0x80000000 | 4,    5,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int, QMetaType::Bool,    7,    8,    9,
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,    5,
    QMetaType::Void, QMetaType::QByteArray,    5,
    QMetaType::Void, 0x80000000 | 18, QMetaType::Int,    5,   19,
    QMetaType::Void, 0x80000000 | 18,    5,

       0        // eod
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialPort *_t = static_cast<SerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->rcvData((*reinterpret_cast< SerialPort::CtrlCmd(*)>(_a[1]))); break;
        case 3: { bool _r = _t->openPort((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->openPort((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->move((*reinterpret_cast< MoveFlag(*)>(_a[1]))); break;
        case 6: _t->readCom(); break;
        case 7: _t->getData(); break;
        case 8: _t->getCtrlMsg((*reinterpret_cast< const SSDB_CtrlCmd(*)>(_a[1]))); break;
        case 9: _t->sendCMD((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 10: _t->sendCMD((*reinterpret_cast< const uchar*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 11: _t->sendCMD((*reinterpret_cast< const uchar*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SerialPort::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::errMsg)) {
                *result = 0;
            }
        }
        {
            typedef void (SerialPort::*_t)(SerialPort::CtrlCmd );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::rcvData)) {
                *result = 2;
            }
        }
    }
}

const QMetaObject SerialPort::staticMetaObject = {
    { &QSerialPort::staticMetaObject, qt_meta_stringdata_SerialPort.data,
      qt_meta_data_SerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort.stringdata0))
        return static_cast<void*>(const_cast< SerialPort*>(this));
    return QSerialPort::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QSerialPort::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void SerialPort::errMsg(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 2
void SerialPort::rcvData(SerialPort::CtrlCmd _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_END_MOC_NAMESPACE
