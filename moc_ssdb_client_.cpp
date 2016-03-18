/****************************************************************************
** Meta object code from reading C++ file 'ssdb_client_.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "SSDB/ssdb_client_.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ssdb_client_.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SSDB_Client_t {
    QByteArrayData data[18];
    char stringdata0[171];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SSDB_Client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SSDB_Client_t qt_meta_stringdata_SSDB_Client = {
    {
QT_MOC_LITERAL(0, 0, 11), // "SSDB_Client"
QT_MOC_LITERAL(1, 12, 7), // "CtrlMsg"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 12), // "SSDB_CtrlCmd"
QT_MOC_LITERAL(4, 34, 6), // "errMsg"
QT_MOC_LITERAL(5, 41, 13), // "connectServer"
QT_MOC_LITERAL(6, 55, 4), // "host"
QT_MOC_LITERAL(7, 60, 4), // "port"
QT_MOC_LITERAL(8, 65, 8), // "ticktack"
QT_MOC_LITERAL(9, 74, 12), // "queryDirCtrl"
QT_MOC_LITERAL(10, 87, 11), // "rcvVideoMsg"
QT_MOC_LITERAL(11, 99, 4), // "list"
QT_MOC_LITERAL(12, 104, 4), // "type"
QT_MOC_LITERAL(13, 109, 14), // "queryVideoCtrl"
QT_MOC_LITERAL(14, 124, 13), // "sendVideoInfo"
QT_MOC_LITERAL(15, 138, 8), // "getSPMsg"
QT_MOC_LITERAL(16, 147, 19), // "SerialPort::CtrlCmd"
QT_MOC_LITERAL(17, 167, 3) // "cmd"

    },
    "SSDB_Client\0CtrlMsg\0\0SSDB_CtrlCmd\0"
    "errMsg\0connectServer\0host\0port\0ticktack\0"
    "queryDirCtrl\0rcvVideoMsg\0list\0type\0"
    "queryVideoCtrl\0sendVideoInfo\0getSPMsg\0"
    "SerialPort::CtrlCmd\0cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SSDB_Client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    2,   72,    2, 0x06 /* Public */,
       4,    1,   77,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       5,    2,   80,    2, 0x0a /* Public */,
       5,    0,   85,    2, 0x0a /* Public */,
       8,    0,   86,    2, 0x0a /* Public */,
       9,    0,   87,    2, 0x0a /* Public */,
      10,    2,   88,    2, 0x0a /* Public */,
      13,    0,   93,    2, 0x0a /* Public */,
      14,    0,   94,    2, 0x0a /* Public */,
      15,    1,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Bool, QMetaType::QString, QMetaType::Int,    6,    7,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,   11,   12,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 16,   17,

       0        // eod
};

void SSDB_Client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SSDB_Client *_t = static_cast<SSDB_Client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CtrlMsg((*reinterpret_cast< SSDB_CtrlCmd(*)>(_a[1]))); break;
        case 1: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: { bool _r = _t->connectServer((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->connectServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 5: _t->ticktack(); break;
        case 6: _t->queryDirCtrl(); break;
        case 7: _t->rcvVideoMsg((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 8: _t->queryVideoCtrl(); break;
        case 9: _t->sendVideoInfo(); break;
        case 10: _t->getSPMsg((*reinterpret_cast< const SerialPort::CtrlCmd(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SSDB_Client::*_t)(SSDB_CtrlCmd );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SSDB_Client::CtrlMsg)) {
                *result = 0;
            }
        }
        {
            typedef void (SSDB_Client::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SSDB_Client::errMsg)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject SSDB_Client::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_SSDB_Client.data,
      qt_meta_data_SSDB_Client,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SSDB_Client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SSDB_Client::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SSDB_Client.stringdata0))
        return static_cast<void*>(const_cast< SSDB_Client*>(this));
    return QThread::qt_metacast(_clname);
}

int SSDB_Client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void SSDB_Client::CtrlMsg(SSDB_CtrlCmd _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void SSDB_Client::errMsg(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
