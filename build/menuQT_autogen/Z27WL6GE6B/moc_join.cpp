/****************************************************************************
** Meta object code from reading C++ file 'join.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../client/menuQT/join.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'join.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Join_t {
    QByteArrayData data[22];
    char stringdata0[266];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Join_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Join_t qt_meta_stringdata_Join = {
    {
QT_MOC_LITERAL(0, 0, 4), // "Join"
QT_MOC_LITERAL(1, 5, 15), // "closedWithError"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 8), // "exitCode"
QT_MOC_LITERAL(4, 31, 11), // "emitTypeMap"
QT_MOC_LITERAL(5, 43, 7), // "typeMap"
QT_MOC_LITERAL(6, 51, 10), // "closeEvent"
QT_MOC_LITERAL(7, 62, 12), // "QCloseEvent*"
QT_MOC_LITERAL(8, 75, 5), // "event"
QT_MOC_LITERAL(9, 81, 13), // "sliderChanged"
QT_MOC_LITERAL(10, 95, 5), // "value"
QT_MOC_LITERAL(11, 101, 23), // "handlerInfoGameReceived"
QT_MOC_LITERAL(12, 125, 15), // "messageInfoGame"
QT_MOC_LITERAL(13, 141, 12), // "handleClosed"
QT_MOC_LITERAL(14, 154, 14), // "handlerTypeMap"
QT_MOC_LITERAL(15, 169, 18), // "typeWeaponToString"
QT_MOC_LITERAL(16, 188, 11), // "std::string"
QT_MOC_LITERAL(17, 200, 12), // "TypeWeapon_t"
QT_MOC_LITERAL(18, 213, 4), // "type"
QT_MOC_LITERAL(19, 218, 13), // "getTextureMap"
QT_MOC_LITERAL(20, 232, 21), // "getTextureIconSoldier"
QT_MOC_LITERAL(21, 254, 11) // "typeSoldier"

    },
    "Join\0closedWithError\0\0exitCode\0"
    "emitTypeMap\0typeMap\0closeEvent\0"
    "QCloseEvent*\0event\0sliderChanged\0value\0"
    "handlerInfoGameReceived\0messageInfoGame\0"
    "handleClosed\0handlerTypeMap\0"
    "typeWeaponToString\0std::string\0"
    "TypeWeapon_t\0type\0getTextureMap\0"
    "getTextureIconSoldier\0typeSoldier"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Join[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   70,    2, 0x08 /* Private */,
       9,    1,   73,    2, 0x08 /* Private */,
      11,    1,   76,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,
      14,    1,   82,    2, 0x08 /* Private */,
      15,    1,   85,    2, 0x08 /* Private */,
      19,    1,   88,    2, 0x08 /* Private */,
      20,    1,   91,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void, QMetaType::Int,   10,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString,    5,
    0x80000000 | 16, 0x80000000 | 17,   18,
    QMetaType::QPixmap, QMetaType::QString,    5,
    QMetaType::QPixmap, QMetaType::QString,   21,

       0        // eod
};

void Join::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Join *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->closedWithError((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->emitTypeMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->closeEvent((*reinterpret_cast< QCloseEvent*(*)>(_a[1]))); break;
        case 3: _t->sliderChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->handlerInfoGameReceived((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->handleClosed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->handlerTypeMap((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: { std::string _r = _t->typeWeaponToString((*reinterpret_cast< TypeWeapon_t(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< std::string*>(_a[0]) = std::move(_r); }  break;
        case 8: { QPixmap _r = _t->getTextureMap((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        case 9: { QPixmap _r = _t->getTextureIconSoldier((*reinterpret_cast< QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QPixmap*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (Join::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Join::closedWithError)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (Join::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&Join::emitTypeMap)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Join::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_Join.data,
    qt_meta_data_Join,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Join::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Join::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Join.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int Join::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void Join::closedWithError(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Join::emitTypeMap(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
