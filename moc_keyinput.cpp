/****************************************************************************
** Meta object code from reading C++ file 'keyinput.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "keyinput.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'keyinput.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_KeyInput_t {
    QByteArrayData data[8];
    char stringdata0[59];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_KeyInput_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_KeyInput_t qt_meta_stringdata_KeyInput = {
    {
QT_MOC_LITERAL(0, 0, 8), // "KeyInput"
QT_MOC_LITERAL(1, 9, 10), // "keyChanged"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 6), // "status"
QT_MOC_LITERAL(4, 28, 10), // "keyPressed"
QT_MOC_LITERAL(5, 39, 3), // "key"
QT_MOC_LITERAL(6, 43, 8), // "readData"
QT_MOC_LITERAL(7, 52, 6) // "socket"

    },
    "KeyInput\0keyChanged\0\0status\0keyPressed\0"
    "key\0readData\0socket"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_KeyInput[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    2,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   37,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::UChar, QMetaType::Bool,    5,    3,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void KeyInput::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        KeyInput *_t = static_cast<KeyInput *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->keyChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->keyPressed((*reinterpret_cast< uchar(*)>(_a[1])),(*reinterpret_cast< bool(*)>(_a[2]))); break;
        case 2: _t->readData((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (KeyInput::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyInput::keyChanged)) {
                *result = 0;
            }
        }
        {
            typedef void (KeyInput::*_t)(uchar , bool );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&KeyInput::keyPressed)) {
                *result = 1;
            }
        }
    }
}

const QMetaObject KeyInput::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_KeyInput.data,
      qt_meta_data_KeyInput,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *KeyInput::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *KeyInput::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_KeyInput.stringdata0))
        return static_cast<void*>(const_cast< KeyInput*>(this));
    return QObject::qt_metacast(_clname);
}

int KeyInput::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void KeyInput::keyChanged(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void KeyInput::keyPressed(uchar _t1, bool _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
