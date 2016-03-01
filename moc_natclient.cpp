/****************************************************************************
** Meta object code from reading C++ file 'natclient.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "net/natclient.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'natclient.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_NatClient_t {
    QByteArrayData data[26];
    char stringdata0[238];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NatClient_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NatClient_t qt_meta_stringdata_NatClient = {
    {
QT_MOC_LITERAL(0, 0, 9), // "NatClient"
QT_MOC_LITERAL(1, 10, 8), // "errorMsg"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 1), // "e"
QT_MOC_LITERAL(4, 22, 9), // "reciveMsg"
QT_MOC_LITERAL(5, 32, 1), // "m"
QT_MOC_LITERAL(6, 34, 11), // "receiveData"
QT_MOC_LITERAL(7, 46, 12), // "processLogin"
QT_MOC_LITERAL(8, 59, 4), // "data"
QT_MOC_LITERAL(9, 64, 16), // "processP2PmsgREQ"
QT_MOC_LITERAL(10, 81, 12), // "QHostAddress"
QT_MOC_LITERAL(11, 94, 4), // "addr"
QT_MOC_LITERAL(12, 99, 4), // "port"
QT_MOC_LITERAL(13, 104, 22), // "processSomeWantCallYou"
QT_MOC_LITERAL(14, 127, 5), // "login"
QT_MOC_LITERAL(15, 133, 6), // "logout"
QT_MOC_LITERAL(16, 140, 5), // "force"
QT_MOC_LITERAL(17, 146, 8), // "sendData"
QT_MOC_LITERAL(18, 155, 16), // "processOnlineAck"
QT_MOC_LITERAL(19, 172, 10), // "onineCheck"
QT_MOC_LITERAL(20, 183, 11), // "setServerIP"
QT_MOC_LITERAL(21, 195, 2), // "ip"
QT_MOC_LITERAL(22, 198, 13), // "setServerPort"
QT_MOC_LITERAL(23, 212, 4), // "WORD"
QT_MOC_LITERAL(24, 217, 15), // "setLocalNatName"
QT_MOC_LITERAL(25, 233, 4) // "name"

    },
    "NatClient\0errorMsg\0\0e\0reciveMsg\0m\0"
    "receiveData\0processLogin\0data\0"
    "processP2PmsgREQ\0QHostAddress\0addr\0"
    "port\0processSomeWantCallYou\0login\0"
    "logout\0force\0sendData\0processOnlineAck\0"
    "onineCheck\0setServerIP\0ip\0setServerPort\0"
    "WORD\0setLocalNatName\0name"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NatClient[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       4,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   95,    2, 0x0a /* Public */,
       7,    1,   96,    2, 0x0a /* Public */,
       9,    3,   99,    2, 0x0a /* Public */,
      13,    1,  106,    2, 0x0a /* Public */,
      14,    0,  109,    2, 0x0a /* Public */,
      15,    1,  110,    2, 0x0a /* Public */,
      15,    0,  113,    2, 0x2a /* Public | MethodCloned */,
      17,    1,  114,    2, 0x0a /* Public */,
      18,    0,  117,    2, 0x0a /* Public */,
      19,    0,  118,    2, 0x0a /* Public */,
      20,    1,  119,    2, 0x0a /* Public */,
      22,    1,  122,    2, 0x0a /* Public */,
      24,    1,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QByteArray,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 10, QMetaType::UShort,    8,   11,   12,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   21,
    QMetaType::Void, 0x80000000 | 23,   12,
    QMetaType::Void, QMetaType::QByteArray,   25,

       0        // eod
};

void NatClient::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        NatClient *_t = static_cast<NatClient *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errorMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->reciveMsg((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->receiveData(); break;
        case 3: _t->processLogin((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->processP2PmsgREQ((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])),(*reinterpret_cast< const quint16(*)>(_a[3]))); break;
        case 5: _t->processSomeWantCallYou((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 6: _t->login(); break;
        case 7: _t->logout((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->logout(); break;
        case 9: _t->sendData((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 10: _t->processOnlineAck(); break;
        case 11: _t->onineCheck(); break;
        case 12: _t->setServerIP((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 13: _t->setServerPort((*reinterpret_cast< WORD(*)>(_a[1]))); break;
        case 14: _t->setLocalNatName((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (NatClient::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NatClient::errorMsg)) {
                *result = 0;
            }
        }
        {
            typedef void (NatClient::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&NatClient::reciveMsg)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject NatClient::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_NatClient.data,
      qt_meta_data_NatClient,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *NatClient::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NatClient::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_NatClient.stringdata0))
        return static_cast<void*>(const_cast< NatClient*>(this));
    return QObject::qt_metacast(_clname);
}

int NatClient::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void NatClient::errorMsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NatClient::reciveMsg(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
