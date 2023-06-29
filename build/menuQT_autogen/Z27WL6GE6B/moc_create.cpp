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
    QByteArrayData data[25];
    char stringdata0[287];
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
QT_MOC_LITERAL(4, 33, 11), // "emitTypeMap"
QT_MOC_LITERAL(5, 45, 7), // "typeMap"
QT_MOC_LITERAL(6, 53, 18), // "startButtonClicked"
QT_MOC_LITERAL(7, 72, 10), // "closeEvent"
QT_MOC_LITERAL(8, 83, 12), // "QCloseEvent*"
QT_MOC_LITERAL(9, 96, 5), // "event"
QT_MOC_LITERAL(10, 102, 13), // "sliderChanged"
QT_MOC_LITERAL(11, 116, 5), // "value"
QT_MOC_LITERAL(12, 122, 23), // "handlerInfoGameReceived"
QT_MOC_LITERAL(13, 146, 15), // "messageInfoGame"
QT_MOC_LITERAL(14, 162, 12), // "handleClosed"
QT_MOC_LITERAL(15, 175, 14), // "handlerTypeMap"
QT_MOC_LITERAL(16, 190, 18), // "typeWeaponToString"
QT_MOC_LITERAL(17, 209, 11), // "std::string"
QT_MOC_LITERAL(18, 221, 12), // "TypeWeapon_t"
QT_MOC_LITERAL(19, 234, 4), // "type"
QT_MOC_LITERAL(20, 239, 11), // "getImageMap"
QT_MOC_LITERAL(21, 251, 8), // "QString&"
QT_MOC_LITERAL(22, 260, 3), // "map"
QT_MOC_LITERAL(23, 264, 15), // "getImageSoldier"
QT_MOC_LITERAL(24, 280, 6) // "weapon"

    },
    "Create\0closedWithError\0\0exitCode\0"
    "emitTypeMap\0typeMap\0startButtonClicked\0"
    "closeEvent\0QCloseEvent*\0event\0"
    "sliderChanged\0value\0handlerInfoGameReceived\0"
    "messageInfoGame\0handleClosed\0"
    "handlerTypeMap\0typeWeaponToString\0"
    "std::string\0TypeWeapon_t\0type\0getImageMap\0"
    "QString&\0map\0getImageSoldier\0weapon"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Create[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   75,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      12,    1,   82,    2, 0x08 /* Private */,
      14,    1,   85,    2, 0x08 /* Private */,
      15,    1,   88,    2, 0x08 /* Private */,
      16,    1,   91,    2, 0x08 /* Private */,
      20,    1,   94,    2, 0x08 /* Private */,
      23,    1,   97,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, QMetaType::Int,   11,
    QMetaType::Void, QMetaType::QString,   13,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    0x80000000 | 17, 0x80000000 | 18,   19,
    0x80000000 | 17, 0x80000000 | 21,   22,
    0x80000000 | 17, 0x80000000 | 21,   24,

       0        // eod
};

void Create::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Create *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->closedWithError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->emitTypeMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->startButtonClicked(); break;
        case 3: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 4: _t->sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 5: _t->handlerInfoGameReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->handleClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->handlerTypeMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: { std::string _r = _t->typeWeaponToString((*reinterpret_cast< TypeWeapon_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 9: { std::string _r = _t->getImageMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 10: { std::string _r = _t->getImageSoldier((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
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
        {
            using _t = void (Create::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Create::emitTypeMap)) {
                *result = 1;
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
void Create::closedWithError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Create::emitTypeMap(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
