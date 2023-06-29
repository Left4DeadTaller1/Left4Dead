/****************************************************************************
** Meta object code from reading C++ file 'create.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client/menuQT/create.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'create.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Create_t {
    QByteArrayData data[14];
    char stringdata0[150];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Create_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Create_t qt_meta_stringdata_Create = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Create"
QT_MOC_LITERAL(1, 7, 15), // "closedWithError"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 8), // "exitCode"
QT_MOC_LITERAL(4, 33, 18), // "startButtonClicked"
QT_MOC_LITERAL(5, 52, 10), // "closeEvent"
QT_MOC_LITERAL(6, 63, 12), // "QCloseEvent*"
QT_MOC_LITERAL(7, 76, 5), // "event"
QT_MOC_LITERAL(8, 82, 13), // "sliderChanged"
QT_MOC_LITERAL(9, 96, 5), // "value"
QT_MOC_LITERAL(10, 102, 18), // "handleJoinReceived"
QT_MOC_LITERAL(11, 121, 8), // "nickname"
QT_MOC_LITERAL(12, 130, 6), // "weapon"
QT_MOC_LITERAL(13, 137, 12) // "handleClosed"

    },
    "Create\0closedWithError\0\0exitCode\0"
    "startButtonClicked\0closeEvent\0"
    "QCloseEvent*\0event\0sliderChanged\0value\0"
    "handleJoinReceived\0nickname\0weapon\0"
    "handleClosed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Create[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   47,    2, 0x08 /* Private */,
       5,    1,   48,    2, 0x08 /* Private */,
       8,    1,   51,    2, 0x08 /* Private */,
      10,    2,   54,    2, 0x08 /* Private */,
      13,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::Int,    9,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,   11,   12,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void Create::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Create *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->closedWithError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->startButtonClicked(); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->handleJoinReceived((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->handleClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Create::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Create::closedWithError)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Create::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Create.data,
    qt_meta_data_Create,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Create::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Create::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Create.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Create::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void Create::closedWithError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
