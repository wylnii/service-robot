/****************************************************************************
** Meta object code from reading C++ file 'screenface.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "screenface.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'screenface.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ScreenFace_t {
    QByteArrayData data[12];
    char stringdata0[104];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ScreenFace_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ScreenFace_t qt_meta_stringdata_ScreenFace = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ScreenFace"
QT_MOC_LITERAL(1, 11, 13), // "changeWindows"
QT_MOC_LITERAL(2, 25, 0), // ""
QT_MOC_LITERAL(3, 26, 2), // "en"
QT_MOC_LITERAL(4, 29, 13), // "changeEmotion"
QT_MOC_LITERAL(5, 43, 7), // "Emotion"
QT_MOC_LITERAL(6, 51, 7), // "emotion"
QT_MOC_LITERAL(7, 59, 10), // "startMovie"
QT_MOC_LITERAL(8, 70, 9), // "stopMovie"
QT_MOC_LITERAL(9, 80, 4), // "show"
QT_MOC_LITERAL(10, 85, 4), // "hide"
QT_MOC_LITERAL(11, 90, 13) // "autoChangeEmt"

    },
    "ScreenFace\0changeWindows\0\0en\0changeEmotion\0"
    "Emotion\0emotion\0startMovie\0stopMovie\0"
    "show\0hide\0autoChangeEmt"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ScreenFace[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       1,    0,   57,    2, 0x26 /* Public | MethodCloned */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   58,    2, 0x0a /* Public */,
       7,    0,   61,    2, 0x0a /* Public */,
       8,    0,   62,    2, 0x0a /* Public */,
       9,    0,   63,    2, 0x0a /* Public */,
      10,    0,   64,    2, 0x0a /* Public */,
      11,    0,   65,    2, 0x0a /* Public */,

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

       0        // eod
};

void ScreenFace::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ScreenFace *_t = static_cast<ScreenFace *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->changeWindows((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->changeWindows(); break;
        case 2: _t->changeEmotion((*reinterpret_cast< Emotion(*)>(_a[1]))); break;
        case 3: _t->startMovie(); break;
        case 4: _t->stopMovie(); break;
        case 5: _t->show(); break;
        case 6: _t->hide(); break;
        case 7: _t->autoChangeEmt(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ScreenFace::*_t)(bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ScreenFace::changeWindows)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject ScreenFace::staticMetaObject = {
    { &QLabel::staticMetaObject, qt_meta_stringdata_ScreenFace.data,
      qt_meta_data_ScreenFace,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ScreenFace::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ScreenFace::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ScreenFace.stringdata0))
        return static_cast<void*>(const_cast< ScreenFace*>(this));
    return QLabel::qt_metacast(_clname);
}

int ScreenFace::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QLabel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ScreenFace::changeWindows(bool _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
