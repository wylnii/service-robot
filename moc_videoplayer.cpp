/****************************************************************************
** Meta object code from reading C++ file 'videoplayer.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "videoplayer/videoplayer.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'videoplayer.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_VideoPlayer_t {
    QByteArrayData data[22];
    char stringdata0[140];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VideoPlayer_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VideoPlayer_t qt_meta_stringdata_VideoPlayer = {
    {
QT_MOC_LITERAL(0, 0, 11), // "VideoPlayer"
QT_MOC_LITERAL(1, 12, 7), // "playEnd"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 9), // "returnMsg"
QT_MOC_LITERAL(4, 31, 4), // "list"
QT_MOC_LITERAL(5, 36, 4), // "type"
QT_MOC_LITERAL(6, 41, 4), // "play"
QT_MOC_LITERAL(7, 46, 4), // "file"
QT_MOC_LITERAL(8, 51, 2), // "no"
QT_MOC_LITERAL(9, 54, 7), // "silence"
QT_MOC_LITERAL(10, 62, 1), // "s"
QT_MOC_LITERAL(11, 64, 6), // "replay"
QT_MOC_LITERAL(12, 71, 5), // "pause"
QT_MOC_LITERAL(13, 77, 4), // "stop"
QT_MOC_LITERAL(14, 82, 7), // "repaint"
QT_MOC_LITERAL(15, 90, 8), // "playNext"
QT_MOC_LITERAL(16, 99, 1), // "n"
QT_MOC_LITERAL(17, 101, 8), // "playLast"
QT_MOC_LITERAL(18, 110, 1), // "l"
QT_MOC_LITERAL(19, 112, 10), // "getCtrlMsg"
QT_MOC_LITERAL(20, 123, 12), // "SSDB_CtrlCmd"
QT_MOC_LITERAL(21, 136, 3) // "cmd"

    },
    "VideoPlayer\0playEnd\0\0returnMsg\0list\0"
    "type\0play\0file\0no\0silence\0s\0replay\0"
    "pause\0stop\0repaint\0playNext\0n\0playLast\0"
    "l\0getCtrlMsg\0SSDB_CtrlCmd\0cmd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VideoPlayer[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      16,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   94,    2, 0x06 /* Public */,
       3,    2,   95,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,  100,    2, 0x0a /* Public */,
       6,    1,  101,    2, 0x0a /* Public */,
       6,    1,  104,    2, 0x0a /* Public */,
       9,    1,  107,    2, 0x0a /* Public */,
       9,    0,  110,    2, 0x2a /* Public | MethodCloned */,
      11,    0,  111,    2, 0x0a /* Public */,
      12,    0,  112,    2, 0x0a /* Public */,
      13,    1,  113,    2, 0x0a /* Public */,
      13,    0,  116,    2, 0x2a /* Public | MethodCloned */,
      15,    1,  117,    2, 0x0a /* Public */,
      15,    0,  120,    2, 0x2a /* Public | MethodCloned */,
      17,    1,  121,    2, 0x0a /* Public */,
      17,    0,  124,    2, 0x2a /* Public | MethodCloned */,
      19,    1,  125,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    4,    5,

 // slots: parameters
    QMetaType::Int,
    QMetaType::Int, QMetaType::QString,    7,
    QMetaType::Int, QMetaType::Int,    8,
    QMetaType::Void, QMetaType::Bool,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   14,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   16,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   18,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 20,   21,

       0        // eod
};

void VideoPlayer::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        VideoPlayer *_t = static_cast<VideoPlayer *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->playEnd(); break;
        case 1: _t->returnMsg((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: { int _r = _t->play();
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 3: { int _r = _t->play((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 4: { int _r = _t->play((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 5: _t->silence((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 6: _t->silence(); break;
        case 7: _t->replay(); break;
        case 8: _t->pause(); break;
        case 9: _t->stop((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 10: _t->stop(); break;
        case 11: _t->playNext((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 12: _t->playNext(); break;
        case 13: _t->playLast((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 14: _t->playLast(); break;
        case 15: _t->getCtrlMsg((*reinterpret_cast< const SSDB_CtrlCmd(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (VideoPlayer::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoPlayer::playEnd)) {
                *result = 0;
            }
        }
        {
            typedef void (VideoPlayer::*_t)(const QString & , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&VideoPlayer::returnMsg)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject VideoPlayer::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_VideoPlayer.data,
      qt_meta_data_VideoPlayer,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *VideoPlayer::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VideoPlayer::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_VideoPlayer.stringdata0))
        return static_cast<void*>(const_cast< VideoPlayer*>(this));
    return QThread::qt_metacast(_clname);
}

int VideoPlayer::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 16)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 16;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 16)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 16;
    }
    return _id;
}

// SIGNAL 0
void VideoPlayer::playEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void VideoPlayer::returnMsg(const QString & _t1, int _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
