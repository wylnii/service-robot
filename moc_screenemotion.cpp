/****************************************************************************
** Meta object code from reading C++ file 'screenemotion.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "screenemotion/screenemotion.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenemotion.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScreenEmotion_t {
    QByteArrayData data[13];
    char stringdata0[114];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenEmotion_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenEmotion_t qt_meta_stringdata_ScreenEmotion = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ScreenEmotion"
QT_MOC_LITERAL(1, 14, 13), // "changeWindows"
QT_MOC_LITERAL(2, 28, 0), // ""
QT_MOC_LITERAL(3, 29, 2), // "en"
QT_MOC_LITERAL(4, 32, 13), // "changeEmotion"
QT_MOC_LITERAL(5, 46, 7), // "Emotion"
QT_MOC_LITERAL(6, 54, 7), // "emotion"
QT_MOC_LITERAL(7, 62, 10), // "startMovie"
QT_MOC_LITERAL(8, 73, 9), // "stopMovie"
QT_MOC_LITERAL(9, 83, 4), // "show"
QT_MOC_LITERAL(10, 88, 4), // "hide"
QT_MOC_LITERAL(11, 93, 6), // "exHide"
QT_MOC_LITERAL(12, 100, 13) // "autoChangeEmt"

    },
    "ScreenEmotion\0changeWindows\0\0en\0"
    "changeEmotion\0Emotion\0emotion\0startMovie\0"
    "stopMovie\0show\0hide\0exHide\0autoChangeEmt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenEmotion[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       1,    0,   62,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   63,    2, 0x0a /* Public */,
       7,    0,   66,    2, 0x0a /* Public */,
       8,    0,   67,    2, 0x0a /* Public */,
       9,    0,   68,    2, 0x0a /* Public */,
      10,    0,   69,    2, 0x0a /* Public */,
      11,    0,   70,    2, 0x0a /* Public */,
      12,    0,   71,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ScreenEmotion::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenEmotion *_t = static_cast<ScreenEmotion *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeWindows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeWindows(); break;
        case 2: _t->changeEmotion((*reinterpret_cast< Emotion(*)>(_a[1]))); break;
        case 3: _t->startMovie(); break;
        case 4: _t->stopMovie(); break;
        case 5: _t->show(); break;
        case 6: _t->hide(); break;
        case 7: _t->exHide(); break;
        case 8: _t->autoChangeEmt(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenEmotion::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenEmotion::changeWindows)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ScreenEmotion::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ScreenEmotion.data,
      qt_meta_data_ScreenEmotion,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScreenEmotion::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenEmotion::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenEmotion.stringdata0))
        return static_cast<void*>(const_cast< ScreenEmotion*>(this));
    return QLabel::qt_metacast(_clname);
}

int ScreenEmotion::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void ScreenEmotion::changeWindows(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
