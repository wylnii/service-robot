/****************************************************************************
** Meta object code from reading C++ file 'usb_wifi.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "net/usb_wifi.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'usb_wifi.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_USB_WiFi_t {
    QByteArrayData data[14];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_USB_WiFi_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_USB_WiFi_t qt_meta_stringdata_USB_WiFi = {
    {
QT_MOC_LITERAL(0, 0, 8), // "USB_WiFi"
QT_MOC_LITERAL(1, 9, 8), // "errormsg"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 9), // "scan_wifi"
QT_MOC_LITERAL(4, 29, 18), // "QList<QStringList>"
QT_MOC_LITERAL(5, 48, 6), // "update"
QT_MOC_LITERAL(6, 55, 12), // "connect_wifi"
QT_MOC_LITERAL(7, 68, 4), // "ssid"
QT_MOC_LITERAL(8, 73, 5), // "state"
QT_MOC_LITERAL(9, 79, 8), // "passcode"
QT_MOC_LITERAL(10, 88, 16), // "connect_wifi_by_"
QT_MOC_LITERAL(11, 105, 3), // "cmd"
QT_MOC_LITERAL(12, 109, 4), // "type"
QT_MOC_LITERAL(13, 114, 9) // "stop_wifi"

    },
    "USB_WiFi\0errormsg\0\0scan_wifi\0"
    "QList<QStringList>\0update\0connect_wifi\0"
    "ssid\0state\0passcode\0connect_wifi_by_\0"
    "cmd\0type\0stop_wifi"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_USB_WiFi[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   42,    2, 0x0a /* Public */,
       6,    3,   45,    2, 0x0a /* Public */,
      10,    3,   52,    2, 0x0a /* Public */,
      13,    0,   59,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    0x80000000 | 4, QMetaType::Int,    5,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Bool, QMetaType::QString, QMetaType::QString, QMetaType::QString,   11,    7,   12,
    QMetaType::Bool,

       0        // eod
};

void USB_WiFi::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        USB_WiFi *_t = static_cast<USB_WiFi *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->errormsg((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: { QList<QStringList> _r = _t->scan_wifi((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<QStringList>*>(_a[0]) = _r; }  break;
        case 2: { bool _r = _t->connect_wifi((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 3: { bool _r = _t->connect_wifi_by_((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3])));
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        case 4: { bool _r = _t->stop_wifi();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = _r; }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (USB_WiFi::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&USB_WiFi::errormsg)) {
                *result = 0;
            }
        }
    }
}

const QMetaObject USB_WiFi::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_USB_WiFi.data,
      qt_meta_data_USB_WiFi,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *USB_WiFi::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *USB_WiFi::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_USB_WiFi.stringdata0))
        return static_cast<void*>(const_cast< USB_WiFi*>(this));
    return QObject::qt_metacast(_clname);
}

int USB_WiFi::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
void USB_WiFi::errormsg(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
