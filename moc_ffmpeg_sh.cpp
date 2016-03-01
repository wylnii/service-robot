/****************************************************************************
** Meta object code from reading C++ file 'ffmpeg_sh.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "ffmpeg/ffmpeg_sh.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ffmpeg_sh.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ffmpeg_sh_t {
    QByteArrayData data[14];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ffmpeg_sh_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ffmpeg_sh_t qt_meta_stringdata_ffmpeg_sh = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ffmpeg_sh"
QT_MOC_LITERAL(1, 10, 6), // "errMsg"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 4), // "type"
QT_MOC_LITERAL(4, 23, 9), // "rtsp_send"
QT_MOC_LITERAL(5, 33, 7), // "rtsp_ip"
QT_MOC_LITERAL(6, 41, 4), // "port"
QT_MOC_LITERAL(7, 46, 4), // "feed"
QT_MOC_LITERAL(8, 51, 10), // "Resolution"
QT_MOC_LITERAL(9, 62, 3), // "fps"
QT_MOC_LITERAL(10, 66, 7), // "bitrate"
QT_MOC_LITERAL(11, 74, 6), // "device"
QT_MOC_LITERAL(12, 81, 11), // "stopProcess"
QT_MOC_LITERAL(13, 93, 7) // "readMsg"

    },
    "ffmpeg_sh\0errMsg\0\0type\0rtsp_send\0"
    "rtsp_ip\0port\0feed\0Resolution\0fps\0"
    "bitrate\0device\0stopProcess\0readMsg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ffmpeg_sh[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   39,    2, 0x06 /* Public */,
       1,    1,   44,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       4,    7,   47,    2, 0x0a /* Public */,
      12,    0,   62,    2, 0x0a /* Public */,
      13,    0,   63,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Bool,    2,    3,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString, QMetaType::QString,    5,    6,    7,    8,    9,   10,   11,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ffmpeg_sh::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ffmpeg_sh *_t = static_cast<ffmpeg_sh *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 1: _t->errMsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->rtsp_send((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4])),(*reinterpret_cast< QString(*)>(_a[5])),(*reinterpret_cast< QString(*)>(_a[6])),(*reinterpret_cast< QString(*)>(_a[7]))); break;
        case 3: _t->stopProcess(); break;
        case 4: _t->readMsg(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ffmpeg_sh::*_t)(QString , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ffmpeg_sh::errMsg)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ffmpeg_sh::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ffmpeg_sh.data,
      qt_meta_data_ffmpeg_sh,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ffmpeg_sh::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ffmpeg_sh::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ffmpeg_sh.stringdata0))
        return static_cast<void*>(const_cast< ffmpeg_sh*>(this));
    return QObject::qt_metacast(_clname);
}

int ffmpeg_sh::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ffmpeg_sh::errMsg(QString _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
